#include<bits/stdc++.h>
using namespace std;
int t[50][26],f[50],n,m,i,j,k,x;
vector<int> s;
class StringGame//每次挑选一个可用的元素来比较其他元素
{
	public:
		vector<int> getWinningStrings(vector<string> a)
		{
			for(n=a.size(),m=a[0].size();i<n;i++)for(j=0;j<m;j++)t[i][a[i][j]-97]++;
			for(x=0;x<n;x++)
			{
				for(memset(f,0,sizeof(f)),f[x]=k=1;k<27;k++)for(i=0;i<26;i++)
				{
					for(j=0;j<n;j++)if(!f[j]&&t[j][i]>t[x][i])goto E;
					for(j=0;j<n;j++)if(t[j][i]<t[x][i])f[j]=1;E:;
				}
				for(i=0;i<n;i++)if(!f[i])goto F;
				s.push_back(x);F:;
			}
			return s;
		}
};
