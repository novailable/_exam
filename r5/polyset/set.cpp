#include "set.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"

// set::set() : _bag(new searchable_array_bag()) {}
// set::set(const set &other) : _bag(0) 
// {
// 	if (const searchable_array_bag *arr = dynamic_cast<const searchable_array_bag *>(other._bag))
// 		_bag = new searchable_array_bag(*arr);
// 	else if (const searchable_tree_bag *t = dynamic_cast<const searchable_tree_bag *>(other._bag))
// 		_bag = new searchable_tree_bag(*t);
// 	else
// 		_bag = new searchable_array_bag();
// }

// set	&set::operator=(const set &other)
// {
// 	if (this != &other)
// 	{
// 		delete	_bag;
// 		if (const searchable_array_bag *arr = dynamic_cast<const searchable_array_bag *>(other._bag))
// 			_bag = new searchable_array_bag(*arr);
// 		else if (const searchable_tree_bag *t = dynamic_cast<const searchable_tree_bag *>(other._bag))
// 			_bag = new searchable_tree_bag(*t);
// 		else
// 			_bag = new searchable_array_bag();
// 	}
// 	return (*this);
// }

set::~set()
{
	//  if (dynamic_cast<searchable_array_bag*>(_bag))
    //     delete dynamic_cast<searchable_array_bag*>(_bag);
    // else if (dynamic_cast<searchable_tree_bag*>(_bag))
    //     delete dynamic_cast<searchable_tree_bag*>(_bag);
}

set::set(searchable_bag &bag) : _bag(bag)
{
}

void set::insert (int value)
{
	if (!this->has(value))
		_bag.insert(value);
}

void set::insert (int *array, int size)
{
	for (int i = 0; i < size; ++i)
		this->insert(array[i]);
}

void set::print() const
{
	_bag.print();
}
void set::clear()
{
	_bag.clear();
}
bool set::has(int value) const
{
	return (_bag.has(value));
}

searchable_bag& set::get_bag() const { return _bag;}
