# bigint - Arbitrary-Precision Arithmetic

## 📝 Subject Summary
In computer science, a **bignum** (*or **big integer***) represents an integer of **arbitrary precision**, capable of storing values larger than `SIZE_MAX` or `UINT64_MAX` without loss of precision when speed does.<br>
This is achieved by storing the number’s digits as a **string** (*or **array***), and performing manual arithmetic.<br>
Mostly used for when the speed of arithmetic is not a limiting factor.

This exercise implements a **[bigint class](https://github.com/flmarsou/42nice-exam05/blob/main/bigint/bigint.hpp)** that stores an unsigned integer as a string handling **additions**, **digit shifts**, and **comparisons** through operators.
```cpp
class	bigint
{
	public:
		bigint(unsigned int nbr = 0) : _big(std::to_string(nbr)) {};
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
```

## 💡 Examples

| Object      | Operation     | Result |
| ----------- | ------------- | ------ |
| bigint(21)  | + 21          | 42     |
| bigint(21)  | += bigint(21) | 42     |
| bigint(0)   | ++x           | 1      |
| bigint(0)   | x++           | 0 -> 1 |
| bigint(42)  | << 3          | 42000  |
| bigint(4)   | (x << 2) + 3  | 403    |
| bigint(0)   | (x << 2)      | 0      |
| bigint(0)   | (x << 2) + 3  | 3      |
| bigint(999) | >>= bigint(1) | 99     |
| bigint(999) | >>= bigint(2) | 9      |
| bigint(1)   | == bigint(1)  | true   |
| bigint(1)   | >= bigint(1)  | true   |
| bigint(9)   | < bigint(1)   | false  |

## 📑 Files
- [x] [`bigint.hpp`](https://github.com/flmarsou/42nice-exam05/blob/main/bigint/bigint.hpp) - Header file
- [x] [`bigint.cpp`](https://github.com/flmarsou/42nice-exam05/blob/main/bigint/bigint.cpp) - Code file
- [x] [`bigint_commented.cpp`](https://github.com/flmarsou/42nice-exam05/blob/main/bigint/bigint_commented.cpp) - Code file (with explanations)
- [x] [`main.cpp`](https://github.com/flmarsou/42nice-exam05/blob/main/bigint/main.cpp) - Given main with debug couts


# vect2 - Vector 2D
