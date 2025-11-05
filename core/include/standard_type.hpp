#ifndef STANDARD_TYPE_HPP
#define STANDARD_TYPE_HPP

#include <cstdint>
#include <tuple>
#include <utility>

namespace standard_type
{
using int8   = std::int8_t;
using int16  = std::int16_t;
using int32  = std::int32_t;
using int64  = std::int64_t;
using uint8  = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;
using point  = std::pair<float, float>;
using RGBA   = std::tuple<uint8, uint8, uint8, uint8>;
} // namespace standard_type

#endif