#pragma once
#include <string>
#include <iostream>
#include <map>
#include "mystack.hpp"
#include "mystack.cpp"

using namespace std;

class evaluator {
public:
	string read_expression();				// infix expression을 입력으로 받아온 뒤 반환
	string convert_to_postfix(string);		// infix expression을 postfix로 변환한 뒤 반환. 각 수/연산자 사이에는 공백이 하나 있음.
	double evaluate_postfix(string);		// postfix expression을 계산한 뒤 출력. 중간에 변수가 있으면 변수의 값을 사용자로부터 입력받음.
};
