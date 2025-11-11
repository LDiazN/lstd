#include "assert.hpp"
using namespace lstd;

void lstd::Assert(bool condition, std::string message)
{
#ifdef DEBUG
    if (!condition)
        throw AssertionError(message);
#endif
}
