#line 2 "MayTheBestPetWin.cpp"  
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

const int S = 1000000;

std::bitset<S + 9> f;

class MayTheBestPetWin {  
public:  
	int calc(vector <int> A, vector <int> B) {
		int n = SZ(A);
		int sa = 0, sb = 0;// sa, sb分别表示A和B的和
		for(auto a : A) sa += a;
		for(auto b : B) sb += b;
		// 设一个集合的区间为[a, b]，那么另一个就是[sa - a, sb - b]
		// 对于这个情况下的答案是max{sb - b - a, b + a - sa}
		// 我们只需要求出所有合法的a + b即可
		f.reset(), f[0] = 1;
		// f[i] = 1表示a + b可以等于i
		for(int i = 0; i < n; ++i)// 用位运算加速
			f = f | f << A[i] + B[i];
		int ans = 1e9;
		for(int i = 0; i <= sa + sb; ++i)// 统计答案
			if(f[i]) chkmin(ans, std::max(i - sa, sb - i));
		return ans;
	}    
};  
