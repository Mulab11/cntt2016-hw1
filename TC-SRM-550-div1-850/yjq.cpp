#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

const int MAXN = 20;

int	l;
int	tn[MAXN][MAXN], N;
int	A[MAXN << 2][MAXN << 2], B[MAXN << 2][MAXN << 2], tmpF[MAXN << 2][MAXN << 2];


void cong( int x[MAXN << 2][MAXN << 2], int y[MAXN << 2][MAXN << 2] )
{
	memset( tmpF, 0, sizeof(tmpF) );
	for ( int i = 0; i <= N; ++i )
		for ( int j = 0; j <= N; ++j )
			if ( x[i][j] )
				for ( int k = 0; k <= N; ++k )
					if ( y[j][k] )
						( tmpF[i][k] += (long long) x[i][j] * y[j][k] % MOD ) %= MOD;
	memcpy( x, tmpF, sizeof(tmpF) );
	return;
}

int cnt[3] ; 
class ConversionMachine {
public:
	int countAll( string s1, string s2, vector<int> cv, int M )
	{
		l = s1.length();
		int	sum	= 0;
		for ( int i = 0; i < l; ++i )
		{
			int tmp = 0;
			while ( s1[i] != s2[i] )
			{
				tmp++;
				M -= cv[s1[i] - 'a'];
				s1[i]++;
				if ( M < 0 )
					return(0);
				if ( s1[i] == 'd' )
					s1[i] = 'a';
			}
			sum += tmp;
			cnt[tmp]++;
		}
		int t = 0;
		for ( int i = 0; i < 3; ++i )
			t += cv[i];
		sum += M / t * 3;
		for ( int i = 0; i <= l; ++i )
			for ( int j = 0; i + j <= l; ++j )
				tn[i][j] = N++;
		A[0][tn[cnt[0]][cnt[1]]] = 1;
		for ( int i = 0; i <= l; ++i )
			for ( int j = 0; i + j <= l; ++j )
			{
				if ( i )
					B[tn[i][j]][tn[i - 1][j]] = i;
				if ( j )
					B[tn[i][j]][tn[i + 1][j - 1]] = j;
				if ( i + j < l )
					B[tn[i][j]][tn[i][j + 1]] = l - i - j;
			}
		B[tn[l][0]][N]	= 1;
		B[N][N]		= 1;
		while ( sum )
		{
			if ( sum & 1 )
				cong( A, B );
			cong( B, B );
			sum >>= 1;
		}
		return( (A[0][tn[l][0]] + A[0][N]) % MOD);
	}
};

