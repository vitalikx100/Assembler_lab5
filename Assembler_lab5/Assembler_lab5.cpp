#include <iostream>

using namespace std;

int main()
{
	double a, b, d;
	double c1 = 1.0;
	double c_4 = -4;
	double c_153 = -153;
	double x = 0;
	int error = 0;

	cout << "Input a, b, d: ";
	cin >> a >> b >> d;
	_asm
	{
		;Вторая скобка
		finit;
		fld a; st(0) = a
		fmul b; st(0) = a * b
		fadd c1; st(0) = a * b + 1
		fldz;st(0) = 0, st(1) = a * b + 1
 		fcomp; st(0) = a * b + 1
		fnstsw AX
		sahf; загружаем флаги из регистра AH
		jz error_0


		;Первая скобка
		fld c_153; st(0) = -153; st(1) = a * b + 1
		fld b; st(0) = b; st(1) = -153; st(2) = a * b + 1
		fldz; st(0) = 0; st(1) = b; st(2) = -153; st(3) = a * b + 1
		fcomp; st(0) = b; st(1) = -153; st(2) = a * b + 1
		fnstsw AX
		sahf
		jz error_0
		fdivp st(1), st; st(0) = -153 / b; st(1) = a * b + 1
		fld a; st(0) = a; st(1) = -153 / b; st(2) = a * b + 1
		fmul c_4; st(0) = -4 * a; st(1) = -153 / b; st(2) = a * b + 1
		fadd d; st(0) = -4 * a + d; st(1) = -153 / b; st(2) = a * b + 1
		faddp st(1), st; st(0) = -4 * a + d - 153 / b; st(1) = a * b + 1
		

		fdiv st, st(1); st(0) = (-4 * a + d - 153 / b) / (a * b + 1)

		fstp x; x = (-4 * a + d - 153 / b) / (a * b + 1)

		test ax, 1
		jnz error_io

		jmp end_if

		error_0 :
			mov error, 1
			jmp end_if

		error_io :
			mov error, 2
			jmp end_if

		end_if :
	}
	if (error == 1) cout << "Division by zero";
	if (error == 2) cout << "Invalid operation";
	if (error == 0) 
	{
		cout <<"asm: " << x << endl;
		cout <<"C++: " << (double)(-153 / b + d - 4 * a) / (1 + a * b);
	}
	

	return 0;
}
