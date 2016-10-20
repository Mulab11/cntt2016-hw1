#include <bits/stdc++.h>

using namespace std;

class TheSwapsDivOne
{
public:
	double find(vector<string> seq,int k)
	{
		static double val[5005];
		int n = 0;	
		for(int i = 0;i < seq.size();i ++)
			for(int j = 0;j < seq[i].length();j ++) val[++ n] = seq[i][j] - 48;
		static double p[1000005],g[1000005];
		g[0] = 1.0;
		//f[i][j][k]=the probability that position i moves to poisition j after k turns
		//p[k] = f[i][j][k] (i != j),g[k] = f[i][i][k]
		for(int i = 1;i <= k;i ++)
		{
			p[i] = (p[i - 1] * (n - 1) * (n - 2) / 2 + g[i - 1] + (n - 2) * p[i - 1]) / (n * (n - 1) / 2);
			g[i] = 1 - (n - 1) * p[i];
		}
		double ans = 0,all = 0;
		for(int i = 1;i <= n;i ++)
		{
			for(int j = 1;j <= n;j ++)
				ans += val[j] * (i != j ? p[k] : g[k]) * (i * (n - i + 1));
			all += n - i + 1;
		}
		return ans / all;
	}
};