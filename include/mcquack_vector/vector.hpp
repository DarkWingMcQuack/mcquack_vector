#pragma once

#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
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

    vector() noexcept
    {
        // static_assert(sizeof(dynamic_) == sizeof(small_));
        if constexpr(VECTOR_SIZE != 0) {
            tag_ptr();
            zero_small_size();
        }
    }

    ~vector()
    {

        if constexpr(VECTOR_SIZE == 0) {
            delete[] dynamic_.data_;
        } else {
            if(not data_ptr_tagged()) {
                delete[] dynamic_.data_;
            }
        }
    }

    /// @brief Access elements of the vector
    /// @param pos Position of the element in the vector
    /// @return Reference to the element at the specified position
    /// @warning Calling this function with an out of range index results in undefined behavior.
    [[nodiscard]] auto operator[](std::size_t pos) noexcept -> T&
    {
        return data()[pos];
    }


    /// @brief Access elements of the vector (const version)
    /// @param pos Position of the element in the vector
    /// @return Const reference to the element at the specified position
    /// @warning Calling this function with an out of range index results in undefined behavior.
    [[nodiscard]] auto operator[](std::size_t pos) const noexcept -> const T&
    {
        return data()[pos];
    }

    /// @brief Access the first element in the vector (const version)
    /// @return Const reference to the first element in the vector
    /// @warning Calling this function on an empty vector results in undefined behavior.
    [[nodiscard]] auto front() const noexcept -> const T&
    {
        return data()[0];
    }

    /// @brief Access the first element in the vector
    /// @return Reference to the first element in the vector
    /// @warning Calling this function on an empty vector results in undefined behavior.
    [[nodiscard]] auto front() noexcept -> T&
    {
        return data()[0];
    }

    /// @brief Access the last element in the vector (const version)
    /// @return Const reference to the last element in the vector
    /// @warning Calling this function on an empty vector results in undefined behavior.
    [[nodiscard]] auto back() const noexcept -> const T&
    {
        return data()[size() - 1];
    }

    /// @brief Access the last element in the vector
    /// @return Reference to the last element in the vector
    /// @warning Calling this function on an empty vector results in undefined behavior.
    [[nodiscard]] auto back() noexcept -> T&
    {
        return data()[size() - 1];
    }

    /// @brief Check whether the vector is empty
    /// @return True if the vector is empty, false otherwise
    [[nodiscard]] auto empty() const noexcept -> bool
    {
        return size() <= 0;
    }

    /**
     * @brief Adds a new element to the end of the vector
     * @param args The arguments to forward to the constructor of the element
     * This method constructs a new element in place at the end of the vector from the given arguments.
     * It chooses between four cases based on the current state of the vector:
     * - The vector is small and there is space left in the small buffer, in which case it constructs the new element in the small buffer.
     * - The vector is small and the small buffer is full, in which case it reallocates the vector to the heap.
     * - The vector is large and the heap is full, in which case it reallocates the vector's memory on the heap.
     * - The vector is large and there is space left on the heap, so we just append it in the heap memory.
     */
    template<class... Args>
    auto emplace_back(Args&&... args) noexcept -> void
    {
        const auto current_size = size();

        if constexpr(VECTOR_SIZE != 0) {
            // Case 1: small vector and there is space left in the small buffer
            if(data_ptr_tagged() and current_size < SMALL_CAPACITY) {
                // Construct the new element in the small buffer
                small_.data_[current_size] = T{std::forward<Args>(args)...};
                // Increase the size stored in the tagged pointer
                inc_small_size();
                return;
            }

            // Case 2: small vector and the small buffer is full
            if(data_ptr_tagged() and current_size == SMALL_CAPACITY) {
                // Reallocate to the heap

                // allocate
                auto* data = new T[INITIAL_HEAP_SIZE];

                // move small buffer into newly allocated data
                std::move(small_.data_.begin(),
                          small_.data_.end(),
                          data);

                // set the members to the right values
                dynamic_.size_ = current_size;
                dynamic_.capacity_ = INITIAL_HEAP_SIZE;
                dynamic_.data_ = data;
            }
        }

        // Case 3: large vector and the heap is full
        if(current_size == dynamic_.capacity_) {
            // allocate
            auto* data = new T[dynamic_.capacity_ * GROW_FACTOR];

            // move old heap to new one
            std::move(dynamic_.data_,
                      dynamic_.data_ + dynamic_.capacity_,
                      data);

            delete[] dynamic_.data_;

            dynamic_.capacity_ = dynamic_.capacity_ * GROW_FACTOR;
            dynamic_.data_ = data;
        }

        // Case 4: large vector and there is space left on the heap
        // Just append it in the heap memory
        dynamic_.data_[current_size] = T{std::forward<Args>(args)...};
        dynamic_.size_++;
    }

    /**
     * @brief Adds an element to the end of the vector
     * @param elem The element to be added to the vector
     * This method is a wrapper around the emplace_back method, providing a way
     * to add elements to the vector by copying them.
     */
    auto push_back(const T& elem) noexcept -> void
    {
        emplace_back(elem);
    }

    /**
     * @brief Adds an element to the end of the vector
     * @param elem The element to be added to the vector
     * This method is a wrapper around the emplace_back method, providing a way
     * to add elements to the vector by moving them.
     */
    auto push_back(T&& elem) noexcept -> void
    {
        emplace_back(std::move(elem));
    }

    /**
     * @brief Removes the last element from the vector
     * Does nothing if the vector is empty. If the vector is using small buffer
     * optimization, it decreases the size stored in the tagged pointer.
     * Otherwise, it simply decreases the size field of the vector.
     */
    auto pop_back() noexcept -> void
    {
        if constexpr(VECTOR_SIZE != 0) {
            if(data_ptr_tagged()) {
                dec_small_size();
                return;
            }
        }

        dynamic_.size_--;
    }

    /**
     * @brief Returns a constant pointer to the vector's data
     * If the vector is using small buffer optimization, this function returns
     * a pointer to the small buffer. Otherwise, it returns the data pointer.
     * @return A constant pointer to the vector's data
     */
    [[nodiscard]] auto data() const noexcept -> const T*
    {

        if constexpr(VECTOR_SIZE != 0) {
            if(data_ptr_tagged()) {
                return small_.data_.data();
            }
        }
        return dynamic_.data_;
    }

    /**
     * @brief Returns a pointer to the vector's data
     * If the vector is using small buffer optimization, this function returns
     * a pointer to the small buffer. Otherwise, it returns the data pointer.
     * @return A pointer to the vector's data
     */
    [[nodiscard]] auto data() noexcept -> T*
    {

        if constexpr(VECTOR_SIZE != 0) {
            if(data_ptr_tagged()) {
                return small_.data_.data();
            }
        }
        return dynamic_.data_;
    }

    /**
     * @brief Returns the number of elements in the vector
     * If the vector is using small buffer optimization, this function retrieves
     * the size stored in the tagged pointer. Otherwise, it returns the size field
     * of the vector.
     * @return The number of elements in the vector
     */
    [[nodiscard]] auto size() const noexcept -> std::size_t
    {

        if constexpr(VECTOR_SIZE != 0) {
            if(data_ptr_tagged()) {
                return small_size();
            }
        }

        return dynamic_.size_;
    }

private:
    /**
     * @brief Check if the last bit of the pointer is set
     * @return true if the last bit is set, false otherwise
     */
    [[nodiscard]] auto data_ptr_tagged() const noexcept -> bool
    {
        return small_.info_ & 0b00000001;
    }

    auto tag_ptr() noexcept -> void
    {
        small_.info_ |= 0b00000001;
    }

    [[nodiscard]] auto small_size() const noexcept -> std::uint8_t
    {
        return small_.info_ >> 1;
    }

    auto inc_small_size() noexcept -> void
    {
        small_.info_ += 2;
    }

    auto dec_small_size() noexcept -> void
    {
        small_.info_ -= 2;
    }

    auto zero_small_size() noexcept -> void
    {
        small_.info_ = 0b00000001;
    }



    // Compute the size of the custom vector in bytes.
    // This is calculated as the sum of sizes of two std::size_t members and one T* member,
    // minus two bytes which are used for tagging and size tracking.
    constexpr static const auto VECTOR_SIZE = (2 * sizeof(std::size_t)
                                               + sizeof(T*))
        - sizeof(std::uint8_t);


    // Size of one element in the vector
    constexpr static const auto ELEMENT_SIZE = sizeof(T);

    // Compute the capacity of the vector for the small buffer optimization.
    // This is computed by dividing the total size of the custom vector by the size of one element.
    constexpr static const auto SMALL_CAPACITY = VECTOR_SIZE / ELEMENT_SIZE;

    constexpr static const auto INITIAL_HEAP_SIZE = 16;
    constexpr static const auto GROW_FACTOR = 2;



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

} // namespace mcquack
