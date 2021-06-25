#include "CSLRMatrix.h"

CSLRMatrix::CSLRMatrix() noexcept: size(0), nzero(0), adiag(nullptr), altr(nullptr), jptr(nullptr), iptr(nullptr) {}

CSLRMatrix::CSLRMatrix (const int size, const int nzero): size(size), nzero(nzero) {
    if (size <= 0) throw IncompatibleDimException ("The size of the matrix must be a positive integer number");

    this->adiag = new double[size];
    for (int i = 0; i < size; ++i) adiag[i]=0;

    this->altr = new double[nzero];
    this->jptr = new int[nzero];
    for (int i = 0; i < nzero; ++i) altr[i]=jptr[i]=0;

    this->iptr = new int[size + 1];
    for (int i = 0; i < size + 1; ++i) iptr[i] = 0;
}

CSLRMatrix::CSLRMatrix(
    const int     size,
    const int     nzero,
    const double *adiag, 
    const double *altr, 
    const double *autr,
    const int    *jptr, 
    const int    *iptr): size(size), nzero(nzero) 
{
    if (size <= 0) throw IncompatibleDimException ("The size of the matrix must be a positive integer number");

    this->adiag = new double[size];
    for (int i = 0; i < size; ++i) this->adiag[i] = adiag[i];

    this->altr = new double[nzero];
    this->jptr = new int[nzero];

    for (int i = 0; i < nzero; ++i) {
        this->altr[i] = altr[i];
        this->jptr[i] = jptr[i];
    }

    this->iptr = new int[size+1];
    for (int i = 0; i < size + 1; ++i) this->iptr[i] = iptr[i];
}

CSLRMatrix::CSLRMatrix (const CSLRMatrix &orig) noexcept: size(orig.size), nzero(orig.nzero) {
    adiag = new double[orig.size];
    for (int i = 0; i < size; ++i) adiag[i] = orig.adiag[i];

    altr = new double[orig.nzero];
    for (int i = 0; i < nzero; ++i) altr[i] = orig.altr[i];

    jptr = new int[orig.nzero];
    for (int i = 0; i < nzero; ++i) jptr[i] = orig.jptr[i];

    iptr = new int[orig.size + 1];
    for (int i = 0; i < size + 1; ++i) iptr[i] = orig.iptr[i];
}

CSLRMatrix::~CSLRMatrix() {
    delete[] adiag;
    delete[] altr;
    delete[] jptr;
    delete[] iptr;
}

CSLRMatrix& CSLRMatrix::operator = (const CSLRMatrix &a) noexcept {
    if (size != a.size || nzero != a.nzero) {
        delete []adiag;
        delete []altr;
        delete []jptr;
        delete []iptr;

        size = a.size;
        nzero = a.nzero;

        adiag = new double[size];
        altr = new double[nzero];
        jptr = new int[nzero];
        iptr = new int[size+1];
    }
    for (int i = 0; i < size; ++i) adiag[i] = a.adiag[i];
    for (int i = 0; i < nzero; ++i) altr[i] = a.altr[i];
    for (int i = 0; i < nzero; ++i) jptr[i] = a.jptr[i];
    for (int i = 0; i < size + 1; ++i) iptr[i] = a.iptr[i];

    return *this;
}

CSLRMatrix CSLRMatrix::operator * (const double num) const noexcept{
    CSLRMatrix b(*this);
    
    for(int i=0; i<nzero; i++) b.altr[i] *= num;
    
    for(int i=0; i<size; i++)
        b.adiag[i] *= num;
        
    return b;
}

CSLRMatrix operator * (const double num,const CSLRMatrix &a) noexcept{
    CSLRMatrix b(a);
    for(int i=0; i<a.nzero; i++) b.altr[i] *= num;
    
    for(int i=0; i<a.size; i++)
        b.adiag[i] *= num;
        
    return b;
}

Vector CSLRMatrix::operator * (const Vector &a) const {
    if (a.n != size) throw IncompatibleDimException ("The size of the vector must be equal the size of the matrix");
    Vector result(size);
    for (int i = 0; i < size; ++i) result.arr[i] = a.arr[i] * adiag[i];
    for (int i = 0; i < size; ++i) {
        for (int j = iptr[i]; j < iptr[i+1]; ++j) {
            result.arr[i] += a.arr[jptr[j]]*altr[j];
            result.arr[jptr[j]] += a.arr[i]*altr[j];
        }
    }
    return result;
}

const int CSLRMatrix::dim() const noexcept{
    return size;
}
const int CSLRMatrix::zeroqnt() const noexcept {
    return nzero;
}

std::ostream& operator << (std::ostream& out,const CSLRMatrix &a) noexcept {
    int count = 0;
    bool b;
    for (int i = 0; i < a.size; ++i) {
        for (int j = 0; j < a.size; ++j) {
            b = true;
            if (i < j) {
                for (int k = 0; k < a.iptr[j + 1] - a.iptr[j]; ++k) {
                    if (i == a.jptr[a.iptr[j] + k]) {
                        out << std::setw(6) << a.altr[a.iptr[j] + k] << " ";
                        b = false;
                    }
                }
            }
            if (i == j) out << std::setw(6) << a.adiag[i] << " ";
            else {
                if (i > j && j == a.jptr[count] && count < a.iptr[i + 1]) {
                    out << std::setw(6) << a.altr[count] << " ";
                    ++count;
                }
                else if (b) out << std::setw(6) << 0 << " ";
            }
        }
        out<<std::endl;
    }
    return out;
}

std::istream& operator >> (std::istream &in, CSLRMatrix &a) noexcept {
    int size, nzero;
    std::cout << "Input the size of the matrix and the quantity of nonzero elements under the main diagonal\n";
    std::cin >> size >> nzero;
    if (size != a.size || nzero != a.nzero) {
        delete []a.adiag;
        delete []a.altr;
        delete []a.jptr;
        delete []a.iptr;
        a.size = size;
        a.nzero = nzero;
        a.adiag = new double[size];
        a.altr = new double[nzero];
        a.jptr = new int[nzero];
        a.iptr = new int[size+1];
    }
    int kl=0;
    a.iptr[0] = 0;
    for (int i = 0; i < a.size; ++i) {
        int temp = kl;
        for (int j = 0; j < a.size; ++j) {
            double x;
            in>>x;
            if (i == j) a.adiag[i] = x;
            if (i > j && x != 0) {
                a.altr[kl] = x;
                a.jptr[kl] = j;
                ++kl;
            }
        }
        a.iptr[i + 1] = a.iptr[i] + kl - temp;
    }
    return in;
}