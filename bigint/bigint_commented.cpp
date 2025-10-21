#include "bigint.hpp"

// ========================================================================== //
//     Additions                                                              //
// ========================================================================== //

/**
 * Addition assignment operator (x += y)
 * Adds another bigint to the current bigint.
 * 
 * Steps:
 * 1. Initialize carry to 0 (carry is the overflows when sum exceeds 9)
 * 2. `i` and `j` are start from the least significant digit (rightmost) digit of both bigints
 * 3. Loop while there are digits left in either bigint or a carry exists:
 *    a. Get the current digit from each bigint (or 0 if index is out of bound)
 *    b. Add the digit together with the carry
 *    c. Update the carry for the next iteration (sum / 10)
 *    d. Append the current digit of the sum (sum % 10) to the result string
 *    e. Move to the next more significant digit
 * 4. Reverse the result string since digits were added from least significant to most
 * 5. Update the current bigint
 * 6. Return the updated bigint
 */
bigint	&bigint::operator+=(const bigint &other)
{
	int	carry = 0;
	int	i = _big.size() - 1;
	int	j = other._big.size() - 1;

	std::string	result;

	while (i >= 0 || j >= 0 || carry)
	{
		int	currentDigit = i >= 0 ? _big[i] - '0' : 0;
		int	otherDigit = j >= 0 ? other._big[j] - '0' : 0;
		int	sum = currentDigit + otherDigit + carry;
		carry = sum / 10;
		result.push_back((sum % 10) + '0');
		--i;
		--j;
	}

	std::reverse(result.begin(), result.end());
	_big = result;

	return (*this);
}

/**
 * Addition operator (x + y)
 * Returns a new bigint that is the sum of the current bigint and 'other'.
 * 
 * Steps:
 * 1. Make a copy of the current bigint
 * 2. Apply the addition assignement operator to the copy
 * 3. Return the copy
 */
bigint	bigint::operator+(const bigint &other) const
{
	bigint	copy(*this);
	copy += other;
	return (copy);
}

// ========================================================================== //
//     Increments                                                             //
// ========================================================================== //

/**
 * Pre-increment operator (++x)
 * Immediately increases the current bigint by 1 and returns a reference to the updated object.
 * 
 * Steps:
 * 1. Create a dummy bigint with value 1
 * 2. Add it to the current bigint
 * 3. Return the updated bigint
 */
bigint	&bigint::operator++()
{
	bigint	dummy(1);
	*this += dummy;
	return (*this);
}

/**
 * Post-increment operator (x++)
 * Returns a copy of the current bigint, then increments the original object by 1.
 * 
 * Steps:
 * 1. Create a dummy bigint with value 1
 * 2. Create a copy of the current bigint
 * 3. Add the dummy bigint to the current bigint
 * 4. Return the copy
 */
bigint	bigint::operator++(int)
{
	bigint	dummy(1);
	bigint	copy(*this);
	*this += dummy;
	return (copy);
}

// ========================================================================== //
//     Shifts                                                                 //
// ========================================================================== //

/**
 * Left-Shift assignment operator (x <<= n)
 * Multiplies the current bigint by 10^amount by appending 0's at the end.
 * 
 * Steps:
 * 1. Check if the current bigint is not zero (we don't add zeros if it's already zero)
 * 2. Append '0' characters equal to the shift amount
 * 3. Return the updated bigint
 */
bigint	&bigint::operator<<=(unsigned int amount)
{
	if (_big != "0")
		_big.append(amount, '0');
	return (*this);
}

/**
 * Left-shift operator (x << n)
 * Returns a new bigint that is the current bigint multiplied by 10^amount
 * 
 * Steps:
 * 1. Make a copy of the current bigint
 * 2. Apply the left-shift assignment to the copy
 * 3. Return the copy
 */
bigint	bigint::operator<<(unsigned int amount) const
{
	bigint	copy(*this);
	copy <<= amount;
	return (copy);
}

/**
 * Right-shift assignment operator (x >>= other)
 * Divides the current bigint by 10^other, discarding the remainder.
 * 
 * Steps:
 * 1. Convert 'other' bigint to an unsigned long to determine shift amount
 * 2. If current bigint size is GREATER or EQUAL to the shift amount, erase the last 'amount' digit
 * 3. Otherwise reset the current bigint to zero
 * 4. Return the updated bigint
 */
bigint	&bigint::operator>>=(const bigint &other)
{
	const unsigned int	size = _big.size();
	const unsigned long	amount = std::atol(other._big.c_str());

	size >= amount
		? _big.erase(size - amount)
		: _big = "0";

	return (*this);
}

// ========================================================================== //
//     Comparisons                                                            //
// ========================================================================== //

/**
 * Less-than operator (x < y)
 * Compares two bigints numerically.
 * 
 * Steps:
 * 1. If the sizes (number of digits) are different, the smaller size is the smaller bigint
 * 2. If sizes are equal, compare the string representations lexicographically
 * 3. Return true if the current bigint is less than 'other', false otherwise
 */
bool	bigint::operator<(const bigint &other) const
{
	return (_big.size() != other._big.size())
		? _big.size() < other._big.size()
		: _big < other._big;
}

/**
 * Greater-than operator (x > y)
 * Returns true if the current bigint is greater than 'other'.
 * 
 * Note: Implemented re-using the less-than operator in reverse.
 */
bool	bigint::operator>(const bigint &other) const { return (other < *this); }

/**
 * Less-than-or-equal operator (x <= y)
 * Returns true if the current bigint is less than or equal to 'other'.
 * 
 * Note: Implemented re-using negation of the greater-than operator in reverse.
 */
bool	bigint::operator<=(const bigint &other) const { return !(*this > other); }

/**
 * Greater-than-or-equal operator (x >= y)
 * Returns true if the current bigint is greater than or equal to 'other'.
 * 
 * Note: Implemented re-using negation of the less-than operator.
 */
bool	bigint::operator>=(const bigint &other) const { return !(*this < other); }

/**
 * Equality operator (x == y)
 * Returns true if the current bigint has the same value as 'other'.
 */
bool	bigint::operator==(const bigint &other) const { return (_big == other._big); }

/**
 * Inequality operator (x != y)
 * Returns true if the current bigint has a different value from 'other'.
 */
bool	bigint::operator!=(const bigint &other) const { return (_big != other._big); }

// ========================================================================== //
//     Ostream                                                                //
// ========================================================================== //

std::ostream	&operator<<(std::ostream &out, const bigint &other)
{
	out << other.getBig();
	return (out);
}
