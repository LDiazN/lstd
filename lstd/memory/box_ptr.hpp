#ifndef BOX_PTR_HPP
#define BOX_PTR_HPP

#include <lstd/debug/assert.hpp>

namespace lstd {

    /// Simple owning ptr, only allows one reference to the given pointer
    template<typename T>
    class BoxPtr
    {
    public:
        BoxPtr() {}

        BoxPtr(T* _ptr) : ptr(_ptr) {}

        BoxPtr(const BoxPtr& other) = delete;

        BoxPtr(BoxPtr&& other) {
            ptr = other.Take();
        }

        BoxPtr<T>& operator=(const BoxPtr<T>& other) = delete;

        BoxPtr<T>& operator=(BoxPtr<T>&& other) {
            // Q: Is this really possible?
            if (&other == this)
                return *this;

            Destroy();
            ptr = other.Take();

            return *this;
        }

        BoxPtr<T>& operator=(std::nullptr_t&) {
            Destroy();
            ptr = nullptr;

            return *this;
        }

        ~BoxPtr() {
            if (ptr != nullptr)
                delete ptr;
        }

        T& operator*() {
            Assert(ptr != nullptr, "dereferencing null ptr");
            return *ptr;
        }

        const T& operator*() const {
            Assert(ptr != nullptr, "dereferencing null ptr");
            return *ptr;
        }

        T* operator->() {
            Assert(ptr != nullptr, "dereferencing null ptr");
            return ptr;
        }

        const T* operator->() const {
            Assert(ptr != nullptr, "dereferencing null ptr");
            return ptr;
        }

        bool operator==(const BoxPtr<T>& other) const {
            return ptr == other.ptr;
        }

        bool operator==(std::nullptr_t) const {
            return ptr == nullptr;
        }

        bool operator!=(const BoxPtr<T>& other) const {
            return !(ptr == other.ptr);
        }

        T* RawPtr() const {
            return ptr;
        }

    private:
        T* Take() {
            auto p = ptr;
            ptr = nullptr;
            return p;
        }

        void Destroy() {
            if (ptr != nullptr)
                delete ptr;
        }

    private:
        T* ptr = nullptr;
    };
}

#endif