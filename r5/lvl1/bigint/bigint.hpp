#ifndef	BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <sstream>
#include <cstdlib>

class	bigint
{
	public:
		std::string	_num;
		bigint();
		bigint(const bigint &other);
		bigint	&operator=(const bigint &other);
		~bigint();

		bigint(int num);
		bigint(std::string num);
		std::string non_0(std::string num);

		bigint	operator>>(int num) const;
		bigint	operator>>=(int num);
		bigint	operator>>(const bigint &other) const;
		bigint	operator>>=(const bigint &other);

		bigint	operator<<(int num) const;
		bigint	operator<<=(int num);
		bigint	operator<<(const bigint &other) const;
		bigint	operator<<=(const bigint &other);

		bigint	operator+(const bigint &other) const;
		bigint	operator+(int n) const;
		bigint	operator+=(const bigint &other);
		bigint	operator+=(int n);

		bool	operator<(const bigint &other) const;
		bool	operator>(const bigint &other) const;
		bool	operator<=(const bigint &other) const;
		bool	operator>=(const bigint &other) const;
		bool	operator==(const bigint &other) const;
		bool	operator!=(const bigint &other) const;

};

std::ostream	&operator<<(std::ostream &out, const bigint &other);

#endif