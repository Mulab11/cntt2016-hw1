#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;

class TheNumberGameDivOne{
public:
	string find(LL x){
		if(x & 1LL) return "Brus"; int i;
		for(i = 0; x != 1; x >>= 1, ++ i)
			if(x & 1) return "John";
		return (i & 1) ? "Brus" : "John";
	}
};
