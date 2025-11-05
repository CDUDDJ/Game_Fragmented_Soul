#include "../include/time_tool.hpp"

using namespace project;

float time_tool::second_to_nanosecond(float second)
{
    return second * 1e9;
}

float time_tool::nanosecond_to_second(float nanosecond)
{
    return nanosecond / 1e9;
}