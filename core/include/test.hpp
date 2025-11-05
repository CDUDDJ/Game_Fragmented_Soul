#ifndef TEST_HPP
#define TEST_HPP

#include "standard_type.hpp"
#include <iostream>
#include <string_view>
#include <type_traits>
#include <utility>

inline standard_type::int64 g_test_failed = 0;

template <typename Func, typename... Args>
auto test(const Func &func, std::string_view info, Args &&...args)
    -> std::enable_if_t<std::is_same_v<std::invoke_result_t<Func, Args...>, bool>>
{
    if (!func(std::forward<Args>(args)...))
    {
        std::cerr << "❌ Test failed: " << info << "\n";
        ++g_test_failed;
    }
}

inline void test(bool expect, std::string_view info)
{
    if (!expect)
    {
        std::cerr << "❌ Test failed: " << info << "\n";
        ++g_test_failed;
    }
}

inline standard_type::int32 test_summary(std::string_view name = "")
{
    if (g_test_failed == 0)
    {
        std::cout << "✅ [" << name << "] All tests passed.\n";
        return 0;
    }
    else
    {
        std::cerr << "❌ [" << name << "] " << g_test_failed << " tests failed.\n";
        return 1;
    }
}

#endif