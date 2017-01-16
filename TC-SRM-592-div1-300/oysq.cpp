#line 2 "LittleElephantAndBalls.cpp"  
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

const int N = 50;

class LittleElephantAndBalls {  
public:  
	int getNumber(string s) {
		int ans = 0, t = 0, c[300] = {0};
		// 贪心，假设将字符串分成左右两边
		// 如果左边没有该字母，放在左边的最右端，否则放在右边的最左端
		for(auto i : s) {
			ans += t;
			if((++c[(int)i]) <= 2)
				t++;
		}
		return ans;
	}    
};  
