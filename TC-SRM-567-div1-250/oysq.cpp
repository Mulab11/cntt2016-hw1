#line 2 "TheSquareRootDilemma.cpp"  
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

const int R = 77777;

class TheSquareRootDilemma {  
public:  
	int countPairs(int n, int m) {
		int ans = 0;
		for(int i = 1; i <= n; ++i) {// 枚举A
			int t = 1, p = i;
			for(int j = 2; j * j <= n; ++j)// 分解A的质因数
				if(p % j == 0) {
					int c = 0;
					while(p % j == 0) p /= j, c ^= 1;
					if(c) t *= j;
				}
			if(p > 1) t *= p;
			// 对于A的质因子p，假设次数是k，如果k是奇数，那么B必须要有奇数个p来配对，那么B的范围除以p
			// 我们计算平方数个数即可
			ans += sqrt(m / t);
		}
		return ans;
	}  
};  
