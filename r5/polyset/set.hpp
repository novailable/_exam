#pragma once

#include "searchable_bag.hpp"

class	set
{
	private:
		searchable_bag& _bag;
	public:
		set() = delete;
		set(const set &other) = delete;
		set	&operator=(const set &other) = delete;
		~set();

		set(searchable_bag &bag);

		void insert (int);
		void insert (int *, int);
		void print() const;
		void clear();

		bool has(int) const;
		searchable_bag&	get_bag() const;
};