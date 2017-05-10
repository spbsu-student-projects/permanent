#pragma once
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iostream>

class monom {
private:
	std::vector<int> powers;
public:
	monom();
	monom(int);
	monom(int, int);
	void resize();
	int get_power(int);
	int get_power();
	monom& operator*=(monom);
	monom& operator^=(int);
	monom& operator%=(monom);
	monom& operator/=(monom);
	friend monom operator*(monom, monom);
	friend monom operator^(monom, int);
	friend monom operator%(monom, monom);
	friend monom operator/(monom, monom);
	friend bool operator<(monom, monom);
	friend bool operator>(monom, monom);
	friend bool operator==(monom, monom);
	friend bool operator!=(monom, monom);
	friend bool operator<=(monom, monom);
	friend bool operator>=(monom, monom);
	friend std::ostream& operator<<(std::ostream&, monom);
};

class polynom {
private:
	std::map<monom, long double> monoms;
	void clean();
public:
	polynom();
	polynom(long double);
	polynom(monom, long double);
	polynom& operator+=(polynom&);
	polynom& operator-=(polynom&);
	polynom& operator*=(polynom&);
	polynom& operator^=(int);
	//polynom& operator%=(monom);
	//polynom& operator/=(monom);
	//polynom& operator%=(polynom);
	//polynom& operator/=(polynom);
	friend polynom operator+(polynom, polynom);
	friend polynom operator-(polynom, polynom);
	friend polynom operator*(polynom, polynom);
	friend polynom operator^(polynom, int);
	//friend polynom operator%(polynom, monom);
	//friend polynom operator/(polynom, monom);
	//friend polynom operator%(polynom, polynom);
	//friend polynom operator/(polynom, polynom);
	friend std::ostream& operator<<(std::ostream&, polynom&);
};

extern polynom polynom_make_polynom(std::string&, int start = 0, int end = 1e9);
extern int polynom_make_int(std::string&, int start = 0, int end = 1e9);
extern long double string_to_real(std::string&);
