#include <iostream>
#include <string>
#include <Windows.h>
#include "evaluator.hpp"
#include "mystack.hpp"
using namespace std;

int main()
{
	evaluator ev;
	while (1) {
		system("cls");	// 매 실행마다 콘솔창 청소
		cout << "Input a well-formed infix arithmetic expression : ";
		string s = ev.read_expression();
		s = ev.convert_to_postfix(s);
		cout <<"Result of converting to postfix expression : " << s << endl;
		cout << "Evaluation result : " << ev.evaluate_postfix(s) << endl << endl;
		cout << "To quit, type 'q'. To continue, type any letters. ";
		cin >> s;
		if (s == "q") break;
	}
}

