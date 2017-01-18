#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 51
using namespace std;
struct Excavations
{
	vector<int>V[N],ELSE;
	bool can[N];
	long long f[N][N],c[N][N];
	long long count(vector <int> kind, vector <int> depth, vector <int> found, int K)
	{
		int n=kind.size();
		int i,j,k,l,x,y;
		for(i=0;i<=50;i++)
		{
			c[i][0]=1;
			for(j=1;j<=i;j++)
			c[i][j]=c[i-1][j-1]+c[i-1][j];
		}
		for(i=0;i<found.size();i++)
		can[found[i]]=true;
		//没找到的等价，推入ELSE
		for(i=0;i<n;i++)
		{
			if(can[kind[i]])
			V[kind[i]].push_back(depth[i]);
			else ELSE.push_back(depth[i]);
		}
		sort(ELSE.begin(),ELSE.end());
		//分别排序 
		for(i=1;i<=50;i++)
		if(can[i])
		{
			if(V[i].size()==0) return 0;
			sort(V[i].begin(),V[i].end());
		}
		long long ans=0;
		for(l=0;l<ELSE.size();l++)
		{
			x=ELSE[l]-1;
			int free=ELSE.size()-l-1;
			memset(f,0,sizeof(f));
			f[0][0]=1;
			for(i=1;i<=50;i++)
			{
				if(!can[i])
				{
					for(j=0;j<=K;j++)
					f[i][j]=f[i-1][j];
				}
				else
				{
					y=0;
					while(y!=V[i].size()&&V[i][y]<=x) y++;
					free+=V[i].size()-y;
					for(j=0;j<=K;j++)
					{
						for(k=1;k<=min(j,y);k++)
						f[i][j]+=f[i-1][j-k]*c[y][k];
					}
				}
			}
			for(i=0;i<K;i++)
			ans+=f[50][i]*c[free][K-1-i];
		}
		//至少选一个没找到的，按照所有选的没找到的最小值进行不重复计算 
		memset(f,0,sizeof(f));
		f[0][0]=1; 
		for(i=1;i<=50;i++)
		{
			if(!can[i])
			{
				for(j=0;j<=K;j++)
				f[i][j]=f[i-1][j];
			}
			else
			{
				for(j=0;j<=K;j++)
				{
					for(k=1;k<=V[i].size()&&k<=j;k++)
					f[i][j]+=f[i-1][j-k]*c[V[i].size()][k];
				}
			}
		}
		ans+=f[50][K];
		//只选找到的种类的方案数 
		return ans;
 	}
};
/*int main()
{
	Excavations P;
	vector<int>V1,V2,V3;
	V1.push_back(1);V1.push_back(1);V1.push_back(2);V1.push_back(2);
	V2.push_back(10);V2.push_back(15);V2.push_back(10);V2.push_back(20);
	V3.push_back(1);
	cout<<P.count(V1,V2,V3,2);
}*/