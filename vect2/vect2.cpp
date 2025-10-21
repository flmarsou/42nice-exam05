#include "vect2.hpp"

vect2	&vect2::operator=(const vect2 &other)
{
	if (this != &other)
	{
		_x = other._x;
		_y = other._y;
	}
	return (*this);
}

int	vect2::operator[](int index) const { return index == 0 ? _x : _y; }
int	&vect2::operator[](int index) { return index == 0 ? _x : _y; }

vect2	&vect2::operator++()
{
	++_x;
	++_y;
	return (*this);
}

vect2	vect2::operator++(int)
{
	vect2	copy(*this);
	++_x;
	++_y;
	return (copy);
}

vect2	&vect2::operator--()
{
	--_x;
	--_y;
	return (*this);
}

vect2	vect2::operator--(int)
{
	vect2	copy(*this);
	--_x;
	--_y;
	return (copy);
}

vect2	vect2::operator+(const vect2 &other) const
{
	vect2	copy(*this);
	copy._x += other._x;
	copy._y += other._y;
	return (copy);
}

vect2	&vect2::operator+=(const vect2 &other)
{
	_x += other._x;
	_y += other._y;
	return (*this);
}

vect2	vect2::operator-(const vect2 &other) const
{
	vect2	copy(*this);
	copy._x -= other._x;
	copy._y -= other._y;
	return (copy);
}

vect2	&vect2::operator-=(const vect2 &other)
{
	_x -= other._x;
	_y -= other._y;
	return (*this);
}

vect2	vect2::operator*(int scalar) const
{
	vect2	copy(*this);
	copy._x *= scalar;
	copy._y *= scalar;
	return (copy);
}

vect2	&vect2::operator*=(int scalar)
{
	_x *= scalar;
	_y *= scalar;
	return (*this);
}

vect2	vect2::operator-() const
{
	vect2	copy(*this);
	copy._x = -copy._x;
	copy._y = -copy._y;
	return (copy);
}

bool	vect2::operator==(const vect2 &other) const { return (_x == other._x && _y == other._y); }
bool	vect2::operator!=(const vect2 &other) const { return (_x != other._x || _y != other._y); }

vect2	operator*(int scalar, const vect2 &other)
{
	vect2	copy(other);
	copy *= scalar;
	return (copy);
}

std::ostream	&operator<<(std::ostream &out, const vect2 &other)
{
	out << "{" << other[0] << ", " << other[1] << "}";
	return (out);
}
