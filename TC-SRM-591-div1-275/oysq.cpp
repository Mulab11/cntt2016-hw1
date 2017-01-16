#line 2 "TheTree.cpp"  
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

class TheTree {  
public:  
	int maximumDiameter(vector <int> cnt) {
		int ans = 0, d = SZ(cnt);
		cnt.insert(cnt.begin(), 1);// V自己距离为0
		for(int i = SZ(cnt) - 1; i >= 0; --i) {// 枚举距离V最远的点i
			int j = i;
			while(j > 0 && cnt[j] > 1) --j;// 贪心最小的lca
			chkmax(ans, d + i - 2 * j);
			i = j;
		}
		return ans;
	}    
};  
