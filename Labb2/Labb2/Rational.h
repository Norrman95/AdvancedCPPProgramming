#pragma once
#include<iostream>
#include "GCD.h"

template<typename Tint>
class Rational
{
public:
	Tint P, Q;

	friend std::ostream& operator<<(std::ostream & cout, Rational<Tint> R)
	{
		cout << R.P << "/" << R.Q;
		return cout;
	}
	friend std::istream& operator >> (std::istream & cin, Rational<Tint>& R)
	{
		cin >> R.P;
		cin >> R.Q;

		return cin;
	}

	Rational() : P(0), Q(1) {}
	Rational(Tint P) : P(P), Q(1) {}
	Rational(Tint PP, Tint QQ) : P(PP), Q(QQ)
	{
		if (Q < 0)
		{
			P = -P;
			Q = -Q;
		}
		Reduce(P, Q);
	}

	template<typename T>
	Rational(Rational<T>& rhs)
	{
		P = rhs.P;
		Q = rhs.Q;
	}

	template<typename T>
	Rational operator-(const Rational<T> rhs)
	{
		P = (P * rhs.Q) - (rhs.P * Q);
		Q = (Q * rhs.Q);
		Reduce(P, Q);

		return *this;
	}

	Rational operator=(const Rational rhs)
	{
		Q = rhs.Q;
		P = rhs.P;
		return *this;
	}

	template<typename T>
	friend bool operator==(const Rational<Tint> lhs, const Rational<T> rhs)
	{
		if (lhs.P == rhs.P && lhs.Q == rhs.Q)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template<typename T>
	Rational operator+=(const Rational<T>& rhs)
	{
		P = (P * rhs.Q) + (rhs.P * Q);
		Q = (Q * rhs.Q);
		Reduce(P, Q);

		return *this;
	}

	Rational operator+=(const int i)
	{
		P += i * Q;
		Reduce(P, Q);

		return *this;
	}

	Rational operator++()
	{
		P += 1 * Q;
		Reduce(P, Q);

		return *this;
	}

	Rational operator++(int)
	{
		Rational temp(*this);
		operator++();

		return temp;
	}


	template<typename T>
	Rational operator+(const Rational<T> rhs)
	{
		Rational temp(*this);

		return temp += rhs;
	}

	Rational operator+(const int i)
	{
		P += i * Q;

		return *this;
	}

	operator int()
	{
		return (P / Q);
	}
};

typedef Rational<short> Rshort;
typedef Rational<int> Rint;
typedef Rational<long long> RLL;