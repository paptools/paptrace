#ifndef PAPTRACE_UTILS_H
#define PAPTRACE_UTILS_H

// Third-party headers.
#include <gtest/gtest.h>

// C++ standard library headers.
#include <sstream>
#include <string>

namespace paptrace {
namespace utils {
template <typename T>::std::string PrintToString(const T &value) {
  std::stringstream ss;
  ::testing::internal::UniversalTersePrinter<T>::Print(value, &ss);
  return ss.str();
}
} // namespace utils
} // namespace paptrace

// Utility macros.
#define TOKEN_PASTE(x, y) x##y
#define TOKEN_PASTE2(x, y) TOKEN_PASTE(x, y)
#define TO_STRING(x) paptrace::utils::PrintToString(x)

// Utility macros for looping over variadic arguments.
#define FE_0(WHAT)
#define FE_1(WHAT, X) WHAT(X)
#define FE_2(WHAT, X, ...) WHAT(X) FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X) FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X) FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X) FE_4(WHAT, __VA_ARGS__)
#define FE_6(WHAT, X, ...) WHAT(X) FE_5(WHAT, __VA_ARGS__)
#define FE_7(WHAT, X, ...) WHAT(X) FE_6(WHAT, __VA_ARGS__)
#define FE_8(WHAT, X, ...) WHAT(X) FE_7(WHAT, __VA_ARGS__)
#define FE_9(WHAT, X, ...) WHAT(X) FE_8(WHAT, __VA_ARGS__)
#define FE_10(WHAT, X, ...) WHAT(X) FE_9(WHAT, __VA_ARGS__)
#define GET_MACRO(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME
#define FOR_EACH(action, ...)                                                  \
  GET_MACRO(_0, __VA_ARGS__, FE_10, FE_9, FE_8, FE_7, FE_6, FE_5, FE_4, FE_3,  \
            FE_2, FE_1, FE_0)                                                  \
  (action, __VA_ARGS__)

#endif // PAPTRACE_UTILS_H
