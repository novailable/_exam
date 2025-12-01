#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() : tree_bag() {}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &other) : tree_bag(other) {}
searchable_tree_bag	&searchable_tree_bag::operator=(const searchable_tree_bag &other) { 
	tree_bag::operator=(other);
	return (*this);
}

searchable_tree_bag::~searchable_tree_bag() {};

bool	searchable_tree_bag::has(int value) const
{
	node *cur = tree;
	while (cur)
	{
		if (value == cur->value)
			return true;
		else if (value > cur->value)
			return (cur = cur->r);
		else if (value < cur->value)
			return (cur = cur->l);
	}
	return false;
}