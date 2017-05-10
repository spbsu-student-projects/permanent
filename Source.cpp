#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <math.h>
#include "polynom.h"
#include <string>
#include <fstream>
#include <ctime>
using namespace std;
string s;
vector<vector<polynom>> matr;
int n;
vector<int> perm;
long long fact;
polynom res;
int main(){
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	fin >> n;
	int start = clock();
	matr.resize(n);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			fin >> s;
			matr[i].push_back(polynom_make_polynom(s));
		}
	}
	//fout << clock() - start<< endl;
	fact = 1;
	for (int i = 1; i <= n; i++){
		fact = fact * i;
	}
	for (int i = 0; i < n; i++){
		perm.push_back(i);
	}
	fact = 1;
	//res = polynom();
	for (int i = 0; i < n; i++){
		fact = fact * (i + 1);
	}
	polynom tres;
	for (int k = 0; k < fact; k++){
		tres = polynom(1);
		for (int j = 0; j < n; j++){
			tres = tres * matr[j][perm[j]];
		}
		res += tres;
		next_permutation(perm.begin(),perm.end()); 
	}
	fout << res << endl;
	//fout << clock() - start << endl;
	return 0;
}