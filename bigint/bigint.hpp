#pragma once

# include <iostream>
# include <algorithm>

class	bigint
{
	public:
		bigint() : _big("0") {};
		bigint(unsigned int nbr) : _big(std::to_string(nbr)) {};
		bigint(const bigint &other) : _big(other._big) {};

		std::string	getBig() const { return (_big); };

		// Additions
		bigint	operator+(const bigint &other) const;
		bigint	&operator+=(const bigint &other);

		// Increments
		bigint	&operator++();		// ++x
		bigint	operator++(int);	// x++

		// Shifts
		bigint	operator<<(unsigned int amount) const;
		bigint	&operator<<=(unsigned int amount);
		bigint	&operator>>=(const bigint &other);

		// Comparisons
		bool	operator<(const bigint &other) const;
		bool	operator>(const bigint &other) const;
		bool	operator<=(const bigint &other) const;
		bool	operator>=(const bigint &other) const;
		bool	operator==(const bigint &other) const;
		bool	operator!=(const bigint &other) const;

	private:
		std::string	_big;
};

// Ostream
std::ostream	&operator<<(std::ostream &out, const bigint &other);
