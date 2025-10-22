#include "set.hpp"

bool	set::has(int value)
{
	return (_bag.has(value));
}

void	set::insert(int value)
{
	_bag.insert(value);
}

void	set::insert(int *arr, int size)
{
	_bag.insert(arr, size);
}

void	set::print() const
{
	_bag.print();
}

void	set::clear()
{
	_bag.clear();
}

const searchable_bag	&set::get_bag() const
{
	return (_bag);
}
