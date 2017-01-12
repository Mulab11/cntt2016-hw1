#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

double Ava[MAXN][MAXN][MAXN][3],F[2][MAXN][MAXN][MAXN],Self[MAXN][3],Prb[MAXN];
int N;

class RockPaperScissors
{
public:
	double bestScore(vector <int> rockProb, vector <int> paperProb, vector <int> scissorsProb)
	{
		N = rockProb.size();
		for(int i = 1;i <= N;i ++)
		{
			Self[i][0] = rockProb[i - 1] / 300.0;
			Self[i][1] = scissorsProb[i - 1] / 300.0;
			Self[i][2] = paperProb[i - 1] / 300.0;
		}
		for(int i = 0;i <= N;i ++)
		{
			Prb[i] = 1;
			for(int j = i;j;j --)
				Prb[i] *= j / 1.0 / (N - j + 1); 
		}
		for(int i = 1;i <= N;i ++)
		{
			memset(F,0,sizeof F);
			F[1][0][0][0] = 1;
			int cr = 0;
			for(int j = 1;j <= N;j ++)
				if (i == j) continue; else
				{
					cr ^= 1;
					for(int a = 0;a <= j;a ++)
						for(int b = 0;a + b <= j;b ++)
							for(int c = 0;a + b + c <= j;c ++) F[cr ^ 1][a][b][c] = 0;
					for(int a = 0;a <= j;a ++)
						for(int b = 0;a + b <= j;b ++)
							for(int c = 0;a + b + c <= j;c ++)
								if (F[cr][a][b][c]) 
									//the probabilities that ith dice is in the bag when the status is (a,b,c) and now we are consider jth dice.
								{
									F[cr ^ 1][a + 1][b][c] += F[cr][a][b][c] * Self[j][0];
									F[cr ^ 1][a][b + 1][c] += F[cr][a][b][c] * Self[j][1];
									F[cr ^ 1][a][b][c + 1] += F[cr][a][b][c] * Self[j][2];
									F[cr ^ 1][a][b][c] += F[cr][a][b][c];
								}
				}
			cr ^= 1;
			for(int a = 0;a <= N;a ++)
				for(int b = 0;a + b <= N;b ++)
					for(int c = 0;a + b + c <= N;c ++)
						for(int ii = 0;ii < 3;ii ++)
						{
							double val = F[cr][a][b][c] * Prb[a + b + c] / (N - a - b - c); // the probability that (a,b,c) would throw out ith dice
							Ava[a][b][c][ii] += val * 3 * Self[i][(ii + 2) % 3] + val * Self[i][ii];
							//the scores that I will get if there are a rocks,b papers,c scissors in the bag and I choose to make decision ii
						}
		}
		double ans = 0;
		for(int a = 0;a <= N;a ++)
			for(int b = 0;a + b <= N;b ++)
				for(int c = 0;a + b + c <= N;c ++)
				{
					double mx = 0;
					for(int i = 0;i < 3;i ++) mx = max(mx,Ava[a][b][c][i]);
					ans += mx; //for every status,the contribution is independent
				}
		return ans;
	}
};
