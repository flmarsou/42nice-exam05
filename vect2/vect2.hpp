#pragma once

# include <iostream>

class	vect2
{
	public:
		vect2(int x = 0, int y = 0) : _x(x), _y(y) {};
		vect2(const vect2 &other) : _x(other._x), _y(other._y) {};
		vect2	&operator=(const vect2 &other);

		// Accesses
		int	operator[](int index) const;
		int	&operator[](int index);

		// Increments & Decrements
		vect2	&operator++();		// ++x
		vect2	operator++(int);	// x++
		vect2	&operator--();		// --x
		vect2	operator--(int);	// x--

		// Maths
		vect2	operator+(const vect2 &other) const;
		vect2	&operator+=(const vect2 &other);

		vect2	operator-(const vect2 &other) const;
		vect2	&operator-=(const vect2 &other);

		vect2	operator*(int scalar) const;
		vect2	&operator*=(int scalar);

		// Unary Minus
		vect2	operator-() const;

		// Comparisons
		bool	operator==(const vect2 &other) const;
		bool	operator!=(const vect2 &other) const;

	private:
		int	_x;
		int	_y;
};

vect2	operator*(int scalar, const vect2 &other);

std::ostream	&operator<<(std::ostream &out, const vect2 &other);
