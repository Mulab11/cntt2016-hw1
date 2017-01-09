//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include <string>
#include <iostream>

using namespace std;

#define FOR(i,a,b) for (int i = a; i <= b; i++)

class CuttingBitString {
public:
	bool check(string s) {
		//valid segment must not has a leading zero
		if (s[0] == '0') return false;

		long long t = 0;
		int sz = s.size();

		//calculate the value of s in decimal
		FOR (i, 0, sz - 1)
			t = t * 2 + (s[i] == '1');

		//try to divide s by 5 when it is possible
		while ((t % 5) == 0) t /= 5;

		return t == 1;
	}

	int getmin(string s) {
		//n is length of s
		int n = s.size();
		//the f array in dynamic program
		int f[100];

		FOR (i, 0, n - 1) {
			f[i] = -1;

			//if the prefix of i + 1 first characters of s is a power of 5 in binary
			//and not leading by 0, f[i] = 1.
			if (check(s.substr(0, i + 1))) {
				f[i] = 1;

			}
                        else {
			   // try the possibilities of the last part of s
			     FOR (j, 1, i)
				 	if (check(s.substr(j, i - j + 1)) && f[j - 1] != -1)
				 		if (f[i] == -1 || f[i] > f[j - 1] + 1)
				 			f[i] = f[j - 1] + 1;
                       }
		}

		return f[n - 1];
	}
};