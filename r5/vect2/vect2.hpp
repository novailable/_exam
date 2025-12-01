#ifndef	VECT2_HPP
#define	VECT2_HPP

#include <iostream>

class	vect2
{
	public:
		int x;
		int y;
		vect2();
		vect2(const vect2 &other);
		~vect2();
		vect2(int x_, int y_);
		vect2	&operator=(const vect2 &other);

		vect2	operator+(const vect2 &other) const;
		vect2	&operator+=(const vect2 &other);

		vect2	operator-(const vect2 &other) const;
		vect2	&operator-=(const vect2 &other);

		vect2	operator*(const vect2 &other) const;
		vect2	&operator*=(const vect2 &other);
		vect2	operator*(int scale) const;
		vect2	&operator*=(int scale);

		vect2	&operator++();
		vect2	&operator--();
		vect2	operator++(int);
		vect2	operator--(int);
		vect2	operator-() const;

		bool	operator==(const vect2 &other) const;
		bool	operator!=(const vect2 &other) const;

		int	&operator[](int index);
		const int &operator[](int index) const;
};

std::ostream &operator<<(std::ostream &out, const vect2 &other);
vect2	operator*(int scale, const vect2 &other);

#endif
