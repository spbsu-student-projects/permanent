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
#include <iomanip>
using namespace std;
string s;
vector<vector<polynom> > matr;
int n;
vector<int> perm;
polynom res;
int main(){
	cin >> n;
	matr.resize(n);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			cin >> s;
			matr[i].push_back(polynom_make_polynom(s));
		}
	}
	int pow2 = 1 << n;
	for (int i = 0; i < pow2; i++) {
        vector<bool> take(n);
        int x = i;
        int s = 0;
        for (int j = 0; j < n; j++) {
            if (x == 0) break;
            if (x % 2) {
                take[j] = true;
                s++;
            }
            x /= 2;
        }
        polynom summator;
        if (s % 2 != 0) summator = polynom(-1);
        else summator = polynom(1);
        for (int j = 0; j < n; j++) {
            polynom sum;
            for (int k = 0; k < n; k++) {
                if (take[k]) sum += matr[j][k];
            }
            summator *= sum;
        }
        res += summator;
	}
	if (n % 2 != 0) res = res * polynom(-1);
	cout << res << endl;
	return 0;
}
