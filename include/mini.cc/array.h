#pragma once

#include <mini.c/array.h>

namespace mini
{
    template<typename T>
    struct array_iter {
        T *begin_;
        T *end_;

        array_iter(T *array) : begin_(array), end_(array + mini_array_count(array)) {}

        T *begin() { return begin_; }
        T *end()   { return end_; }

        const T *begin() const { return begin_; }
        const T *end()   const { return end_; }
    };

    template<typename T>
    array_iter<T> iterate(T *array) { return array_iter(array); }

    template<typename T>
    struct Array {
        MINI_ARRAY(T) base_;

        Array(Mini_Allocator allocator)
            : base_(MINI_ARRAY_INIT(allocator, T))
        {

        }

        Array()
            : base_(nullptr)
        {

        }

        void destroy()
        {
            MINI_ASSERT(base_ != nullptr,);
            mini_array_destroy(base_);
        }

        usize count() const
        {
            MINI_ASSERT(base_ != nullptr,);
            return mini_array_count(base_);
        }

        array_iter<T> iter()
        {
            MINI_ASSERT(base_ != nullptr,);
            return iterate(base_);
        }

        array_iter<const T> iter() const
        {
            MINI_ASSERT(base_ != nullptr,);
            return iterate((const T*)base_);
        }

        usize append(T item)
        {
            MINI_ASSERT(base_ != nullptr,);
            mini_array_append(base_, item);
            return count() - 1;
        }

        void insert(T item, usize index)
        {
            MINI_ASSERT(base_ != nullptr,);
            mini_array_insert(base_, item, index);
        }

        void remove(usize index)
        {
            MINI_ASSERT(base_ != nullptr,);
            mini_array_remove(base_, index);
        }

        void clear()
        {
            MINI_ASSERT(base_ != nullptr,);
            mini_array_clear(base_);
        }

        T &operator[](usize index)
        {
            MINI_ASSERT(base_ != nullptr,);
            return base_[index];
        }

        const T &operator[](usize index) const
        {
            MINI_ASSERT(base_ != nullptr,);
            return base_[index];
        }
    };

} // namespace mini
