#include "polynom.h"

std::vector<std::string> variables;

//Monoms//

monom::monom() {
	powers.resize(variables.size());
}

monom::monom(int variable) {
	powers.resize(variables.size());
	powers[variable] = 1;
}

monom::monom(int variable, int power) {
	powers.resize(variables.size());
	powers[variable] = power;
}

void monom::resize() {
	powers.resize(variables.size());
}

int monom::get_power() {
	int sum = 0;
	for (int power : powers) sum += power;
	return sum;
}

monom& monom::operator*=(monom right) {
	resize();
	right.resize();

	for (int i = 0; i < (int)variables.size(); i++) {
		powers[i] += right.powers[i];
	}

	return *this;
}

monom& monom::operator^=(int power) {
	monom answer = (*this) ^ power;
	powers = answer.powers;
	return *this;
}

monom& monom::operator%=(monom right) {
	resize();
	right.resize();

	int number_of_times = -1;

	for (int i = 0; i < (int)variables.size(); i++) {
		if (right.powers[i] > 0) {
			if (number_of_times == -1 || number_of_times > powers[i] / right.powers[i]) {
				number_of_times = powers[i] / right.powers[i];
			}
		}
	}
	for (int i = 0; i < (int)variables.size(); i++) {
		powers[i] -= number_of_times * right.powers[i];
	}

	return *this;
}

monom& monom::operator/=(monom right) {
	monom answer = (*this) / right;
	powers = answer.powers;
	return *this;
}

monom operator*(monom left, monom right) {
	monom answer = left;
	answer *= right;
	return answer;
}

monom operator^(monom left, int power) {
	if (power == 0) return monom();
	monom answer = left ^ (power / 2);
	answer *= answer;
	if (power % 2 != 0) answer *= left;
	return answer;
}

monom operator%(monom left, monom right) {
	monom answer = left;
	answer %= right;
	return answer;
}

monom operator/(monom left, monom right) {
	left.resize();
	right.resize();

	monom mod = left % right;
	monom answer = left;
	for (int i = 0; i < (int)variables.size(); i++) {
		answer.powers[i] -= mod.powers[i];
		answer.powers[i] /= right.powers[i];
	}

	return answer;
}

bool operator<(monom a, monom b) {
	a.resize();
	b.resize();

	int delta = a.get_power() - b.get_power();
	if (delta != 0) {
		return delta > 0;
	}

	for (int i = 0; i < (int)variables.size(); i++) {
		delta = a.powers[i] - b.powers[i];
		if (delta != 0) {
			return delta > 0;
		}
	}

	return false;
}

bool operator>(monom a, monom b) {
	return b < a;
}

bool operator==(monom a, monom b) {
	return !((a < b) || (a > b));
}

bool operator!=(monom a, monom b) {
	return !(a == b);
}

bool operator<=(monom a, monom b) {
	return !(a > b);
}

bool operator>=(monom a, monom b) {
	return !(a < b);
}

std::ostream& operator<<(std::ostream& os, monom a) {
	a.resize();

	int all_power = a.get_power();
	for (int i = 0; i < (int)variables.size(); i++) {
		all_power -= a.powers[i];
		if (a.powers[i] > 0) os << variables[i];
		if (a.powers[i] > 1) os << "^" << a.powers[i];
		if (all_power > 0 && a.powers[i] > 0) os << "*";
	}
	return os;
}

//Polynoms//

void polynom::clean() {
	std::map<monom, long double> new_monoms;
	for (auto a : monoms) {
		if (a.second != 0) {
			new_monoms[a.first] = a.second;
		}
	}
	monoms = new_monoms;
}

polynom::polynom() {

}
polynom::polynom(long double num) {
	monoms[monom()] = num;
}

polynom::polynom(monom a, long double num) {
	monoms[a] = num;
}

polynom& polynom::operator+=(polynom& right) {
	for (auto a : right.monoms) {
		monoms[a.first] += a.second;
	}
	clean();
	return *this;
}
polynom& polynom::operator-=(polynom& right) {
	for (auto a : right.monoms) {
		monoms[a.first] -= a.second;
	}
	clean();
	return *this;
}
polynom& polynom::operator*=(polynom& right) {
	polynom answer = (*this) * right;
	monoms = answer.monoms;
	return *this;
}
polynom& polynom::operator^=(int power) {
	polynom answer = (*this) ^ power;
	monoms = answer.monoms;
	return *this;
}

polynom operator+(polynom left, polynom right) {
	polynom answer = left;
	answer += right;
	return answer;
}

polynom operator-(polynom left, polynom right) {
	polynom answer = left;
	answer -= right;
	return answer;
}

polynom operator*(polynom left, polynom right) {
	polynom answer;
	for (auto a : left.monoms) {
		for (auto b : right.monoms) {
			answer.monoms[a.first * b.first] += a.second * b.second;
		}
	}
	answer.clean();

	return answer;
}

polynom operator^(polynom left, int power) {
	if (power == 0) return polynom(1);
	polynom answer = left ^ (power / 2);
	answer *= answer;
	if (power % 2 != 0) answer *= left;
	return answer;
}

std::ostream& operator<<(std::ostream& os, polynom& poly) {
	poly.clean();

	int all_monoms = 0;
	for (auto a : poly.monoms) {
		if (all_monoms > 0 && a.second > 0) os << "+";
		if (a.second == -1) os << "-";
		else if (a.second != 1) {
			os << a.second;
			if (a.first != monom()) os << "*";
		}
		if (a.first == monom() && (a.second == -1 || a.second == 1)) os << 1;
		os << a.first;
		all_monoms++;
	}
	if (all_monoms == 0) os << 0;
	return os;
}

//Miscellaneous//

polynom polynom_make_polynom(std::string& s, int start, int end) {
	if (end > (int)s.size()) end = s.size();

	if (start >= end) return polynom();

	//+, -
	int balance = 0;
	for (int i = end - 1; i >= start; i--) {
		if (s[i] == '(') balance++;
		if (s[i] == ')') balance--;
		if (balance == 0) {
			if (s[i] == '+') return polynom_make_polynom(s, start, i) + polynom_make_polynom(s, i + 1, end);
			if (s[i] == '-') return polynom_make_polynom(s, start, i) - polynom_make_polynom(s, i + 1, end);
		}
	}

	//*
	balance = 0;
	for (int i = end - 1; i >= start; i--) {
		if (s[i] == '(') balance++;
		if (s[i] == ')') balance--;
		if (balance == 0) {
			if (s[i] == '*') return polynom_make_polynom(s, start, i) * polynom_make_polynom(s, i + 1, end);
		}
	}

	//^ (left)
	balance = 0;
	for (int i = start; i < end; i++) {
		if (s[i] == '(') balance++;
		if (s[i] == ')') balance--;
		if (balance == 0) {
			if (s[i] == '^') return polynom_make_polynom(s, start, i) ^ polynom_make_int(s, i + 1, end);
		}
	}

	//()
	if (s[start] == '(' || s[end - 1] == ')') {
		if (s[start] == '(') start++;
		if (s[end - 1] == ')') end--;
		return polynom_make_polynom(s, start, end);
	}

	//number or variable
	bool not_a_number = false;
	for (int i = start; i < end; i++) {
		if (s[i] != '.' && (s[i] < '0' || s[i] > '9')) not_a_number = true;
	}
	if (not_a_number) {
		std::string variable = s.substr(start, end - start);
		for (int i = 0; i < (int)variables.size(); i++) {
			if (variables[i] == variable) return polynom(monom(i), 1);
		}
		variables.push_back(variable);
		return polynom(monom((int)variables.size() - 1), 1);
	}
	else {
		std::string number = s.substr(start, end - start);
		return polynom(string_to_real(number));
	}
}

int polynom_make_int(std::string& s, int start, int end) {
	if (end > (int)s.size()) end = s.size();

	if (start >= end) return 0;

	//+, -
	int balance = 0;
	for (int i = end - 1; i >= start; i--) {
		if (s[i] == '(') balance++;
		if (s[i] == ')') balance--;
		if (balance == 0) {
			if (s[i] == '+') return polynom_make_int(s, start, i) + polynom_make_int(s, i + 1, end);
			if (s[i] == '-') return polynom_make_int(s, start, i) - polynom_make_int(s, i + 1, end);
		}
	}

	//*
	balance = 0;
	for (int i = end - 1; i >= start; i--) {
		if (s[i] == '(') balance++;
		if (s[i] == ')') balance--;
		if (balance == 0) {
			if (s[i] == '*') return polynom_make_int(s, start, i) * polynom_make_int(s, i + 1, end);
		}
	}

	//()
	if (s[start] == '(' || s[end - 1] == ')') {
		if (s[start] == '(') start++;
		if (s[end - 1] == ')') end--;
		return polynom_make_int(s, start, end);
	}

	//number
	std::string number = s.substr(start, end - start);
	return string_to_real(number);
}

long double string_to_real(std::string& s) {
	std::stringstream sstr;
	long double answer;
	sstr.str(s);
	sstr >> answer;
	return answer;
}
