#line 2 "PyramidSequences.cpp"  
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


class PyramidSequences {  
public:  
	long long distinctPairs(int n, int m) {
		int N = 2 * n - 2, M = 2 * m - 2;
		int d = __gcd(N, M);// 不妨把1 ~ n变成0 ~ n - 1, 假设一个数x，那么在一个循环中，它出现的位置mod d 为 x mod d 和 -x mod d
		ll ans = (ll)(N / d) * (M / d) * (d - 2) / 2;// 0和d / 2需要特殊考虑，因为它们满足x mod d = -x mod d，其他的d - 2种情况可以直接算，/ 2时因为x mod d和-x mod d是对称的
		int c0[2] = {1, 1}, c1[2] = {0};// c0[0]表示0和n - 1两个数，mod d = 0的个数，c0[1]表示0和m - 1两个数，mod d = d / 2的个数
		if((n - 1) % d == 0) c0[0]++;
		else c1[0]++;
		if((m - 1) % d == 0) c0[1]++;
		else c1[1]++;
		// 除去A中0, (n - 1) mod d, B中0, (m - 1) mod d其他的数依然具有对称性
		ans += (ll)((N / d - c0[0]) / 2 + c0[0]) * ((M / d - c0[1]) / 2 + c0[1]);// 考虑0
		ans += (ll)((N / d - c1[0]) / 2 + c1[0]) * ((M / d - c1[1]) / 2 + c1[1]);// 考虑d / 2
		return ans;
	}    
};  
