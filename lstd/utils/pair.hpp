#ifndef PAIR_HPP
#define PAIR_HPP

namespace lstd
{

    template <typename T1, typename T2>
    struct Pair
    {
        T1 first;
        T2 second;

        Pair(T1 _first, T2 _second) : first(_first), second(_second) {}
        Pair() : first(), second() {}
        Pair(T1 value) : Pair(value, value) {}
    };

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

#endif