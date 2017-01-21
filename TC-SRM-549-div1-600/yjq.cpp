#include <bits/stdc++.h>

using namespace std;

int n, m;

const int MAXN = 13;

int tmpr[MAXN], tmpc[MAXN];

int pw[MAXN], pos[MAXN][2], dp[1600000];

int cnt = 0, c_cnt = 0, tot = 0;

int dfs( int x, int now, int mask )
{
	if ( now > c_cnt )
		return(1 << 30);
	if ( ~dp[mask] )
		return(dp[mask]);
	if ( x > cnt )
	{
		if ( now != c_cnt )
			return(1 << 30);
		for ( int i = 0; i < n; i++ )
			if ( tmpr[i] & 1 )
				return(1 << 30);
		for ( int i = 0; i < m; i++ )
			if ( tmpc[i] & 1 )
				return(1 << 30);
		return(0);
	}
	dp[mask] = 0;
	for ( int i = 0, nmask = mask; i < cnt; i++, nmask /= 3 )
		if ( !(nmask % 3) )
		{
			int ret_1 = dfs( x + 1, now, mask + 2 * pw[i] );
			tmpr[pos[i][0]]++, tmpc[pos[i][1]]++;
			int ret_2 = dfs( x + 1, now + 1, mask + pw[i] ) + (x <= tot);
			tmpr[pos[i][0]]--, tmpc[pos[i][1]]--;
			if ( x > tot )
			{
				dp[mask] = min( ret_1, ret_2 );
				break;
			}
			dp[mask] = max( dp[mask], min( ret_1, ret_2 ) );
		}
	return(dp[mask]);
}


class MagicalHats
{
public:
	int findMaximumReward( vector<string> mp, vector<int> a, int M )
	{
		n	= mp.size(), m = mp[0].length();
		c_cnt	= a.size();
		pw[0]	= 1;
		for ( int i = 1; i < 13; i++ )
			pw[i] = pw[i - 1] * 3;
		for ( int i = 0; i < n; i++ )
			for ( int j = 0; j < m; j++ )
				if ( mp[i][j] == 'H' )
					pos[cnt++][0] = i, pos[cnt - 1][1] = j, tmpr[i]++, tmpc[j]++;
		memset( dp, 255, sizeof dp );
		tot = M;
		int v = dfs( 1, 0, 0 );
		if ( v > cnt )
			return(-1);
		int ans = 0;
		sort( a.begin(), a.end() );
		for ( int i = 0; i < v; i++ )
			ans += a[i];
		return(ans);
	}
};


