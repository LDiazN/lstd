#ifndef __ASSERT_HPP__
#define __ASSERT_HPP__

#include <string>

namespace lstd {
    void Assert(bool condition, std::string message="");

    struct AssertionError {
        std::string message;
        AssertionError(std::string m) : message(m) {}
    };
}
#endif