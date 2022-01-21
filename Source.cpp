#include "PolishNotation.h"

int main()
{
	string expr;
	cout << "Introduceti expresia in forma inxfixata (normala): ";
	getline(cin, expr);
	Parser p(expr, "math");
	p.inFixToPostFix();
	p.displayPostFix();
	cout << p.evalPostFix();

	
}