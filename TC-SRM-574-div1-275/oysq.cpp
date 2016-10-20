#line 2 "TheNumberGame.cpp"  
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


class TheNumberGame {  
public:  
	bool check(int *a, int an, int *b, int bn) {
		//bf string match
		for(int i = 1; i + bn - 1 <= an; ++i) {
			bool ok = true;
			for(int j = 1; j <= bn; ++j)
				if(a[i + j - 1] != b[j]) {
					ok = false;
					break;
				}
			if(ok) return true;
		}
		return false;
	}
	string determineOutcome(int A, int B) {
		int a[20] = {0}, an = 0;
		int b[20] = {0}, bn = 0;
		// int -> string
		while(A) a[++an] = A % 10, A /= 10;
		while(B) b[++bn] = B % 10, B /= 10;
		if(check(a, an, b, bn)) return "Manao wins";
		std::reverse(b + 1, b + bn + 1);
		if(check(a, an, b, bn)) return "Manao wins";
		return "Manao loses";
	}
};
