#include "evaluator.hpp"

string evaluator::read_expression() {
	string s;
	cin >> s;
	return s;
}
string evaluator::convert_to_postfix(string s) {
	stack<char> st;
	string output;
	bool prevnum = 0;
	for (int i = 0; i < s.length(); i++) {
		switch (s[i]) {
		case '(':
			st.push(s[i]);
			break;
		case ')':	// ���� �� �� ������ �ϳ��� ��°��� �ְ� �װͰ� ( �ϳ��� ���ÿ��� ����.
			output += st.top();
			output += ' ';
			st.pop();
			st.pop();
			break;
		case '+':
		case '-':
		case '*':
		case '/':	// �����ڵ��� �켱������ ���� ���ÿ� �ְų�, �ٸ� �����ڸ� ��°��� �ְ� ���ÿ��� ������ �� �ڽ��� ���ÿ� �ִ´�.
			if (st.empty() || st.top() == '(') st.push(s[i]);
			else if (s[i] == '+' || s[i] == '-') {
				output += st.top();
				output += ' ';
				st.pop();
				st.push(s[i]);
			}
			else {
				if (st.top() == '*' || st.top() == '/') {
					output += st.top();
					output += ' ';
					st.pop();
					st.push(s[i]);
				}
				else st.push(s[i]);
			}
			break;
		default:	//�����ڿ� ( �׸��� )�� ������ ���� �� ���ڵ��� �پ������� �ϳ��� ��� �Ǵ� ������ �ν��ϰ� ������ ���� �ʴ´�.
			output += s[i];
			if (i != s.length() - 1) {
				switch (s[i + 1]) {
				case '+':
				case '-':
				case '*':
				case '/':
				case '(':
				case ')':
					output += ' ';
				}
			}
			else output += ' ';
		}
	}

	while (!st.empty()) {	// Ž���� ���� �� ���ÿ� �����ִ� �����ڵ��� ��°��� �ִ´�.
		output += st.top();
		output += ' ';
		st.pop();
	}
	return output;
}
double evaluator::evaluate_postfix(string s) {
	stack<double> st;			
	map<string, double> var;	// ����� �ƴ� ������ ó���ϱ� ���� std::map �����̳� ���
	int isvar = 0;				// �� ���� �������, ��������, ���������� Ȯ���ϴ� �뵵
	string num;					// ���ڿ� ������ ��� �Ǵ� ������ �Ǽ� ���·� ó���ϱ� �� �����صδ� �뵵
	for (int i = 0; i < s.length(); i++) {
		switch (s[i]) {
		case '+':
		case '-':
		case '*':
		case '/':		// �����ڰ� ���� ���� �� �� ���� ���ÿ��� �����ϰ� ������ ���Ѵ�.
			double b,c;
			b = st.top();
			st.pop();
			c = st.top();
			st.pop();
			if (s[i] == '+') st.push(b + c);
			else if (s[i] == '-') st.push(c - b);
			else if (s[i] == '*') st.push(b * c);
			else if (s[i] == '/') st.push(c / b);
			break;
		case ' ':
			if (isvar==2) {	// ���� �Է��� ������ ��
				if (var.find(num) == var.end()) {	// ����ڷκ��� ������ ���� �Է¹��� ���� ������ �Է¹޴´�.
					cout << "Input the value of " << num << " : ";
					double a;
					cin >> a;
					var.insert({ num,a });
					st.push(a);
				}
				else {	// ����ڷκ��� ������ ���� �Է¹��� ���� ������ �� ���� ���ÿ� �ִ´�.
					st.push(var[num]);
				}
			}
			else if(isvar==1) st.push(stod(num));	// ���� �Է��� ����� �� �Ǽ������� ��ȯ�ϰ� ���ÿ� �ִ´�.
			
			num = "";
			isvar = 0;
			break;
		default:
			if (!((s[i] >= '0' && s[i] <= '9') || s[i] == '.')) isvar = 2;	//���� Ž���� ���� 0~9�� ���� �Ǵ� . �� �ƴϸ� ������ �ν��Ѵ�.
			else if (isvar == 0) isvar = 1;
			num += s[i];
		}
	}
	return st.top();	// ���� ��갪�� ������ ���� ���� ����Ǿ� ������ �̸� ���.
}