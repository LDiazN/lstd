#include "assert.hpp"

void lstd::Assert(bool condition, std::string message)
{
#ifdef DEBUG
    if (!condition)
        throw AssertionError(message);
#endif
}
