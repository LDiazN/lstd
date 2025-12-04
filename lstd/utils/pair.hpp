#ifndef PAIR_HPP
#define PAIR_HPP

namespace lstd
{

    template <typename T1, typename T2>
    struct Pair
    {
        T1 first;
        T2 second;

        Pair() : first(), second() {}
        Pair(T1 value) : Pair(value, value) {}

        // All combinations of rvalue and lvalue
        Pair(const T1& _first, const T2& _second) : first(_first), second(_second) {}
        Pair(T1&& _first, T2&& _second) : first(std::move(_first)), second(std::move(_second)) {}
        Pair(T1&& _first, const T2& _second) : first(std::move(_first)), second(_second) {}
        Pair(const T1& _first, T2&& _second) : first(_first), second(std::move(_second)) {}
    };

    // Use standalone function operators to allow usage of rvalues in left hand
    template <typename T1, typename T2>
    bool operator<(const Pair<T1, T2>& left, const Pair<T1, T2>& right)
    {
        return left.first < right.first || (left.first == right.first && left.second < right.second);
    }

    template <typename T1, typename T2>
    bool operator>(const Pair<T1, T2>& left, const Pair<T1, T2>& right)
    {
        return !(left < right) && left != right;
    }

    template <typename T1, typename T2>
    bool operator==(const Pair<T1, T2>& left, const Pair<T1, T2>& right) {
        return left.first == right.first && left.second == right.second;
    }

    template <typename T1, typename T2>
    bool operator!=(const Pair<T1, T2>& left, const Pair<T1, T2>& right) {
        return !(left == right);
    }
}

// TODO replace this with our own hashing solution
namespace std {
    template<typename T1, typename T2>
    struct hash<lstd::Pair<T1, T2>> {
        size_t operator()(const lstd::Pair<T1, T2>& p) const noexcept
        {
            return hash<T1>{}(p.first) ^ hash<T2>{}(p.second);
        }
    };
}

#endif