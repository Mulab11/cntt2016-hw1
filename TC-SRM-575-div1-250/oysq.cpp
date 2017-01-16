#line 2 "TheNumberGameDivOne.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

class TheNumberGameDivOne {  
public:  
	string find(long long n) {
		// 2 的奇数次幂为0
		for(int i = 1; i < 60; i += 2)
			if((1ll << i) == n)
				return "Brus";
		// 否则奇数为0，偶数为1
		if(n & 1) return "Brus";
		else return "John";
	}  
};  
