#ifndef BOX_PTR_HPP
#define BOX_PTR_HPP

#include <lstd/debug/assert.hpp>

namespace lstd {

    template<typename T>
    class BoxPtr
    {
    public:
        BoxPtr() {}

        BoxPtr(T* _ptr) : ptr(_ptr) {}

        BoxPtr(BoxPtr other) = delete;

        BoxPtr(const BoxPtr& other) = delete;

        BoxPtr(BoxPtr&& other) {
            ptr = other.Take();
        }

        operator=(const BoxPtr& other) = delete;

        operator=(BoxPtr&& other) {
            // Q: Is this really possible?
            if (&other == this)
                return;

            Destroy();
            ptr = other.Take();
        }

        operator=(std::nullptr_t&) {
            Destroy();
            ptr = nullptr;
        }

        ~BoxPtr() {
            if (ptr != nullptr)
                delete ptr;
        }

        T operator*() const {
            Assert(ptr != nullptr, "dereferencing null ptr");
            return *ptr;
        }

        T* operator->() const {
            Assert(ptr != nullptr, "dereferencing null ptr");
            return ptr;
        }

        bool operator==(const BoxPtr<T>& other) const {
            return ptr == other.ptr;
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