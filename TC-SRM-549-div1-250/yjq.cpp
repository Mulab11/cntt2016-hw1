#include <bits/stdc++.h>

using namespace std;

int n, m;

const int MAXN = 110;

bool mp[MAXN][MAXN], use[MAXN];

int fr[MAXN];

typedef long long LL;

bool check( LL a, LL b, LL c, LL d )
{
	if ( b > d )
		return(0);
	return(a * d > b * c);
}


bool dfs( int now )
{
	for ( int i = 0; i < m; i++ )
		if ( mp[now][i] && !use[i] )
		{
			use[i] = 1;
			if ( !fr[i] || dfs( fr[i] - 1 ) )
			{
				fr[i] = now + 1; return(1);
			}
		}
	return(0);
}


class PointyWizardHats
{
public:
	int getNumHats( vector<int> a, vector<int> b, vector<int> c, vector<int> d )
	{
		n = a.size(), m = d.size();
		for ( int i = 0; i < n; i++ )
			for ( int j = 0; j < m; j++ )
				mp[i][j] = check( a[i], b[i], c[j], d[j] );
		int ans = 0;
		for ( int i = 0; i < n; i++ )
		{
			memset( use, 0, sizeof use );
			ans += dfs( i );
		}
		return(ans);
	}
};

