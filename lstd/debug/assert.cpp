#include "assert.hpp"
using namespace lstd;

void Assert(bool condition, std::string message)
{
#ifdef DEBUG
    if (!condition)
        throw AssertionError(message);
#endif
}
