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

        bool operator<(const Pair<T1, T2> &other)
        {
            return first < other.first || (first == other.first && second < other.second);
        }

        bool operator==(const Pair<T1, T2> &other)
        {
            return first == other.first && second == other.second;
        }
    };

}

#endif