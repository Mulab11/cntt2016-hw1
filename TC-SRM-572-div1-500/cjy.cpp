#include<bits/stdc++.h>
using namespace std;
char S[10],s[10];
vector<int> a,e[10][60];
int n,m,i,j;
class EllysBulls//搜索，剪枝
{
	public:
		void dfs(int x,int f)
		{
			int j=0;
			char d,c=48;
			for(i=0;i<m;i++)if(a[i]<0||a[i]>n-x)return;
			if(x==n)if(S[0]||f>1)S[0]=1;else for(i=0;i<n;i++)S[i]=s[i];else
			for(;c<58;c++)if(e[x][c].size())
			{
				for(auto i : e[x][c])a[i]--;
				s[x]=c;dfs(x+1,f);
				for(auto i : e[x][c])a[i]++;
			}
			else j++,d=c;
			if(j)s[x]=d,dfs(x+1,f*j);
		}
		string getNumber(vector<string> x,vector<int> b)
		{
			for(n=x[0].size(),m=x.size(),a=b;i<n;i++)for(j=0;j<m;j++)e[i][x[j][i]].push_back(j);
			if(dfs(0,1),!S[0])return"Liar";
			if(S[0]<2)return"Ambiguity";
			return S;
		}
};
