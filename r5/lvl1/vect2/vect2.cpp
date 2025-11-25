#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {}

vect2::vect2(const vect2 &other) : x(other.x), y(other.y) {}
vect2::~vect2() {}
vect2::vect2(int x_, int y_) : x(x_), y(y_) {}
vect2	&vect2::operator=(const vect2 &other) 
{
	if (*this != other)
	{
		x = other.x;
		y = other.y;
	}
	return (*this);
}

vect2	vect2::operator+(const vect2 &other) const
{
	return(vect2(x + other.x, y + other.y));
}
vect2	&vect2::operator+=(const vect2 &other)
{
	x += other.x;
	y += other.y;
	return (*this);
}

vect2	vect2::operator-(const vect2 &other) const
{
	return (vect2(x - other.x, y - other.y));
}

vect2	&vect2::operator-=(const vect2 &other)
{
	x -= other.x;
	y -= other.y;
	return (*this);
}

vect2	vect2::operator*(const vect2 &other) const
{
	return (vect2(x * other.x, y * other.y));
}

vect2	&vect2::operator*=(const vect2 &other)
{
	x *= other.x;
	y *= other.y;
	return (*this);
}

vect2	vect2::operator*(int scale) const
{
	return (vect2(x * scale, y * scale));
}

vect2	&vect2::operator*=(int scale)
{
	x *= scale;
	y *= scale;
	return (*this);
}

vect2	&vect2::operator++()
{
	return (*this += vect2(1, 1));
}
vect2	&vect2::operator--()
{
	return (*this -= vect2(1, 1));
}
vect2	vect2::operator++(int)
{
	vect2	result(*this);
	++(*this);
	return (result);
}

vect2	vect2::operator--(int)
{
	vect2	result(*this);
	--(*this);
	return (result);
}

vect2	vect2::operator-() const
{
	return (vect2(-x, -y));
}

bool	vect2::operator==(const vect2 &other) const
{
	return (x == other.x && y == other.y);
}

bool	vect2::operator!=(const vect2 &other) const
{
	return (!(*this == other));
}

int	&vect2::operator[](int index)
{
	return (index == 0 ? x : y);
}

const int &vect2::operator[](int index) const
{
	return (index == 0 ? x : y);
}

std::ostream &operator<<(std::ostream &out, const vect2 &other)
{
	out << "{" << other.x << ", " << other.y << "}";
	return (out);
}
vect2	operator*(int scale, const vect2 &other)
{
	return (other * scale);
}
