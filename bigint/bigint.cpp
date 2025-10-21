#include "bigint.hpp"

bigint	&bigint::operator+=(const bigint &other)
{
	int	carry = 0;
	int	i = _big.size() - 1;
	int	j = other._big.size() - 1;

	std::string	result;

	while (i >= 0 || j >= 0 || carry)
	{
		int	x = i >= 0 ? _big[i] - '0' : 0;
		int	y = j >= 0 ? other._big[j] - '0' : 0;
		int	sum = x + y + carry;
		carry = sum / 10;
		result.push_back((sum % 10) + '0');
		--i;
		--j;
	}

	std::reverse(result.begin(), result.end());
	_big = result;

	return (*this);
}

bigint	bigint::operator+(const bigint &other) const
{
	bigint	result(*this);
	result += other;
	return (result);
}

bigint	&bigint::operator++()
{
	bigint	dummy(1);
	*this += dummy;
	return (*this);
}

bigint	bigint::operator++(int)
{
	bigint	dummy(1);
	bigint	tmp(*this);
	*this += dummy;
	return (tmp);
}

bigint	&bigint::operator<<=(unsigned int amount)
{
	if (_big != "0")
		_big.append(amount, '0');
	return (*this);
}

bigint	bigint::operator<<(unsigned int amount) const
{
	bigint	result(*this);
	result <<= amount;
	return (result);
}

bigint	&bigint::operator>>=(const bigint &other)
{
	const unsigned int	size = _big.size();
	const unsigned long	amount = std::atol(other._big.c_str());

	size >= amount
		? _big.erase(size - amount)
		: _big = "0";

	return (*this);
}

bool	bigint::operator<(const bigint &other) const
{
	return (_big.size() != other._big.size())
		? _big.size() < other._big.size()
		: _big < other._big;
}
bool	bigint::operator>(const bigint &other) const { return (other < *this); }
bool	bigint::operator<=(const bigint &other) const { return !(*this > other); }
bool	bigint::operator>=(const bigint &other) const { return !(*this < other); }
bool	bigint::operator==(const bigint &other) const { return (_big == other._big); }
bool	bigint::operator!=(const bigint &other) const { return (_big != other._big); }

std::ostream	&operator<<(std::ostream &out, const bigint &other)
{
	out << other.getBig();
	return (out);
}
