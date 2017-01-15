#line 2 "SpellCards.cpp"  
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
const int INF = 0x3f3f3f3f;

int n;
int f[N + 9];

class SpellCards {  
public:  
	int maxDamage(vector <int> level, vector <int> damage) {
		// 只要选中的level之和 <= n，就一定可以找到一种合法的方案
		// 因此题目变成了常规的背包dp
		n = SZ(level);
		memset(f, 0, sizeof f);
		for(int i = 0; i < n; ++i) {
			for(int j = n; j >= level[i]; --j)
				chkmax(f[j], f[j - level[i]] + damage[i]);
		}
		return *std::max_element(f, f + n + 1);
	}  
};
