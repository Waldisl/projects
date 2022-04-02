#include "Scalar.hpp"

Scalar::Scalar() {}

Scalar::Scalar(const Scalar &) {}

Scalar::~Scalar() {}

Scalar &Scalar::operator=(const Scalar &second)
{
	if (this == &second)
		return (*this);
	return *this;
}

float Scalar::float_convert(double av)
{
	return (static_cast<float>(av));
}

double Scalar::double_convert(double av)
{
	return (static_cast<double>(av));
}

char Scalar::char_convert(double av)
{
	char c = static_cast<char>(av);
	if (std::isinf(av) || std::isnan(av))
		throw string("impossible");
	else if (c < 32 || c > 126)
		throw string("Non displayable");
	return (c);
}

int Scalar::int_convert(double av)
{
	int i = static_cast<int>(av);
	if (std::isinf(av) || std::isnan(av) || av > INT_MAX || av < INT_MIN)
		throw string("impossible");
	return (i);
}
