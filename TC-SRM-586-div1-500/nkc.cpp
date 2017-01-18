#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 26
using namespace std;
struct History
{
	string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries)
	{
		int n=dynasties.size();
		int i,j,k,x,y,xx,yy;
		int f[N][N];
		string S="";
		vector<int> D[N];
		for(i=0;i<dynasties.size();i++)
		{
			int now=0;
			for(j=0;j<dynasties[i].size();j++)
			{
				if(dynasties[i][j]==' ') D[i].push_back(now),now=0;
				else now=now*10+dynasties[i][j]-48;
			}
			D[i].push_back(now);
		}//把纪年法转成int 
		for(i=0;i<battles.size();i++)
		S+=battles[i];
		memset(f,0x3f,sizeof(f));
		for(i=0;i<n;i++)
		f[i][i]=0;
		for(i=0;i<S.size();i+=6)
		{
			x=S[i]-65;xx=S[i+1]-48;
			y=S[i+3]-65;yy=S[i+4]-48;
			f[y][x]=min(f[y][x],D[y][yy+1]-D[x][xx]-1);
			f[x][y]=min(f[x][y],D[x][xx+1]-D[y][yy]-1);//差分约束，建图跑最短路 
		}
		for(k=0;k<n;k++)
		for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		f[i][j]=min(f[i][j],f[i][k]+f[k][j]);//Floyd跑最短路 
		string ans="";
		for(i=0;i<queries.size();i++)
		{
			x=queries[i][0]-65;xx=queries[i][1]-48;
			y=queries[i][3]-65;yy=queries[i][4]-48;
			if(D[y][yy+1]-D[x][xx]-1<-f[x][y]||D[y][yy]-D[x][xx+1]+1>f[y][x]) ans+='N';
			else ans+='Y';//对应区间有交返回Y，否则返回N 
		}
		return ans;
	}
};