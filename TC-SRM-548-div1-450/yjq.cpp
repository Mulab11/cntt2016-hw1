#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3010;

int cnt[MAXN];

class KingdomAndDice {
public:
	double newFairness( vector <int> a, vector <int> b, int X )
	{
		sort( b.begin(), b.end() );
		int n = a.size(), m = 0, sum = 0;
		for ( int i = 0; i < n; i++ )
			if ( a[i] )
				sum += lower_bound( b.begin(), b.end(), a[i] ) - b.begin();
			else
				++m;
		for ( int i = 1; i <= n * n; i++ )
			cnt[i] = m + 1;
		for ( auto p = b.begin(); p != b.end(); p++ )
		{
			int	l	= (*p) + 1, r = ( (p + 1) == b.end() ) ? X : (*(p + 1) ) - 1, num = p - b.begin() + 1;
			int	co	= r - l + 1;
			for ( int j = 0; j < a.size(); j++ )
				if ( a[j] >= l && a[j] <= r )
					--co;
			for ( int j = 0; j < min( co, m ); j++ )
				for ( int v = n * n; v >= num; v-- )
					cnt[v] = min( cnt[v], cnt[v - num] + 1 );
		}
		double tmp = 1.1, ans;
		for ( int v = 0; v <= n * n; v++ )
			if ( cnt[v] <= m )
			{
				double cur = fabs( (v + sum) / (double(n) * n) - 0.5 );
				if ( cur - tmp < -1e-9 )
					tmp = cur, ans = (v + sum) / (double(n) * n);
			}
		return(ans);
	}
};

