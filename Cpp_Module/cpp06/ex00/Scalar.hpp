#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <climits>

using std::exception;
using std::cout;
using std::endl;
using std::string;

class Scalar
{
	public:
		Scalar();
		Scalar(const Scalar &);
		Scalar& operator=(const Scalar& second);
		~Scalar();

		float	float_convert(double);
		double	double_convert(double);
		char	char_convert(double);
		int		int_convert(double);

};
