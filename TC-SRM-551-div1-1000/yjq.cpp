#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

typedef long long LL;

const int MAXN = 60;

vector<int>	v1[MAXN], v2[MAXN];
int		n, m, ans, top;
int		way[MAXN], mp[MAXN][MAXN], du[MAXN], tree[MAXN], C[MAXN][MAXN], st[MAXN];
int get( int x, int y, int mx )
{
	int ret = 0;
	if ( x > n / 2 || y > n - n / 2 )
		return(0);
	for ( int i = 0, j = v2[y].size() - 1; i < v1[x].size(); i++ )
	{
		while ( j >= 0 && v2[y][j] + v1[x][i] > mx )
			j--;
		ret = (ret + j + 1) % MOD;
	}
	return(ret);
}


void ade( int x, int y )
{
	du[x]++; du[y]++;
	mp[x][y] = mp[y][x] = MOD - 1;
}


int qpow( int x, int y )
{
	int ret = 1;
	while ( y )
	{
		if ( y & 1 )
			ret = (LL) ret * x % MOD;
		x = (LL) x * x % MOD; y >>= 1;
	}
	return(ret);
}


int solve( int n )
{
	int cnt = 0;
	for ( int i = 0; i < n; i++ )
	{
		int pos = -1;
		for ( int j = i; j < n; j++ )
			if ( mp[j][i] )
				pos = j;
		if ( pos == -1 )
			return(0);
		if ( pos != i )
			cnt++;
		for ( int j = 0; j < n; j++ )
			swap( mp[pos][j], mp[i][j] );
		for ( int j = i + 1; j < n; j++ )
			if ( mp[j][i] )
			{
				int t = (LL) qpow( mp[i][i], MOD - 2 ) * mp[j][i] % MOD;
				for ( int k = i; k < n; k++ )
					mp[j][k] = (mp[j][k] - (LL) mp[i][k] * t % MOD + MOD) % MOD;
			}
	}
	int ret = 1;
	for ( int i = 0; i < n; i++ )
		ret = (LL) ret * mp[i][i] % MOD;
	return(cnt & 1 ? MOD - ret : ret);
}


class SweetFruits
{
public:
	int countTrees( vector<int>val, int mx )
	{
		n = val.size();
		for ( int i = 0; i <= n; i++ )
			C[i][0] = 1;
		for ( int i = 1; i <= n; i++ )
			for ( int j = 0; j <= i; j++ )
				C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
		for ( int i = 0; i < n; i++ )
			if ( val[i] != -1 )
				st[top++] = val[i];
		for ( int i = 0; i < 1 << (top / 2); i++ )
		{
			int cnt = 0, sum = 0;
			for ( int j = 0; j < top / 2; j++ )
				if ( i >> j & 1 )
					cnt++, sum += st[j];
			v1[cnt].push_back( sum );
		}
		for ( int i = 0; i < 1 << (top - top / 2); i++ )
		{
			int cnt = 0, sum = 0;
			for ( int j = 0; j < (top - top / 2); j++ )
				if ( i >> j & 1 )
					cnt++, sum += st[j + top / 2];
			v2[cnt].push_back( sum );
		}
		for ( int i = 0; i <= n / 2; i++ )
			sort( v1[i].begin(), v1[i].end() );
		for ( int i = 0; i <= n - n / 2; i++ )
			sort( v2[i].begin(), v2[i].end() );
		for ( int i = 0; i < n; i++ )
			if ( val[i] != -1 )
				m++;
		for ( int i = 0; i <= m; i++ )
		{
			for ( int j = 0; j <= i; j++ )
				way[i] = (way[i] + get( j, i - j, mx ) ) % MOD;
			memset( mp, 0, sizeof(mp) );
			memset( du, 0, sizeof(du) );
			for ( int j = 0; j < i; j++ )
			{
				for ( int k = j + 1; k < i; k++ )
					ade( j, k );
				for ( int k = m; k < n; k++ )
					ade( j, k );
			}
			for ( int j = i; j < m; j++ )
				for ( int k = m; k < n; k++ )
					ade( j, k );
			for ( int j = m; j < n; j++ )
				for ( int k = j + 1; k < n; k++ )
					ade( j, k );
			for ( int j = 0; j < n; j++ )
				mp[j][j] += du[j];
			tree[i] = solve( n - 1 );
			for ( int j = 0; j < i; j++ )
				tree[i] = (tree[i] - (LL) tree[j] * C[i][j] % MOD + MOD) % MOD;
			ans = (ans + (LL) tree[i] * way[i] % MOD) % MOD;
		}
		return(ans);
	}
};

