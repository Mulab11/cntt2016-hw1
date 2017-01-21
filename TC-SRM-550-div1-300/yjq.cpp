#include <bits/stdc++.h>

using namespace std;

const int dx[4][2] = { { 1, 0 }, { 0, -1 }, { -1, 0 }, { 0, 1 } };

const int MAXN = 60 ; 

bool cov[MAXN][MAXN] ; 

class RotatingBot {
public:
	int minArea( vector<int> moves ) {
		int fs = moves.size();
		moves.resize ( 4, 0 );
		int		m = max( moves[0], moves[2] ), n = max( moves[1], moves[3] ), y = m - moves[0], x = n - moves[1];
		memset( cov, 0, sizeof cov );
		int D = 3;
		for ( int i = 0; i < fs; i++ ) {
			int curStep = 0;
			while (1) {
				cov[x][y] = 1;
				int nx = x + dx[D][0], ny = y + dx[D][1];
				if ( !(nx >= 0 && ny >= 0 && nx <= n && ny <= m && !cov[nx][ny]) )
					break;
				x = nx, y = ny;
				curStep ++ ; 
			}
			if ( curStep < moves[i] || (i != fs - 1 && curStep > moves[i]) )
				return(-1);
			D = (D + 1) % 4;
		}
		return( (n + 1) * (m + 1) );
	}
};
