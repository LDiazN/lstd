#include <iostream>
#include <lstd/memory/rc_ptr.hpp>
#include <lstd/utils/pair.hpp>
#include <lstd/collections/vector.hpp>

using namespace std;
using namespace lstd;

class A
{
public:
    A()
    {
        cout << "[ ] Constructing (default)\n";
    }
    A(const A&)
    {
        cout << "[X] Constructing (copy)\n";
    }

    A& operator=(A&& other)
    {
        cout << "[ ] Moving\n";
        return *this;
    }

    A& operator=(const A& other)
    {
        cout << "[X] Copying\n";
        return *this;
    }
};

class B
{
public:
    void f(A a)
    {
        _a = std::move(a);
    }
    A _a;
};

void g(A a)
{
    // Control
}

int main() {

    A a;
    cout << "--- < Ignore > ------------------------ \n";
    B b;
    cout << "--- < End Ignore > -------------------- \n";
    b.f(a);

    return 0;
}
