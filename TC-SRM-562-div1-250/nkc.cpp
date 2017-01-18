#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int col[110][110];
long long tot[4],make[4];
struct PastingPaintingDivOne
{
	int judge(char c)
	{
		if(c=='R') return 1;
		if(c=='G') return 2;
		return 3;
	}
	vector<long long> countColors(vector <string> clipboard, int T)
	{
		int n=clipboard.size(),m=clipboard[0].size();
		int i,j,k,x,y;
		vector<long long>ans;
		if(T<=min(n,m))//T很小的时候直接暴力做 
		{
			for(k=0;k<T;k++)
			{
				for(i=0;i<n;i++)
				for(j=0;j<m;j++)
				if(clipboard[i][j]!='.')
				{
					if(col[i+k][j+k]) tot[col[i+k][j+k]]--;
					tot[judge(clipboard[i][j])]++;
					col[i+k][j+k]=judge(clipboard[i][j]);
				}
			}
			ans.push_back(tot[1]);
			ans.push_back(tot[2]);
			ans.push_back(tot[3]);
			return ans;
		}
		else//T很大的情况 
		{
			for(k=0;k<min(n,m);k++)//先做前min(n,m)步 
			{
				for(i=0;i<n;i++)
				for(j=0;j<m;j++)
				if(clipboard[i][j]!='.')
				{
					if(col[i+k][j+k]) tot[col[i+k][j+k]]--;
					tot[judge(clipboard[i][j])]++;
					col[i+k][j+k]=judge(clipboard[i][j]);
				}
			}
			//后面每步对答案的贡献都一样，只算一步乘起来即可 
			for(i=0;i<n;i++)
			for(j=0;j<m;j++)
			if(clipboard[i][j]!='.')
			{
				if(col[i+k][j+k]) make[col[i+k][j+k]]--;
				make[judge(clipboard[i][j])]++;
			}
			ans.push_back(tot[1]+make[1]*(T-min(n,m)));
			ans.push_back(tot[2]+make[2]*(T-min(n,m)));
			ans.push_back(tot[3]+make[3]*(T-min(n,m)));
			return ans;
		}
	}
};