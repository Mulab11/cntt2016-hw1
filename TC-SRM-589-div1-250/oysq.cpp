#line 2 "GooseTattarrattatDiv1.cpp"  
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

const int N = 26;

int f[N + 9];
int ma[N + 9];
// f[i] 表示并查集的父亲
// ma[i] 表示该集合中字母出现次数的最大值

int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}

class GooseTattarrattatDiv1 {  
public:  
	int getmin(string s) {  
		for(int i = 0; i < 26; ++i) f[i] = i, ma[i] = 0;
		for(auto i : s) ma[i - 'a']++;
		// 回文的话要求s[i] = s[l - i - 1], 那么也就是s[i]和s[l - i - 1]最后要变成一个字母
		// 因此可以把s[i]和s[l - i - 1]并起来，最后对每个集合贪心最小解
		for(int i = 0, l = SZ(s); i < l - i - 1; ++i) {
			int u = find(s[i] - 'a'), v = find(s[l - i - 1] - 'a');
			if(u != v) f[u] = v, chkmax(ma[v], ma[u]);
		}
		int ans = SZ(s);
		for(int i = 0; i < 26; ++i)
			if(find(i) == i) ans -= ma[i];
		return ans;
	}   
};  
