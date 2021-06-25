#include "Vector.h"
#include "CSLRMatrix.h"
using namespace std;

void VectorTest() {
	try {
		Vector a,b;
		cout<<"The first vector:\n";
		cin >> a;
		cout << "The second vector:\n";
		cin >> b;
		cout << "+a = " << +a << endl;
		cout << "-a = " << -a << endl;
		cout<<"a + b = "<< a + b << endl;
		cout << "a - b = " << a - b << endl;
		cout << "a * b = " << a * b << endl;
		cout << "a * 2 = " << a * 2 << endl;
		cout << "2 * a = " << 2 * a << endl;
		Vector c;
		cout << "The third vector:\n";
		cin >> c;
		c += (a+b);
		cout << "c + (a + b) = " << c;
		c -= 2*(a+b);
		cout << "c - (a + b) = " << c;
		cout << "Address of the vector c is equal " << (double*) c << endl;
		c = (a*b)*(a+b);
		cout << "c := (a*b)*(a+b) = " << c << endl;
		cout << "length of c = " << c.length() << endl;
		cout << "dimension of c = " << c.dim() << endl;
	}
	catch (exception &error) {
		cout << error.what() << endl;
		system("pause");
		return;
	}
	system("pause");
}

void MatrixTest() {
	try {
		CSLRMatrix a;
		cin >> a;
		cout << "The size of the matrix is " << a.dim() << endl;
		cout << "The quantity of the nonzero elements in the matrix is " << a.zeroqnt() << endl;
		double number;
		cout << "Input the number\n";
		cin >> number;
		cout << "A * number = \n" << a * number << endl;
		cout << "number * A = \n" << number * a << endl;
		Vector b;
		cin >> b;
		cout << "b * A = " << b * a << endl;
		cout << "A * b = " << a * b << endl;
	}
	catch (exception &error) {
		cout << error.what() << endl;
		system("pause");
		return;
	}
	system("pause");
}

void main() {
	VectorTest();
	MatrixTest();
	try {
		Vector a(1);
		a[-1];
	}
	catch (exception &error) {
		cout << error.what() << endl;
	}
	system("pause");
}