#pragma once

#include <array>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <pstl/glue_execution_defs.h>
#include <type_traits>
#include <utility>

namespace mcquack {

template<class T>
class vector
{
public:
    /// @typedef value_type
    /// @brief Defines the type of elements stored in the vector.
    using value_type = T;

    /// @typedef reference
    /// @brief Alias for a reference to the element type.
    using reference = T&;

    /// @typedef const_reference
    /// @brief Alias for a constant reference to the element type.
    using const_reference = const T&;

    /// @typedef pointer
    /// @brief Alias for a pointer to the element type.
    using pointer = T*;

    /// @typedef const_pointer
    /// @brief Alias for a constant pointer to the element type.
    using const_pointer = const T*;

    /// @typedef iterator
    /// @brief Alias for an iterator over the element type.
    using iterator = T*;

    /// @typedef const_iterator
    /// @brief Alias for a constant iterator over the element type.
    using const_iterator = const T*;

    /// @typedef reverse_iterator
    /// @brief Alias for a reverse iterator over the element type.
    using reverse_iterator = std::reverse_iterator<iterator>;

    /// @typedef const_reverse_iterator
    /// @brief Alias for a constant reverse iterator over the element type.
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /// @typedef difference_type
    /// @brief Alias for the type representing the difference between two iterators.
    using difference_type = ptrdiff_t;

    /// @typedef size_type
    /// @brief Alias for the type that can represent the size of the vector.
    using size_type = std::size_t;

    constexpr vector() noexcept
    {
        // static_assert(sizeof(dynamic_) == sizeof(small_));
        if constexpr(SMALL_VECTOR_OPTIMIZATION_ENABLED) {
            small_init();
        } else {
            dynamic_init();
        }
    }

    constexpr vector(size_type count, const T& value) noexcept
    {
        if constexpr(SMALL_VECTOR_OPTIMIZATION_ENABLED) {
            if(count > SMALL_CAPACITY) {
                dynamic_.size_ = count;
                dynamic_.capacity_ = count;
                dynamic_.data_ = static_cast<T*>(std::malloc(ELEMENT_SIZE * count));
                std::uninitialized_fill(dynamic_.data_,
                                        dynamic_.data_ + count,
                                        value);
            } else {
                small_init();
                std::uninitialized_fill(small_.data_.data(),
                                        small_.data_.data() + count,
                                        value);
                inc_small_size_by(count);
            }
        } else {
            dynamic_.size_ = count;
            dynamic_.capacity_ = count;
            dynamic_.data_ = static_cast<T*>(std::malloc(ELEMENT_SIZE * count));
            std::uninitialized_fill(dynamic_.data_,
                                    dynamic_.data_ + count,
                                    value);
        }
    }

    constexpr explicit vector(size_type count) noexcept
    {
        if constexpr(SMALL_VECTOR_OPTIMIZATION_ENABLED) {
            if(count > SMALL_CAPACITY) {
                dynamic_.size_ = count;
                dynamic_.capacity_ = count;
                dynamic_.data_ = static_cast<T*>(std::malloc(ELEMENT_SIZE * count));
                std::uninitialized_value_construct(dynamic_.data_, dynamic_.data_ + count);
            } else {
                small_init();
                inc_small_size_by(count);
            }
        } else {
            dynamic_.size_ = count;
            dynamic_.capacity_ = count;
            dynamic_.data_ = static_cast<T*>(std::malloc(ELEMENT_SIZE * count));
            std::uninitialized_value_construct(dynamic_.data_, dynamic_.data_ + count);
        }
    }


    // TODO: implement this
    template<class InputIt>
        requires std::input_iterator<InputIt>
    constexpr vector(InputIt first, InputIt last) noexcept;


    // TODO: implement copy/move - assignment/ctors with a swap function
    constexpr vector(const vector& other) noexcept
    {
        if constexpr(SMALL_VECTOR_OPTIMIZATION_ENABLED) {
            if(other.is_small()) {
                small_ = other.small_;
                return;
            }
        }

        dynamic_.size_ = other.dynamic_.size_;
        dynamic_.capacity_ = other.dynamic_.capacity_;
        dynamic_.data_ = static_cast<T*>(std::malloc(ELEMENT_SIZE * dynamic_.capacity_));

        if constexpr(std::is_trivially_constructible_v<T>) {
            std::memcpy(dynamic_.data_, other.dynamic_.data_, dynamic_.size_);
        } else {
            std::uninitialized_copy(other.dynamic_.data_,
                                    other.dynamic_.data_ + dynamic_.size_,
                                    dynamic_.data_);
        }
    }

    constexpr vector(vector&& other) noexcept
    {
        if constexpr(SMALL_VECTOR_OPTIMIZATION_ENABLED) {
            if(other.is_small()) {
                small_ = std::move(other.small_);
                return;
            }
        }

        dynamic_ = other.dynamic_;

        // "nullify" other's dynamic_ to avoid deallocation of the moved resources
        other.dynamic_.data_ = nullptr;
        other.dynamic_.size_ = 0;
        other.dynamic_.capacity_ = 0;
    }

    constexpr auto operator=(const vector& other) noexcept -> vector&
    {
        // TODO: IMPLEMENT
    }

    constexpr auto operator=(vector&& other) noexcept -> vector&
    {
        // TODO: IMPLEMENT
    }

    constexpr ~vector()
    {
        if constexpr(not std::is_trivially_destructible_v<T>) {
            auto* d = data();
            auto s = size();
            std::destroy(d, d + s);
        }

        if constexpr(SMALL_VECTOR_OPTIMIZATION_ENABLED) {
            if(not is_small()) {
                std::free(dynamic_.data_);
            }
        } else {
            std::free(dynamic_.data_);
        }
    }

    ////////////////////////////////////////////////////////////////////
    //                 ITERATORS
    ////////////////////////////////////////////////////////////////////

    [[nodiscard]] constexpr auto begin() noexcept -> iterator
    {
        return data();
    }

    [[nodiscard]] constexpr auto end() noexcept -> iterator
    {
        return data() + size();
    }

    [[nodiscard]] constexpr auto cbegin() const noexcept -> const_iterator
    {
        return data();
    }

    [[nodiscard]] constexpr auto cend() const noexcept -> const_iterator
    {
        return data() + size();
    }

    [[nodiscard]] constexpr auto rbegin() noexcept -> reverse_iterator
    {
        return std::reverse_iterator(end());
    }

    [[nodiscard]] constexpr auto rend() noexcept -> reverse_iterator
    {
        return std::reverse_iterator(begin());
    }

    [[nodiscard]] constexpr auto crbegin() const noexcept -> const_reverse_iterator
    {
        return data();
        return std::reverse_iterator(cbegin());
    }

    [[nodiscard]] constexpr auto crend() const noexcept -> const_reverse_iterator
    {
        return std::reverse_iterator(cbegin());
    }


    ////////////////////////////////////////////////////////////////////
    //                 INDEX OPERATORS
    ////////////////////////////////////////////////////////////////////

    [[nodiscard]] constexpr auto operator[](std::size_t pos) noexcept -> T&
    {
        return data()[pos];
    }

    [[nodiscard]] constexpr auto operator[](std::size_t pos) const noexcept -> const T&
    {
        return data()[pos];
    }

    ////////////////////////////////////////////////////////////////////
    //                 FRONT AND BACK
    ////////////////////////////////////////////////////////////////////

    [[nodiscard]] constexpr auto front() const noexcept -> const T&
    {
        return data()[0];
    }

    [[nodiscard]] constexpr auto front() noexcept -> T&
    {
        return data()[0];
    }

    [[nodiscard]] constexpr auto back() const noexcept -> const T&
    {
        return data()[size() - 1];
    }

    [[nodiscard]] constexpr auto back() noexcept -> T&
    {
        return data()[size() - 1];
    }

    ////////////////////////////////////////////////////////////////////
    //                 EMPLACE_BACK AND PUSH_BACK
    ////////////////////////////////////////////////////////////////////
    template<class... Args>
    constexpr auto emplace_back(Args&&... args) noexcept -> void
    {
        const auto current_size = size();

        if constexpr(SMALL_VECTOR_OPTIMIZATION_ENABLED) {
            if(is_small() and current_size < SMALL_CAPACITY) {
                new(small_.data_.data() + current_size) T{std::forward<Args>(args)...};
                inc_small_size();
                return;
            }

            if(is_small() and current_size == SMALL_CAPACITY) {
                const std::size_t new_capacity = SMALL_CAPACITY * GROW_FACTOR;

                auto* data = static_cast<T*>(std::malloc(new_capacity * ELEMENT_SIZE));

                if constexpr(std::is_trivially_constructible_v<T>) {
                    std::memcpy(data, small_.data_.data(), current_size * ELEMENT_SIZE);
                } else {
                    std::uninitialized_move(small_.data_.begin(),
                                            small_.data_.end(),
                                            data);
                }

                if constexpr(not std::is_trivially_destructible_v<T>) {
                    std::destroy(small_.data_.begin(), dynamic_.data_.end());
                }

                dynamic_.capacity_ = new_capacity;
                dynamic_.size_ = current_size;
                dynamic_.data_ = data;
            }
        }

        if(current_size == dynamic_.capacity_) {
            const std::size_t new_capacity = std::max(current_size, INITIAL_HEAP_SIZE) * GROW_FACTOR;

            if constexpr(std::is_trivially_constructible_v<T> and std::is_trivially_destructible_v<T>) {
                dynamic_.data_ = static_cast<T*>(std::realloc(dynamic_.data_, new_capacity * ELEMENT_SIZE));
            } else {
                auto* data = static_cast<T*>(std::malloc(new_capacity * ELEMENT_SIZE));

                if constexpr(std::is_trivially_constructible_v<T>) {
                    std::memcpy(data, dynamic_.data_, current_size * ELEMENT_SIZE);
                } else {
                    // move old heap to new one
                    std::uninitialized_move(dynamic_.data_,
                                            dynamic_.data_ + current_size,
                                            data);
                }

                if constexpr(not std::is_trivially_destructible_v<T>) {
                    std::destroy(dynamic_.data_, dynamic_.data_ + current_size);
                }

                std::free(dynamic_.data_);

                dynamic_.data_ = data;
            }

            dynamic_.capacity_ = new_capacity;
        }

        new(dynamic_.data_ + current_size) T{std::forward<Args>(args)...};
        dynamic_.size_++;
    }

    constexpr auto push_back(const T& elem) noexcept -> void
    {
        emplace_back(elem);
    }

    constexpr auto push_back(T&& elem) noexcept -> void
    {
        emplace_back(std::move(elem));
    }

    ////////////////////////////////////////////////////////////////////
    //                         POP_BACK
    ////////////////////////////////////////////////////////////////////

    constexpr auto pop_back() noexcept -> void
    {
        if constexpr(SMALL_VECTOR_OPTIMIZATION_ENABLED) {
            if(is_small()) {
                dec_small_size();
                return;
            }
        }

        dynamic_.size_--;
    }


    ////////////////////////////////////////////////////////////////////
    //                         DATA
    ////////////////////////////////////////////////////////////////////

    [[nodiscard]] constexpr auto data() const noexcept -> const T*
    {

        if constexpr(SMALL_VECTOR_OPTIMIZATION_ENABLED) {
            if(is_small()) {
                return small_.data_.data();
            }
        }
        return dynamic_.data_;
    }

    [[nodiscard]] constexpr auto data() noexcept -> T*
    {

        if constexpr(SMALL_VECTOR_OPTIMIZATION_ENABLED) {
            if(is_small()) {
                return small_.data_.data();
            }
        }
        return dynamic_.data_;
    }

    ////////////////////////////////////////////////////////////////////
    //                         SIZE, EMPTY AND CAPACITY
    ////////////////////////////////////////////////////////////////////
    [[nodiscard]] constexpr auto size() const noexcept -> std::size_t
    {

        if constexpr(SMALL_VECTOR_OPTIMIZATION_ENABLED) {
            if(is_small()) {
                return small_size();
            }
        }

        return dynamic_.size_;
    }

    [[nodiscard]] constexpr auto capacity() const noexcept -> std::size_t
    {

        if constexpr(SMALL_VECTOR_OPTIMIZATION_ENABLED) {
            if(is_small()) {
                return SMALL_CAPACITY;
            }
        }

        return dynamic_.capacity_;
    }


    [[nodiscard]] constexpr auto empty() const noexcept -> bool
    {
        return size() <= 0;
    }


    ////////////////////////////////////////////////////////////////////
    //                         swap
    ////////////////////////////////////////////////////////////////////

    constexpr auto swap(vector& other) noexcept -> void
    {
        if constexpr(SMALL_VECTOR_OPTIMIZATION_ENABLED) {
            // If both vectors are small
            if(is_small() && other.is_small()) {
                std::swap(small_, other.small_);
                return;
            }

            // If both vectors are large
            if(!is_small() && !other.is_small()) {
                std::swap(dynamic_, other.dynamic_);
                return;
            }

            // One is small and the other is large
            if(is_small()) {
                auto temp_small = small_;
                dynamic_ = other.dynamic_;
                other.small_ = temp_small;
            } else {
                auto temp_dynamic = dynamic_;
                small_ = other.small_;
                other.dynamic_ = temp_dynamic;
            }
        } else {
            std::swap(dynamic_, other.dynamic_);
        }
    }

    ////////////////////////////////////////////////////////////////////
    //                         reserve
    ////////////////////////////////////////////////////////////////////
    constexpr auto reserve(std::size_t required) noexcept
    {
        if(required <= capacity()) {
            return;
        }

        // TODO: implement me!
    }

private:
    [[nodiscard]] constexpr auto is_small() const noexcept -> bool
    {
        return small_.info_ & 0b00000001;
    }

    constexpr auto tag_as_small() noexcept -> void
    {
        small_.info_ |= 0b00000001;
    }

    [[nodiscard]] constexpr auto small_size() const noexcept -> std::uint8_t
    {
        return small_.info_ >> 1;
    }

    constexpr auto inc_small_size_by(std::size_t number) noexcept -> void
    {
        small_.info_ += static_cast<std::uint8_t>(number) << 1;
    }

    constexpr auto inc_small_size() noexcept -> void
    {
        small_.info_ += 2;
    }

    constexpr auto dec_small_size() noexcept -> void
    {
        small_.info_ -= 2;
    }

    constexpr auto zero_small_size() noexcept -> void
    {
        small_.info_ = 0b00000001;
    }

    constexpr auto small_init() noexcept -> void
    {
        zero_small_size();
        tag_as_small();
    }

    constexpr auto dynamic_init() noexcept -> void
    {
        dynamic_.size_ = 0;
        dynamic_.capacity_ = 0;
        dynamic_.data_ = nullptr;
    }

    // Compute the size of the custom vector in bytes.
    // This is calculated as the sum of sizes of two std::size_t members and one T* member,
    // minus two bytes which are used for tagging and size tracking.
    constinit inline static const auto VECTOR_SIZE =
        2 * sizeof(std::size_t)
        + sizeof(T*)
        - sizeof(std::uint8_t);


    // Size of one element in the vector
    constinit inline static const std::size_t ELEMENT_SIZE = sizeof(T);
    constinit inline static const std::size_t SMALL_CAPACITY = VECTOR_SIZE / ELEMENT_SIZE;
    constinit inline static const std::size_t INITIAL_HEAP_SIZE = 10ul;
    constinit inline static const double GROW_FACTOR = 1.5;
    constinit inline static const bool SMALL_VECTOR_OPTIMIZATION_ENABLED = SMALL_CAPACITY > 0;


private:
    // clang-format off
        struct Empty{};
    // clang-format on

    union
    {
        // Structure for the dynamic array representation
        struct
        {
            std::size_t size_;     // Number of elements in the array
            std::size_t capacity_; // Maximum number of elements that can be stored without reallocating
            T* data_;              // Pointer to the dynamic array

        } dynamic_;

        struct
        {
            std::array<T, SMALL_CAPACITY> data_;

            // fill up the space between data_ and info,
            // such that info_ aligns with the dynamic_.data_ first byte
            [[no_unique_address]] std::conditional_t<
                sizeof(dynamic_) - (sizeof(data_) + 1) == 0,
                Empty,
                std::array<std::uint8_t, sizeof(dynamic_) - (sizeof(data_) + 1)>>
                dummy_;

            std::uint8_t info_;
        } small_;
    };

    static_assert(sizeof(dynamic_) == sizeof(small_));
};


// TODO: optimize
template<class First, class... Args>
    requires(std::is_same_v<First, Args> and ...)
constexpr auto make_vector(First&& first, Args&&... args) -> vector<std::remove_cvref_t<First>>
{
    vector<std::remove_cvref_t<First>> vec;
    vec.emplace_back(std::forward<First>(first));
    (vec.emplace_back(std::forward<Args>(args)), ...);
    return vec;
}

} // namespace mcquack
