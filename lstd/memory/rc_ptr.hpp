#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP
#include <lstd/debug/assert.hpp>

namespace lstd {

    template <typename T>
    struct RcPtrEntry
    {
        size_t count = 0;
        T *ptr = nullptr;

        RcPtrEntry(T* _ptr) : ptr(_ptr), count(1) {}

        /// Increases reference count, returns new count value
        int Inc() 
        {
            count++;
            return count;
        }
        
        /// Decreases reference count, destroys internal object if counter reaches 0
        /// Returns new count value
        int Dec() 
        {
            Assert(count > 0, "Reference count should be positive");

            count--;
            if (count == 0)
            {
                Destroy();
                return 0;
            }

            return count;
        }
        
        /// Destroys internal object
        void Destroy() 
        {
            if (ptr != nullptr)
                delete ptr;

            ptr = nullptr;
        }
    };

    template <typename T>
    class RcPtr
    {
    public:
        RcPtr(T* ptr) 
        {
            entry = new RcPtrEntry<T>(ptr);
        }

        RcPtr(const T& value) 
        {
            auto ptr = new T(value);
            entry = new RcPtrEntry<T>(ptr);
        }

        RcPtr(const RcPtr<T>& other) 
        {
            if (other.entry == nullptr)
                return; 
            
            entry = other.entry;
            entry->Inc();
        }

        RcPtr() {}

        /// Current reference count. 
        /// If null return 0
        int Count() const {
            if (entry != nullptr)
                return entry->count;
            return 0;
        }

        bool operator==(void* ptr) const {
            if (entry == nullptr)
                return ptr == nullptr;
            
            return ptr == entry->ptr;
        }

        bool operator!=(void* ptr) const {
            return !(this->operator==(ptr));
        }

        bool operator==(const RcPtr<T>& other) const
        {
            return other.entry == entry;
        }

        bool operator!=(const RcPtr<T>& other) const
        {
            return !(this->operator==(other));
        }

    private:
        RcPtrEntry<T>* entry = nullptr;
    };

    // We consider RcPtr like the default pointer type
    template <typename T>
    using Ptr = RcPtr<T>;
}

#endif