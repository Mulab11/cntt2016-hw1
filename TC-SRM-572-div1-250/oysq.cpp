#line 2 "NewArenaPassword.cpp"  
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

class NewArenaPassword {  
public:  
	int minChange(string op, int K) {
		int n = SZ(op);
		if(K == n) {// K == n时，前后缀是同一个串，不需要改
			return 0;
		}
		int eq[N + 9];// eq[i]表示前缀位置i对应的后缀位置
		memset(eq, -1, sizeof eq);
		bool vis[N + 9] = {false};
		for(int i = 0; i < K; ++i) {
			eq[i] = n - K + i;
		}
		int ans = 0;
		for(int i = 0; i < K; ++i) {
			if(!vis[i]) {// 避免重复遍历
				int cnt[26] = {0};// 记录每个字母出现次数
				int all = 0;// 集合大小
				std::vector<int> v;
				for(int j = i; j != -1; j = eq[j]) {// 遍历一遍从i开始的需要相等的集合
					cnt[op[j] - 'a']++;
					vis[j] = true;// 标记走过
					++all;
				}
				// 把其他位置改成出现次数最多的字母
				int max = -1;
				for(int j = 0; j < 26; ++j) {
					if(max < cnt[j]) {
						max = cnt[j];
					}
				}
				ans += all - max;
			}
		}
		return ans;
	}    
};  
