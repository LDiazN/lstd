#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

namespace lstd {
    template <typename T>
    class RcPtr
    {
    };

    template <typename T>
    struct RcPtrEntry
    {
        size_t count = 0;
        T *ptr = nullptr;
    };
}

#endif