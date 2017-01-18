#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
struct ThreeColorability
{
	char A[51][51];
	int f[51][51],F[51][51];
	int col[51];
	int n,m;
	bool dfs(int x,int C)
	{
		int i,j;
		col[x]=C;
		for(i=1;i<=n;i++)
		if(i!=x&&f[i][x])
		{
		//	cout<<i<<'!'<<f[i][x];
			if(f[i][x]==1)
			{
				if(!col[i]) dfs(i,3-C);
				else if(col[i]!=3-C) return false;
			}
			else
			{
				if(!col[i]) dfs(i,C);
				else if(col[i]!=C) return false;
			}
		}
		return true;
	}
	bool check()
	{
		int i,j;
		for(i=1;i<=n;i++)
		col[i]=0;
		for(i=1;i<=n;i++)
		if(!col[i])
		if(!dfs(i,1)) return false;
		return true;
	}
	vector <string> lexSmallest(vector <string> cells)
	{
		n=cells.size(),m=cells[0].size();
		int i,j,k;
		for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		A[i+1][j+1]=cells[i][j];
		vector<string>ans;
		for(k=1;k<=m;k++)
		for(i=1;i<n;i++)
		for(j=i+1;j<=n;j++)
		if(A[i][k]!='?'&&A[j][k]!='?')
		{
			if(A[i][k]==A[j][k])
			{
				if(f[i][j]==1) return ans;
				f[i][j]=f[j][i]=2;
			}
			else
			{
				if(f[i][j]==2) return ans;
				f[i][j]=f[j][i]=1;
			}
		}
		if(!check()) return ans;
		for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
		if(A[i][j]=='?')
		{
			memcpy(F,f,sizeof(F));
			bool fl=true;
			for(k=1;k<=n;k++)
			if(i!=k&&A[k][j]!='?')
			{
				if(A[k][j]=='N')
				{
					if(f[i][k]==1) fl=false;
					else f[i][k]=f[k][i]=2;
				}
				else
				{
					if(f[i][k]==2) fl=false;
					else f[i][k]=f[k][i]=1;
				}
			}
		//	if(i==1&&j==1)cout<<f[2][1]<<' '<<f[3][2]<<' '<<f[3][1]<<' '<<fl;
			if(fl&&check()) A[i][j]='N';
			else
			{
				memcpy(f,F,sizeof(f));
				for(k=1;k<=n;k++)
				if(i!=k&&A[k][j]!='?')
				{
					if(A[k][j]=='Z')
					f[i][k]=f[k][i]=2;
					else f[i][k]=f[k][i]=1;
				}
				A[i][j]='Z';
			}
		}
		string S;
		for(i=1;i<=n;i++)
		{
			S="";
			for(j=1;j<=m;j++)
			S+=A[i][j];
			ans.push_back(S);
		}
		return ans;
	}
};
/*ThreeColorability P;
int main()
{
	vector<string>s;
	s.push_back("????NZ");
	s.push_back("???Z?N");
	s.push_back("N??Z??");
	s=P.lexSmallest(s);
	cout<<s[0];
}*/