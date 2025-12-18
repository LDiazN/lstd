#include <iostream>
#include <lstd/memory/rc_ptr.hpp>
#include <lstd/utils/pair.hpp>
using namespace std;
using namespace lstd;

int main() {

    Pair<string,string> p("Hello ", "World");
    // Ptr<Pair<string,string>> p(new Pair("Hello ","World!"));

    cout << p.first << p.second << endl;

    return 0;
}