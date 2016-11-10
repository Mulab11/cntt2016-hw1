#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int gcd( int a, int b ) {
	if( !b ) return a;
	return gcd( b, a % b );
}

int sqrt2( LL x ) {
	int l = 0, r = 282842712 + 1;
	
	while( l + 1 < r ) {
		int mid = (l+r) >> 1;
		if( 1ll*mid*mid <= x ) l = mid;
		else r = mid;
	}
	return l;
}

int sqrt3( LL x ) {
	int l = 0, r = 430886 + 1;
	while( l + 1 < r ) {
		int mid = (l+r) >> 1;
		if( 1ll*mid*mid*mid <= x ) l = mid;
		else r = mid;
	}
	return l;
}

const int N2 = 282842712; // 数据范围开几次方的各个数值 
const int N3 = 430886;
const int N4 = 16817;

int pool[7289070];
int *pta;

bool ip2[N3+1],ip3[N4+1];
int *cp2[N3+1],*pri[N3+1],len[N3+1],pd[N3+1];

LL Solve( LL n )
{
	LL ret = 0ll;
	for( int i = 1; 1ll*i*i*i < n; ++i )	// 计算 n = a * x ^ 2 
		if( ip2[i] ) ret += sqrt2( n / i ) - i;
	
	
	for( int i = 1; 1ll*i*i*i*i < n; ++i )
		if( ip3[i] )
			for( int k = 1; k*k*k <= i; ++k )
			{
				int g = gcd( i, k*k ), pb = i / g, pk = k*k / g;
				if( !ip2[pb] ) continue;
				int miny = i, maxy = sqrt3( n / i );
				int l = len[pb], si = 1<<l;
				for( int s = 0; s < si; ++s ) // 暴力枚举所有素因子乘积 
				{
					int d = 1, mu = 1;
					for( int j = 0; j < l; ++j )
						if( s >> j & 1 ) d *= pri[pb][j], mu *= -1;
					ret += 1ll*mu*( cp2[d][maxy/pk/d] - cp2[d][miny/pk/d] ); // 此处用cp2快速统计 
				}
			}
	return ret;
}

class SemiPerfectPower {
	public:
	LL  count( LL L, LL R ) {
		memset( ip2, 1, sizeof( ip2 ) );
		memset( ip3, 1, sizeof( ip3 ) );
		for( int i = 2; i * i <= N3; ++i ) //预处理无完全平方因子的数 
			for( int j = i*i; j <= N3; j += i*i ) 
				ip2[j] = 0;
		
		for( int i = 2; i*i*i <= N4; ++i ) //预处理无完全立方因子的数 
			for( int j = i*i*i; j <= N4; j += i*i*i )
				ip3[j] = 0;
		
		pta = pool;	
		for( int i = 1; i <= N3; ++i ) // 预处理 cp2[i][j], 表示 1 到 i*j 有多少个数是 i 的倍数但无完全平方因子 
		{
			int l = N3 / i;
			cp2[i] = pta; pta += l+1;
			cp2[i][0] = 0;
			for( int j = 1; j <= l; ++j )
				cp2[i][j] = cp2[i][j-1] + ip2[i*j];
		}

		for( int i = 2; i <= N3; ++i ) //此题只给了 64 M 空间， 一些减少空间的技巧 
			if( len[i] == 0 )
				for( int j = i; j <= N3; j += i )
					len[j] ++;
		
		for( int i = 1; i <= N3; ++i ) //此题只给了 64 M 空间， 一些减少空间的技巧 
			pri[i] = pta, pta += len[i];
						 
		for( int i = 2; i <= N3; ++i ) //此题只给了 64 M 空间， 一些减少空间的技巧 
			if( pd[i] == 0 )
			for( int j = i; j <= N3; j += i )
				pri[j][pd[j]++] = i;
		
		return Solve( R ) - Solve( L - 1 );
	}
};

