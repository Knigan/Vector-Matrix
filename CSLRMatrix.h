#pragma once
#include "Vector.h"
#include "Exception.h"
#include <iostream>
#include <iomanip>

class CSLRMatrix {
	friend class Vector;
private:
	int size,nzero;
	double *adiag,*altr;
	int *jptr,*iptr;
public:
	CSLRMatrix () noexcept;

	CSLRMatrix (const int size, const int nzero);

	CSLRMatrix (const int size, const int nzero, const double *adiag, const double *altr,
	const double *autr, const int *jptr, const int *iptr);

	CSLRMatrix (const CSLRMatrix &orig) noexcept;

	CSLRMatrix& operator = (const CSLRMatrix& a) noexcept;

	~CSLRMatrix();

	CSLRMatrix operator * (const double num) const noexcept;

	friend CSLRMatrix operator * (const double num,const CSLRMatrix &a) noexcept;

	Vector operator * (const Vector &a) const;

	const int dim() const noexcept;

	const int zeroqnt() const noexcept;

	friend std::ostream& operator << (std::ostream& out,const CSLRMatrix &a) noexcept;

	friend std::istream& operator >> (std::istream& in,CSLRMatrix &a) noexcept;
};