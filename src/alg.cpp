// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPrior(char pr) {
	std::pair<char, int> priority[6];
	switch (pr) {
		case '(':
			priority[0].first = '(';
			priority[0].second = 0;
		case ')':
			priority[1].first = ')';
			priority[1].second = 1;
		case '+':
			priority[2].first = '+';
			priority[2].second = 2;
		case '-':
			priority[3].first = '-';
			priority[3].second = 2;
		case '*':
			priority[4].first = '*';
			priority[4].second = 3;
		case '/':
			priority[5].first = '/';
			priority[5].second = 3;
	}
	int prior = -1;
	for (int j = 0; j < 6; ++j) {
		if (pr == priority[j].first) {
			prior = priority[j].second;
			break;
		}
	}
	return prior;
}

std::string func1(const std::string&s) {
        if (s.length() <= 2) return s;
        int n = 2 - s.length() % 2;
        std::string a(s, 0, n);
        for (auto it = s.begin() + n; it != s.end();) {
                a += ' ';
                a += *it++;
                ;
        }
        return a;
}

std::string infx2pstfx(std::string inf) {
	std::string primer;
	Tstack<char, 100> stack1;
	for (auto&x : inf) {
		int prior = getPrior(x);
		if (prior == -1) {
			primer += x;
		} else {
			if (stack1.get() < prior || prior == 0 || stack1.isEmpty()) {
				stack1.push(x);
			} else if (x == ')') {
				char zn = stack1.get();
				while (getPrior(zn) >= prior) {
					primer += zn;
					stack1.pop();
					zn = stack1.get();
				}
				stack1.pop();
			} else {
				char zn = stack1.get();
				while (getPrior(zn) >= prior) {
					primer += zn;
					stack1.pop();
					zn = stack1.get();
				}
				stack1.push(op);
			}
		}
	}
	while (!stack1.isEmpty()) {
		primer += stack1.get();
		stack1.pop();
	}
	primer = func1(primer);
	return primer;
}

int count(const int& a, const int& b, const int& oper) {
	switch (oper) {
		default:
			break;
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			return a / b;
	}
	return 0;
}

int eval(std::string pref) {
	Tstack<int, 100> stack1;
	std::string num = "";
	for (size_t i = 0; i < pref.size(); i++) {
		if (getPrior(pref[i]) == -1) {
			if (pref[i] == ' ') {
				continue;
			} else if (isdigit(pref[i + 1])) {
				num += pref[i];
				continue;
			} else {
				num += pref[i];
				stack1.push(atoi(num.c_str()));
				num = "";
			}
		} else {
			int b = stack1.get();
			stack1.pop();
			int a = stack1.get();
			stack1.pop();
			stack1.push(count(a, b, pref[i]));
		}
	}
	return stack1.get();
}
