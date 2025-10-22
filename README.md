# bigint - Arbitrary-Precision Arithmetic

### 📝 Subject Summary
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

### 💡 Examples

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

### 📑 Files
- [x] [`bigint.hpp`](https://github.com/flmarsou/42nice-exam05/blob/main/bigint/bigint.hpp) - Header file
- [x] [`bigint.cpp`](https://github.com/flmarsou/42nice-exam05/blob/main/bigint/bigint.cpp) - Code file
- [x] [`bigint_commented.cpp`](https://github.com/flmarsou/42nice-exam05/blob/main/bigint/bigint_commented.cpp) - Code file (with explanations)
- [x] [`main.cpp`](https://github.com/flmarsou/42nice-exam05/blob/main/bigint/main.cpp) - Given main with debug couts


# vect2 - Vector 2D

### 📝 Subject Summary
The goal of this exercise is to create a simple **2D mathematical vector** class that supports basic arithmetic and comparison operations.

This exercise implements a **[vect2 class](https://github.com/flmarsou/42nice-exam05/blob/main/vect2/vect2.hpp)** that stores two integers (***x** and **y***) handling **indexing**, **arithmetics**, and **comparisons** through operators.
```cpp
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

// Maths
vect2	operator*(int scalar, const vect2 &other);

// Ostream
std::ostream	&operator<<(std::ostream &out, const vect2 &other);
```

### 💡 Examples

| Object        | Operation         | Result          |
| ------------- | ----------------- | --------------- |
| vect2(1, 2)   |                   | {1, 2}          |
| vect2(1, 2)   | ++vect2           | {2, 3}          |
| vect2(1, 2)   | vect2++           | {1, 2} -> {2, 3 |
| vect2(1, 2)   | + vect2(1, 2)     | {2, 4}          |
| vect2(1, 2)   | - vect2(1, 2)     | {0, 0}          |
| vect2(0, 0)   | - vect2(1, 2)     | {-1, -2}        |
| vect2(2, -3)  | * vect2(2, 2)     | {4, -6}         |
| vect2(69, 42) | == vect2(-69, 42) | false           |
| vect2(69, 42) | == vect2(69, 42)  | true            |
| vect2(69, 42) | != vect2(69, 42)  | false           |
| vect2(2, 0)   | -vect2            | {-2, 0}         |

### 📑 Files
- [x] [`vect2.hpp`](https://github.com/flmarsou/42nice-exam05/blob/main/vect2/vect2.hpp) - Header file
- [x] [`vect2.cpp`](https://github.com/flmarsou/42nice-exam05/blob/main/vect2/vect2.cpp) - Code file
- [x] [`main.cpp`](https://github.com/flmarsou/42nice-exam05/blob/main/vect2/main.cpp) - Given main with debug couts
