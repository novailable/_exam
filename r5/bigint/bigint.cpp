#include "bigint.hpp"

bigint::bigint() : _num("0") {}

bigint::bigint(const bigint &other) : _num(other._num) {}

bigint	&bigint::operator=(const bigint &other)
{
	if (this != &other)
		_num = other._num;
	return (*this);
}

bigint::~bigint() {}

bigint::bigint(std::string num) : _num(non_0(num)) {}

bigint::bigint(int num)
{
	std::stringstream	ss;
	ss << num;
	ss >> _num;
	non_0(_num);
}

std::string bigint::non_0(std::string num)
{
	size_t	i = 0;
	if (num.empty() || num.size() == 1)
		return num;
	while (i < num.size() - 1)
	{
		if (num[i] != '0')
			break;
		i++;
	}
	num.erase(0, i);
	_num = num;
	return (num);
}

std::ostream	&operator<<(std::ostream &out, const bigint &other)
{
	out << other._num;
	return (out);
}

bigint	bigint::operator>>(int num) const
{
	std::string	result = _num;
	if (num >= (int)result.size())
		return (bigint("0"));
	result.erase(result.size() - num);
	return (bigint(result));
}

bigint	bigint::operator>>=(int num)
{
	*this = (*this >> num);
	return (*this);
}

bigint	bigint::operator>>(const bigint &other) const
{
	size_t	o_size = other._num.size();
	size_t size = 0;
	if (o_size > _num.size() || o_size > 18)
		return (bigint("0"));
	for (size_t i = 0; i < o_size; ++i)
		size = size * 10 + (other._num[i] - '0');
	return (*this >> size);
}

bigint	bigint::operator>>=(const bigint &other)
{
	*this = (*this >> other);
	return (*this);
}

bigint	bigint::operator+(const bigint &other) const
{
	int osize = other._num.size() - 1;
	int tsize = _num.size() - 1;
	std::string result;
	int carry = 0;

	while (osize >= 0 || tsize >= 0 || carry)
	{
		int sum = carry;
		if (osize >= 0) sum += other._num[osize--] - '0';
		if (tsize >= 0) sum += _num[tsize--] - '0';
		carry = sum / 10;
		result.push_back(sum % 10 + '0');
	}
	std::reverse(result.begin(), result.end());
	return (bigint(result));
}

bigint	bigint::operator+(int n) const
{
	return (*this + bigint(n));
}

bigint	bigint::operator+=(const bigint &other)
{
	*this = *this + other;
	return (*this);
}

bigint	bigint::operator+=(int n)
{
	*this += bigint(n);
	return (*this);
}

bigint	bigint::operator<<(int num) const
{
	if (num <= 0)
		return (*this);
	return (bigint(_num + std::string(num, '0')));
}

bigint	bigint::operator<<=(int num)
{
	*this = (*this << num);
	return (*this);
}

bigint	bigint::operator<<(const bigint &other) const
{
	size_t	o_size = other._num.size();
	size_t size = 0;
	if (o_size > _num.size() || o_size > 18)
		return (bigint("0"));
	for (size_t i = 0; i < o_size; ++i)
		size = size * 10 + (other._num[i] - '0');
	return (*this << size);
}

bigint	bigint::operator<<=(const bigint &other)
{
	*this = (*this << other);
	return (*this);
}

bool	bigint::operator<(const bigint &other) const
{
	size_t	a = _num.size(), b = other._num.size();
	if (a != b)
		return (a < b);
	return (_num < other._num);
}

bool	bigint::operator>(const bigint &other) const
{
	return (other < *this);
}

bool	bigint::operator<=(const bigint &other) const
{
	return !(*this > other);
}

bool	bigint::operator>=(const bigint &other) const
{
	return !(*this < other);
}

bool	bigint::operator==(const bigint &other) const
{
	return (_num == other._num);
}

bool	bigint::operator!=(const bigint &other) const
{
	return !(*this == other);
}