#include <bits/stdc++.h>

using namespace std;


bool check( vector<int> a, int lim )
{
	int lst = 0;
	for ( int i = 0, n = a.size(); i < n; i++ )
	{
		int cur = a[i];
		if ( cur > lst )
			lst = max( lst + 1, cur - lim );
		else {
			if ( cur + lim <= lst )
				return(0);
			lst++;
		}
	}
	return(1);
}


class KingdomAndTrees {
public:

	int minLevel( vector<int> a )
	{
		int l = 0, r = int(1e9) + 5, tmp = 0;
		while ( l <= r )
		{
			int mid = l + r >> 1;
			if ( check( a, mid ) )
				tmp = mid, r = mid - 1;
			else l = mid + 1;
		}
		return(tmp);
	}
};

