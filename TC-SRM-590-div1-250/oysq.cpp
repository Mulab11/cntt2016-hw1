#line 2 "FoxAndChess.cpp"  
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

class FoxAndChess {  
public:  
	string ableToMove(string s, string t) {
		// 只要满足s[i] = R的情况下对应的位置在i的右边，L同理，以及两串LR都一样即可
		int n = SZ(s), i = 0, j = 0;
		for(; i < n; ++i)
			if(s[i] != '.') {
				while(j < n && t[j] == '.') ++j;
				if(j == n || s[i] != t[j]) return "Impossible";
				if(s[i] == 'L' && i < j) return "Impossible";
				if(s[i] == 'R' && i > j) return "Impossible";
				++j;
			}
		while(j < n && t[j] == '.') ++j;
		return j == n ? "Possible" : "Impossible";
	}    
};  
