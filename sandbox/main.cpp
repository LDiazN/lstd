#include <iostream>
#include <lstd/memory/rc_ptr.hpp>
#include <lstd/utils/pair.hpp>
#include <lstd/collections/vector.hpp>

using namespace std;
using namespace lstd;

int main() {

    Ptr<Pair<string,string>> ptr(new Pair<string,string>("Hello ","World!"));
    cout << ptr->first << ptr->second << endl;


    return 0;
}