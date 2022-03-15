#pragma once
#include <string>
#include <iostream>
#include <map>
#include "mystack.hpp"
#include "mystack.cpp"

using namespace std;

class evaluator {
public:
	string read_expression();				// infix expression�� �Է����� �޾ƿ� �� ��ȯ
	string convert_to_postfix(string);		// infix expression�� postfix�� ��ȯ�� �� ��ȯ. �� ��/������ ���̿��� ������ �ϳ� ����.
	double evaluate_postfix(string);		// postfix expression�� ����� �� ���. �߰��� ������ ������ ������ ���� ����ڷκ��� �Է¹���.
};
