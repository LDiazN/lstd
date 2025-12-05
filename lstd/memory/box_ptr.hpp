#ifndef BOX_PTR_HPP
#define BOX_PTR_HPP

#include <lstd/debug/assert.hpp>

namespace lstd {

    /// Simple owning ptr, only allows one reference to the given pointer
    template<typename T>
    class BoxPtr
    {
    public:
        BoxPtr() = default;

        BoxPtr(T* _ptr) : ptr(_ptr) {}

        BoxPtr(const BoxPtr& other) = delete;

        BoxPtr(BoxPtr&& other) {
            ptr = other.Take();
        }

        BoxPtr& operator=(const BoxPtr& other) = delete;

        BoxPtr& operator=(BoxPtr&& other) {
            // Q: Is this really possible?
            if (&other == this)
                return *this;

            Destroy();
            ptr = other.Take();

            return *this;
        }

        BoxPtr& operator=(std::nullptr_t) {
            Destroy();
            ptr = nullptr;

            return *this;
        }

        ~BoxPtr() {
            Destroy();
        }

        T& operator*() {
            return const_cast<T&>(*std::as_const(*this));
        }

        const T& operator*() const {
            Assert(ptr != nullptr, "dereferencing null ptr");
            return *ptr;
        }

        T* operator->() {
            return const_cast<T*>(std::as_const(*this).operator->());
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