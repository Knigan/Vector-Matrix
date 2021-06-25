#pragma once
#include "CSLRMatrix.h"
#include "Exception.h"
#include <iostream>
#include <iomanip>
class Vector {
	friend class CSLRMatrix;
private:
	int n;
	double *arr;
public:
	Vector() noexcept;
	explicit Vector(const int n); //!!! Запретить неявные преобразования (НЕ ИСПРАВЛЕНО)
	Vector(const Vector& orig) noexcept;
	~Vector() noexcept;
	double& operator [] (const int i);
	const double& operator [] (const int i) const;
	friend bool operator == (const Vector& a, Vector& b);
	Vector& operator = (const Vector &a) noexcept;
	Vector& operator += (const Vector &a);
	Vector& operator -= (const Vector &a);
	const Vector& operator + () const noexcept;
	Vector operator + (const Vector &a) const;
	Vector operator - () const noexcept;
	Vector operator - (const Vector &a) const;
	Vector operator * (const double num) const noexcept;
	friend Vector operator * (const double num,const Vector &a) noexcept;
	const double operator * (const Vector &a) const;
	Vector operator * (const CSLRMatrix &a) const;
	explicit operator double*() const noexcept;          //!!! Запретить неявные преобразования (НЕ ИСПРАВЛЕНО)
	friend std::ostream& operator << (std::ostream& out,const Vector &a) noexcept;
	friend std::istream& operator >> (std::istream& in,Vector &a) noexcept;
	const double length() const noexcept;
	const int dim() const noexcept;
};