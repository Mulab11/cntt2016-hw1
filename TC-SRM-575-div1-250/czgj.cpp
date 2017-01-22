/*
	Da biao zhao gui lv da fa hao!!!
	Brus wins when: n is odd, or n is an odd power of 2.
*/
#include <bits/stdc++.h>
using namespace std;
class TheNumberGameDivOne {
	public:
	string find(long long n) {
		return (n & 1) || n == (1ll << (1 | (int)round(log(n) / log(2)))) ? "Brus" : "John";
	}
};

/*
	Sayonora bokura wa kitto umare kawareru kara
	kanashimi ni te wo furun deshou
		- Oracion
*/
