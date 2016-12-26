/*
对于一个点集S，令U\S中的点全都取了极值（lower或upper），那么假如存在i \in S,j \in S且i,j没有边相连，都没有取到极值，
那么设sum(i)=与i相连的点的权值和，sum(j)同理，设sum(i)<sum(j)，那么我们显然可以令val(i)减小，val(j)增加，这样始终更好，
那么相当于最终，要不S中的点两两有边，要不都取到了极值，后者相当于S=0的情况，考虑前者。我们枚举U\S中哪些点取了lower或upper，
对于i \in S，设a[i]=\sum_{j \in U\S,link[i][j]=1} val_j，M = max_sum - \sum_{j \in U \ S} val_j，那么M相当于S中的点的总权值，
对于i \in S,他的贡献就是val_i * (a_i + M - val_i)，那么S中的点的总贡献就是\sum_{i \in S} val_i * (a_i + (M - val_i) / 2)。
那么什么时候val_i是最优的呢？不妨假设我们令val_i + dx,val_j - dx后方案更优，那么必有val_j - a_j != val_i - a_i，换句话说，
当val_i取到极值时，有val_j - a_j = val_i - a_i，不妨设=c，那么就有val_i = a_i + m / 2 + c。令S={x_i}，
可以列出：val_{x_1}+...+val_{x_k}=M=a_{x_1}+...+a_{x_k}+kM/2+kc，解出c，就得到了所有的val，判断是否合法，更新答案即可。
*/
#include <bits/stdc++.h>

using namespace std;

class BoundedOptimization
{
public:
	bool lk[14][14];

	void get_lk(vector<string> a)
	{
		string tmp = "";
		for(int i = 0;i < a.size();i ++)
			tmp = tmp + a[i];
		for(int i = 0;i < tmp.length();i += 3)
		{
			int u = tmp[i] - 'a',v = tmp[i + 1] - 'a';
			lk[u][v] = lk[v][u] = 1;
		}
	}

	double maxValue(vector <string> expr, vector <int> lowerBound, vector <int> upperBound, int maxSum)
	{
		int n = lowerBound.size();
		get_lk(expr);
		double ans = 0;
		int full = (1 << n) - 1;
		//枚举一个团
		for(int s = 0;s < (1 << n);s ++)
		{
			bool cliq = 1;
			for(int i = 0;i < n;i ++)
				if (s & (1 << i))
					for(int j = 0;j < n;j ++)
						if (i != j && (s & (1 << j)) && !lk[i][j]) {cliq = 0;break;}
			if (!cliq) continue;
			//ups为取到上界的点，其他就是取下界的点
			for(int ups = full ^ s;;ups = (full ^ s) & (ups - 1))
			{
				static double val[15],a[15];
				double m = maxSum;
				for(int i = 0;i < n;i ++)
					if (!(s & (1 << i)))
					{
						if (ups & (1 << i)) val[i] = upperBound[i]; else
							val[i] = lowerBound[i];
						m -= val[i];
					} 
				//算出当前剩下的权值
				if (m < 0) continue;
				double lm = m;
				for(int i = 0;i < n;i ++)
					if (s & (1 << i))
					{
						a[i] = 0;
						for(int j = 0;j < n;j ++)
							if (!(s & (1 << j)) && lk[i][j]) a[i] += val[j];
						val[i] = a[i] + m / 2; 
						lm -= m / 2 + a[i];
					}
				bool ok = 1;
				for(int i = 0;i < n;i ++)
					if (s & (1 << i))
					{
						val[i] += lm / (__builtin_popcount(s));
						if (val[i] > upperBound[i] + 1e-8 || val[i] < lowerBound[i] - 1e-8) ok = 0; //要在范围内
					}
				if (!ok) 
				{
					if (!ups) break;
					continue;
				}
				double cur = 0;
				for(int i = 0;i < n;i ++)
					for(int j = i + 1;j < n;j ++)
						if (lk[i][j]) cur += val[i] * val[j]; //算答案
				ans = max(ans,cur);
				if (!ups) break;
			}
		}
		return ans;
	}
};
