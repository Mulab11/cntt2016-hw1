#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<cmath>
using namespace std;

#define F(val) (lower_bound(secondDie.begin(),secondDie.end(),val)-secondDie.begin())

class KingdomAndDice
{
	public:
	int n,m,tot,cnt[55];
	set<int> ocr;
	
	bool f[55][55*55];
	
	double newFairness(vector<int> firstDie,vector<int> secondDie,int X)
	{
		n=firstDie.size();
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				tot+=firstDie[i]>secondDie[j];
		for(int i=0;i<n;i++)
			if(firstDie[i])ocr.insert(firstDie[i]);
				else m++;
		secondDie.push_back(0);
		secondDie.push_back(X+1);
		sort(secondDie.begin(),secondDie.end());
		//We divide all available numbers to some equivalence class.
		//Numbers in the same class have the same influence on p.
		for(int i=0;i+1<secondDie.size();i++)
		{
			cnt[i]=secondDie[i+1]-secondDie[i]-1;
			for(int j=0;j<n;j++)//There can't be equal numbers.
				if(secondDie[i]<firstDie[j]&&firstDie[j]<secondDie[i+1])
					cnt[i]--;
		}
		//Use a simple Multiple knapsack to solve it.
		f[0][0]=1;
		for(int p=0;p<secondDie.size()-1;p++)
			for(int i=m-1;~i;i--)
				for(int j=n*n;~j;j--)
					if(f[i][j])
						for(int k=1;i+k<=m&&k<=cnt[p];k++)
							f[i+k][j+k*p]=1;
		double ans=2,best=2;
		//Get the best p.
		for(int i=0;i<=m;i++)
			for(int j=0;j<=n*n;j++)
				if(f[i][j])
				{
					double w=double(tot+j)/(n*n),t=fabs(w-.5);
					if(t<best-1e-10||t<best+1e-10&&w<ans)ans=w,best=t;
				}
		return ans;
	}
};

