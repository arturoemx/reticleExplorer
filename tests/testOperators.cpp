#include <iostream>
#include <geomFeatures.h>
#include <drawingFeatures.h>

using namespace std;
using namespace gfeat;

int main()
{
	vec2D A(3,4), B(5,6), C;

	cout << A <<"+" << B << "=" << A+B << endl;
	cout << A <<"-" << B << "=" << A-B << endl;
	cout << A <<"+" << 5. << "=" << A+(float)5. << endl;
	cout << A <<"-" << 3. << "=" << A-3. << endl;

	C = A;
	A+=5;
	cout << C << "+= 5 => " << A << endl;

	C = A;
	A-=12;
	cout << C << "-= 12 => " << A << endl;
	
	C = A;
	A*=2;
	cout << C << "*= 2 => " << A << endl;
	
	C = A;
	A/=4;
	cout << C << "/= 4 => " << A << endl;
	
	cout << endl;

	return 0;
}