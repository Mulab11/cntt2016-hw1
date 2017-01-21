#include <bits/stdc++.h>
using namespace std;
int		L, R, S, n, g[6], b[6];
vector<int>	a;
void dfs( int x )
{
	int i = 0, j, k, s, t, U[6] = { 0 }, D[6] = { 0 }, f[64] = { 0 };
	if ( x == n )
	{
		for (; i < n; i++ )
			for ( j = 0; j < n; j++ )
				if ( b[i] >> j & 1 )
					U[i]++, D[j]++;
		for ( i = 0; i < n; i++ )
			if ( a[i] < U[i] || a[i] < D[i] )
				return;
		for ( i = 1; i < 1 << n; i++ )
		{
			for ( k = -1, j = s = t = 0; j < n; j++ )
				if ( i >> j & 1 )
					s += a[j] - U[j], t |= b[j], k = k < 0 ? g[j] : k != g[j] ? 0 : k;
			for ( j = 0; j < n; j++ )
				if ( t >> j & 1 )
					s -= a[j] - D[j];
			if ( k && s > 0 )
				return;
		}
		for ( f[i = 0] = 1; i < 1 << n; i++ )
		{
			for ( t = j = 0; j < n; j++ )
				if ( i >> j & 1 )
					t |= b[j];
			for ( j = 0; j < n; j++ )
				if ( (i >> j & 1) && !(t >> j & 1) )
					f[i] += f[i - (1 << j)];
		}
		S += L <= f[i - 1] && f[i - 1] <= R;
	}else if ( g[x] )
		for (; i < 1 << n; i++ )
		{
			for ( j = 0; j < n; j++ )
				if ( (i >> j & 1) && g[j] != g[x] - 1 )
					goto E2;
			b[x] = i, dfs( x + 1 ); E2 :;
		}
	else b[x] = 0, dfs( x + 1 );
}


void dfs1( int x )
{
	if ( x == n )
		dfs( 0 );
	else for ( int i = 0; i < n; i++ )
			g[x] = i, dfs1( x + 1 );
}


class CosmicBlocks
{
public:
	int getNumOrders( vector<int> _, int l, int r )
	{
		return(n = _.size(), a = _, L = l, R = r, dfs1( 0 ), S);
	}
};
