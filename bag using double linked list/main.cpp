#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include "bag.h"
using namespace std;

int main()
{
	vector<bag> v;
	while (1) {
		system("cls");			//매 실행마다 콘솔창 청소
		cout << "Current bag num: " << v.size() << endl;	//명령 실행 이전 현재의 모든 bag 상태를 보여준다.
		for (int i = 0; i < v.size(); i++) {
			cout << "Bag " << i + 1 << ": ";
			v[i].show_contents();
		}
		cout << "==================================" << endl;	//모든 명령은 올바르지 않은 bag 번호를 입력할 시 취소된다.
		cout << "c : construct\ncc : copy construct\nd : destruct\n";
		cout << "i : insert\ne : erase_one\ns : size\ncn : count\n+ : merge and show\n+= : merge and put\n";
		cout << "= : put\n== : is same?\n!= : is different?\ng : print random data\nso : sort\nq : QUIT\n";
		cout << "Please type command: ";
		string s;
		cin >> s;
		if (s == "q") break;

		else if (s == "c") {	//비어있는 bag 하나를 생성한다. 
			v.push_back(bag());
			cout << "Construct complete.\n";
		}
		else if (s == "d") {	//bag 번호 하나를 입력받은 후 그 bag을 삭제한다.
			int type;
			cout << "Type BAG NUMBER that you want to destruct : ";
			cin >> type;
			if (type > v.size() || type < 1)
				cout << "Destruction failed. Please type in right scope.\n";
			else {
				bag a;
				v[type - 1] = a;
				v.erase(v.begin() + type - 1);
				cout << "Destruction successed.\n";
			}
		}
		else if (s == "cc") {	//bag 번호 하나를 입력받은 후 그 bag과 똑같은 bag을 하나 새로 생성한다.
			int type;
			cout << "Type BAG NUMBER that you want to copy : ";
			cin >> type;
			if (type > v.size() || type < 1)
				cout << "Copy construct failed. Please type in right scope.\n";
			else {
				v.push_back(bag(v[type - 1]));
				cout << "Copy construct successed.\n";
			}
		}
		else if (s == "i") {	//bag 번호와 수 하나를 입력받은 후 그 bag에 수를 삽입한다.
			int type, type2;
			cout << "Type BAG NUMBER and INPUT NUMBER : ";
			cin >> type >> type2;
			if (type > v.size() || type < 1)
				cout << "Destruction failed. Please type in right scope.\n";
			else {
				v[type - 1].insert(type2);
				cout << "Insertion successed.\n";
			}
		}
		else if (s == "e") {	//bag 번호와 수 하나를 입력받은 후 그 수를 bag에서 삭제한다.
			int type, type2;
			cout << "Type BAG NUMBER and ERASE NUMBER : ";
			cin >> type >> type2;
			if (type > v.size() || type < 1)
				cout << "Erase failed. Please type in right scope.\n";
			else {
				v[type - 1].erase_one(type2);
				cout << "Erase successed.\n";
			}
		}
		else if (s == "s") {	//bag 번호 하나를 입력받은 후 그 bag의 사이즈를 출력한다.
			int type;
			cout << "Type BAG NUMBER that you want to print size : ";
			cin >> type;
			if (type > v.size() || type < 1)
				cout << "Destruction failed. Please type in right scope.\n";
			else
				cout << "Bag size: " << v[type - 1].size() << '\n';
		}
		else if (s == "cn") {	//bag 번호와 수 하나를 입력받은 후 그 bag내에 입력받은 수가 몇 개 들어있는지 출력한다.
			int type, type2;
			cout << "Type BAG NUMBER and COUNT NUMBER : ";
			cin >> type >> type2;
			if (type > v.size() || type < 1)
				cout << "Counting failed. Please type in right scope.\n";
			else {
				cout << "Counting number: " << v[type - 1].count(type2) << endl;
			}
		}
		else if (s == "+") {	//bag 번호 두 개를 입력받은 후 두 bag을 이어붙인 결과를 출력한다.
			int type, type2;
			cout << "Type TWO BAG NUMBERS : ";
			cin >> type >> type2;
			if (type > v.size() || type < 1 || type2 > v.size() || type2 < 1)
				cout << "Counting failed. Please type in right scope.\n";
			else {
				bag a = v[type - 1] + v[type2 - 1];
				cout << "Merging of two bags - ";
				a.show_contents();
			}
		}
		else if (s == "+=") {	//bag 번호 두 개를 입력받은 후 먼저 입력받은 bag에 나중에 입력받은 bag을 이어붙인다.
			int type, type2;
			cout << "Type MERGED BAG NUMBER and COPIED BAG NUMBER : ";
			cin >> type >> type2;
			if (type > v.size() || type < 1 || type2 > v.size() || type2 < 1)
				cout << "Counting failed. Please type in right scope.\n";
			else {
				v[type - 1] += v[type2 - 1];
				cout << "Merge and put successed.\n";
			}
		}
		else if (s == "=") {	//bag 번호 두 개를 입력받은 후 먼저 입력받은 bag에 나중에 입력받은 bag을 덮어쓰기 한다.
			int type, type2;
			cout << "Type OVERWRITTEN BAG NUMBER and COPIED BAG NUMBER : ";
			cin >> type >> type2;
			if (type > v.size() || type < 1 || type2 > v.size() || type2 < 1)
				cout << "Counting failed. Please type in right scope.\n";
			else {
				v[type - 1] = v[type2 - 1];
				cout << "Overwritting successed.\n";
			}
		}
		else if (s == "==") {	//bag 번호 두 개를 입력받은 후 같으면 SAME, 다르면 NOT SAME 을 출력한다.
			int type, type2;
			cout << "Type TWO BAG NUMBERS : ";
			cin >> type >> type2;
			if (type > v.size() || type < 1 || type2 > v.size() || type2 < 1)
				cout << "Counting failed. Please type in right scope.\n";
			else {
				if (v[type - 1] == v[type2 - 1]) cout << "Two bags are SAME.\n";
				else cout << "Two bags are NOT SAME.\n";
			}
		}
		else if (s == "!=") {	//bag 번호 두 개를 입력받은 후 다르면 DIFFERENT, 같으면 NOT DIFFERENT 를 출력한다.
			int type, type2;
			cout << "Type TWO BAG NUMBERS : ";
			cin >> type >> type2;
			if (type > v.size() || type < 1 || type2 > v.size() || type2 < 1)
				cout << "Counting failed. Please type in right scope.\n";
			else {
				if (v[type - 1] != v[type2 - 1]) cout << "Two bags are DIFFERENT.\n";
				else cout << "Two bags are not DIFFERENT.\n";
			}
		}
		else if (s == "g") {	//bag 번호 하나를 입력받은 후 그 bag 내 랜덤한 요소 하나를 출력한다.
			int type;
			cout << "Type BAG NUMBER that you want to print random data : ";
			cin >> type;
			if (type > v.size() || type < 1)
				cout << "Destruction failed. Please type in right scope.\n";
			else
				cout << "Random data: " << v[type - 1].grab() << '\n';
		}
		else if (s == "so") {	//bag 번호 하나를 입력받은 후 bag 내 요소들을 오름차순으로 정렬시킨 뒤 저장한다.
			int type;
			cout << "Type BAG NUMBER that you want to change datum to ascending order : ";
			cin >> type;
			if (type > v.size() || type < 1)
				cout << "Destruction failed. Please type in right scope.\n";
			else {
				v[type - 1].bagsort();
				cout << "Sorting successed.\n";
			}
		}
		cout << "================== RESULT ==================" << endl;
		cout << "Current bag num: " << v.size() << endl;	//명령 실행 후 bag의 모든 상태를 보여준다.
		for (int i = 0; i < v.size(); i++) {
			cout << "Bag " << i + 1 << ": ";
			v[i].show_contents();
		}
		cout << "\nTo quit, type 'q'. To continue, type anything.";
		cin >> s;
		if (s == "q") break;
	}
}

