#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int A[32][32], B[32][32];
int L[32][2000], R[32][2000];

void cmax(int &a, int b) {if(a < b) a = b;}

class FoxAndFlowerShopDivOne
{
	
	int solve(vector<string> inp, int lim)
	{
		const int N = inp.size(), M = inp[0].size();
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= M; ++j)
			{
				A[i][j] = (inp[i - 1][j - 1] == 'L') + A[i][j - 1];
				B[i][j] = (inp[i - 1][j - 1] == 'P') + B[i][j - 1];
			}
		memset(L[0], -63, sizeof L[0]);
		for(int i = 1; i <= N; ++i)
		{
			memcpy(L[i], L[i - 1], sizeof L[i]);
			for(int l = 1; l <= M; ++l)
				for(int r = l; r <= M; ++r)
				{
					int a = 0, b = 0;
					for(int h = i; h >= 1; --h)
					{
						a += A[h][r] - A[h][l - 1];
						b += B[h][r] - B[h][l - 1];
						cmax(L[i][a - b + 1000], a + b);
					}
				}
		}
		memset(R[N + 1], -63, sizeof R[N + 1]);
		for(int i = N; i >= 1; --i)
		{
			memcpy(R[i], R[i + 1], sizeof R[i]);
			for(int l = 1; l <= M; ++l)
				for(int r = l; r <= M; ++r)
				{
					int a = 0, b = 0;
					for(int h = i; h <= N; ++h)
					{
						a += A[h][r] - A[h][l - 1];
						b += B[h][r] - B[h][l - 1];
						cmax(R[i][a - b + 1000], a + b);
					}
				}
		}
		int A = -1;
		for(int i = 1; i != N; ++i)
			for(int a = -N * M; a <= N * M; ++a)
				for(int b = -N * M; b <= N * M; ++b)
					if(-lim <= a + b && a + b <= lim)
						cmax(A, L[i][a + 1000] + R[i + 1][b + 1000]);
		return A;
	}
	
public:
	int theMaxFlowers(vector<string> inp, int lim)
	{
		const int N = inp.size(), M = inp[0].size();
		int A1 = solve(inp, lim);
		vector<string> ano(M, string(N, ' '));
		for(int i = 0; i != N; ++i)
			for(int j = 0; j != M; ++j)
				ano[j][i] = inp[i][j];
		int A2 = solve(ano, lim);
		return max(A1, A2);
	}
}	user;
