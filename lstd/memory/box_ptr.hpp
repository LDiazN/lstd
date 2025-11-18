#ifndef BOX_PTR_HPP
#define BOX_PTR_HPP

namespace lstd {

    template<typename T>
    class BoxPtr
    {
    public:
        BoxPtr() {}
        BoxPtr(T* _ptr) : ptr(_ptr) {}


    private:
        T* ptr = nullptr;
    };
}

#endif