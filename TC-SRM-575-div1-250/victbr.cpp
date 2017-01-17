#include <bits/stdc++.h>

using namespace std;

class TheNumberGameDivOne{
	public:
		string find(long long n){
			if (n & 1) return "Brus";
			int u = 0;
			while (n % 2 == 0){
				n /= 2;u++;
			}
			if (n == 1 && u%2 == 1) return "Brus";
			return "John";
		}
};
