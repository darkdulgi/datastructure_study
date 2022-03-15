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
		case ')':	// 스택 맨 위 연산자 하나를 출력값에 넣고 그것과 ( 하나를 스택에서 제거.
			output += st.top();
			output += ' ';
			st.pop();
			st.pop();
			break;
		case '+':
		case '-':
		case '*':
		case '/':	// 연산자들을 우선순위에 따라 스택에 넣거나, 다른 연산자를 출력값에 넣고 스택에서 제거한 뒤 자신을 스택에 넣는다.
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
		default:	//연산자와 ( 그리고 )를 제외한 숫자 및 문자들은 붙어있으면 하나의 상수 또는 변수로 인식하고 공백을 넣지 않는다.
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

	while (!st.empty()) {	// 탐색이 끝난 뒤 스택에 남아있는 연산자들을 출력값에 넣는다.
		output += st.top();
		output += ' ';
		st.pop();
	}
	return output;
}
double evaluator::evaluate_postfix(string s) {
	stack<double> st;			
	map<string, double> var;	// 상수가 아닌 변수를 처리하기 위해 std::map 컨테이너 사용
	int isvar = 0;				// 전 값이 상수인지, 변수인지, 연산자인지 확인하는 용도
	string num;					// 문자열 형태의 상수 또는 변수를 실수 형태로 처리하기 전 저장해두는 용도
	for (int i = 0; i < s.length(); i++) {
		switch (s[i]) {
		case '+':
		case '-':
		case '*':
		case '/':		// 연산자가 오면 위의 수 두 개를 스택에서 제거하고 연산을 취한다.
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
			if (isvar==2) {	// 이전 입력이 변수일 때
				if (var.find(num) == var.end()) {	// 사용자로부터 변수의 값을 입력받은 적이 없으면 입력받는다.
					cout << "Input the value of " << num << " : ";
					double a;
					cin >> a;
					var.insert({ num,a });
					st.push(a);
				}
				else {	// 사용자로부터 변수의 값을 입력받은 적이 있으면 그 값을 스택에 넣는다.
					st.push(var[num]);
				}
			}
			else if(isvar==1) st.push(stod(num));	// 이전 입력이 상수일 때 실수형으로 변환하고 스택에 넣는다.
			
			num = "";
			isvar = 0;
			break;
		default:
			if (!((s[i] >= '0' && s[i] <= '9') || s[i] == '.')) isvar = 2;	//현재 탐색한 값이 0~9의 숫자 또는 . 이 아니면 변수로 인식한다.
			else if (isvar == 0) isvar = 1;
			num += s[i];
		}
	}
	return st.top();	// 최종 계산값은 스택의 가장 위에 저장되어 있으니 이를 출력.
}