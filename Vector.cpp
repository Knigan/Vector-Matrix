#include "Vector.h"

//!!! Между функциями и классами оставляют как минимум 1 строку, чтобы код нормально читался

Vector::Vector() noexcept: n(0),arr(nullptr) {}

Vector::Vector(const int n) {
    if (n <= 0) 
        throw IncompatibleDimException("The size of the vector must be a positive integer number");
    this->n = n;
    arr = new double[n];
    
    for (int i = 0; i < n; i++) 
        arr[i]=0;
    //!!! Циклы и if-ы в одну строку - это боль для глаз...
}

Vector::Vector(const Vector &orig) noexcept {
    n=orig.n;
    arr=new double[n];
    for (int i=0; i<n; i++) arr[i]=orig.arr[i];
}

Vector::~Vector() noexcept {
    delete[] arr;
}

const double& Vector::operator[] (const int i) const {
    if (i < n && i >= 0) return arr[i];
    else throw OutOfRangeException();
}

double& Vector::operator[] (const int i) {
    if (i < n && i >= 0) return arr[i];
    else throw OutOfRangeException();
}

bool operator == (const Vector &a, Vector &b) {
    if (a.n != b.n) return false;
    for (int i = 0; i < a.n; ++i) {
        if (a.arr[i] != b.arr[i])
            return false;
    }
    return true;
}

Vector& Vector::operator = (const Vector &a) noexcept {
    if (a == *this) return *this;
    if (n!=a.n) {
        delete[] arr;
        n=a.n;
        arr=new double[n];
    }
    for(int i=0;i<n;i++) arr[i]=a.arr[i];
    return *this;
}

Vector& Vector::operator += (const Vector &a) {
    if (n != a.n) throw IncompatibleDimException("The sizes of the vectors must be equal");
    else for (int i=0;i<a.n;i++) arr[i]+=a.arr[i];
    return *this;
}

Vector& Vector::operator -= (const Vector &a) {
    if(n!=a.n) throw IncompatibleDimException ("The sizes of the vectors must be equal");
    else for(int i=0;i<a.n;i++) arr[i]-=a.arr[i];
    return *this;
}

const Vector& Vector::operator + () const noexcept {
    return *this;
}

Vector Vector::operator + (const Vector &a) const {
    if (n!=a.n) throw IncompatibleDimException ("The sizes of the vectors must be equal");
    Vector b(a);
    for(int i=0;i<n;i++) b.arr[i]+=arr[i];
    return b;
}

Vector Vector::operator - () const noexcept {
    Vector b(n);
    for(int i=0;i<n;i++) b.arr[i]=-arr[i];
    return b;
}

Vector Vector::operator - (const Vector &a) const {
    if(n!=a.n) throw IncompatibleDimException ("The sizes of the vectors must be equal");
    Vector b(*this);
    for(int i=0;i<n;i++) b.arr[i]-=a.arr[i];
    return b;
}

Vector Vector::operator * (const double num) const noexcept {
    Vector b(n);
    for(int i=0;i<n;i++) b.arr[i]=arr[i]*num;
    return b;
}

Vector operator * (const double num,const Vector &a) noexcept {
    Vector b(a.n);
    for(int i=0;i<a.n;i++) b.arr[i]=a.arr[i]*num;
    return b;
}

const double Vector::operator * (const Vector &a) const {
    if (n!=a.n) throw IncompatibleDimException ("The sizes of the vectors must be equal");
    double res=0;
    for(int i=0;i<n;i++) res+=arr[i]*a.arr[i];
    return res;
}

Vector Vector::operator * (const CSLRMatrix &a) const {
    if (n != a.size) throw IncompatibleDimException ("The size of the matrix must be equal the size of the vector");
    int count = 0;
    bool b;
    Vector result(n);
    for (int i = 0; i < n; ++i) {
        double ans = 0;
        for (int j = 0; j < n; ++j) {
            b = true;
            if (i < j) {
                for (int k = 0; k < a.iptr[j + 1] - a.iptr[j]; ++k) {
                    if (a.jptr[a.iptr[j] + k] == i) {
                        ans += arr[j] * a.altr[a.iptr[j] + k];
                        b = false;
                    }
                }
            }
            if (i == j) ans += arr[i] * a.adiag[i];
            else if (i > j && j == a.jptr[count] && count < a.iptr[i + 1]) {
                ans += arr[j] * a.altr[count];
                ++count;
            }
        }
        result.arr[i] = ans;
    }
    return result;
}

const double Vector::length() const noexcept {
    double sum=0;
    for(int i=0;i<n;i++) sum+=arr[i]*arr[i];
    return sqrt(sum);
}

const int Vector::dim() const noexcept {
    return n;
}

Vector::operator double*() const noexcept {
    return arr;
}

std::ostream& operator << (std::ostream &out,const Vector &a) noexcept {
    out<<"[";
    out<<std::fixed;
    for(int i=0;i<a.n;i++) {
        if(i<a.n-1) out<<std::setprecision(3)<<a.arr[i]<<", ";
        else out<<std::setprecision(3)<<a.arr[i]<<"]\n";
    }
    return out;
}

std::istream& operator >> (std::istream &in,Vector &a) noexcept {
    int n;
    std::cout << "Input the size of the vector\n";
    std::cin >> n;
    std::cout << "Input the vector\n";
    if (n != a.n) {
        delete []a.arr;
        a.n = n;
        a.arr = new double[n];
    }
    for(int i = 0; i < a.n; ++i) 
        in >> a.arr[i];
    return in;
}