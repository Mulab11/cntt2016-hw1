#include <bits/stdc++.h>

typedef long long LL;

using namespace std;
vector<string>	S;
string		s;
LL		f, i, j, z;
char getC( LL x, LL y ) {
	if ( z = x - y >> 1, x < y || (x - y) % 2 || y + z >= f || (y + z & z) != z )
		return('.');
	return(y + z & 1 ? 'B' : 'A');
}


class CheckerExpansion {
public:
	vector<string> resultAfter( LL _, LL x, LL y, LL w, LL h ) {
		for ( f = _; i < h; S.push_back( s ), i++ )
			for ( s = "", j = 0; j < w; j++ )
				s += getC( x + j, y + h - i - 1 );
		return(S);
	}
};

