#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <cmath>
#include <utility>

namespace project
{
template <typename T>
class vector2
{
    static_assert(std::is_arithmetic_v<T>, "Vector2 only supports numeric types");

public:
    vector2()  = delete;
    ~vector2() = default;
    template <typename Tp, typename Up>
    vector2(Tp x, Up y)
    {
        data = {static_cast<T>(x), static_cast<T>(y)};
    }
    vector2(const vector2 &b)     = default;
    vector2(vector2 &&b) noexcept = default;
    vector2 operator+(const vector2 &b) const
    {
        return {this->data.first + b.data.first, this->data.second + b.data.second};
    }
    vector2 &operator+=(const vector2 &b)
    {
        this->data = {this->data.first + b.data.first, this->data.second + b.data.second};
        return *this;
    }
    vector2 operator+(T b) const
    {
        return {this->data.first + b, this->data.second + b};
    }
    vector2 &operator+=(T b)
    {
        this->data = {this->data.first + b, this->data.second + b};
        return *this;
    }
    vector2 operator-(const vector2 &b) const
    {
        return {this->data.first - b.data.first, this->data.second - b.data.second};
    }
    vector2 &operator-=(const vector2 &b)
    {
        this->data = {this->data.first - b.data.first, this->data.second - b.data.second};
        return *this;
    }
    vector2 operator-(T b) const
    {
        return {this->data.first - b, this->data.second - b};
    }
    vector2 &operator-=(T b)
    {
        this->data = {this->data.first - b, this->data.second - b};
        return *this;
    }
    vector2 operator*(const vector2 &b) const
    {
        return {this->data.first * b.data.first, this->data.second * b.data.second};
    }
    vector2 &operator*=(const vector2 &b)
    {
        this->data = {this->data.first * b.data.first, this->data.second * b.data.second};
        return *this;
    }
    vector2 operator*(T b) const
    {
        return {this->data.first * b, this->data.second * b};
    }
    vector2 &operator*=(T b)
    {
        this->data = {this->data.first * b, this->data.second * b};
        return *this;
    }
    vector2 operator/(const vector2 &b) const
    {
        return {this->data.first / b.data.first, this->data.second / b.data.second};
    }
    vector2 &operator/=(const vector2 &b)
    {
        this->data = {this->data.first / b.data.first, this->data.second / b.data.second};
        return *this;
    }
    vector2 operator/(T b) const
    {
        return {this->data.first / b, this->data.second / b};
    }
    vector2 &operator/=(T b)
    {
        this->data = {this->data.first / b, this->data.second / b};
        return *this;
    }
    bool operator==(const vector2 &b) const
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return (std::abs(this->data.first - b.data.first) < 0.001 &&
                    std::abs(this->data.second - b.data.second) < 0.001);
        }
        return (this->data.first == b.data.first && this->data.second == b.data.second);
    }
    bool operator!=(const vector2 &b) const
    {
        return (!((*this) == b));
    }
    vector2 &operator=(const vector2 &b)
    {
        data = b.data;
        return *this;
    }
    T get_x() const
    {
        return data.first;
    }
    T get_y() const
    {
        return data.second;
    }

private:
    std::pair<T, T> data{0, 0};
};

template <typename Tp, typename Up>
vector2(Tp, Up) -> vector2<std::common_type_t<Tp, Up>>;
} // namespace project

#endif