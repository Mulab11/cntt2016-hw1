#include<bits/stdc++.h>
using namespace std;
int d[1024][150],i,j,T,x,y,o,v[150];
vector<pair<int,int> >e[150];
string s;
void dij(int*d)
{
	int i=0,j,k;
	for(memset(v,0,sizeof(v));i<=T;i++)
	{
		for(k=-1,j=0;j<=T;j++)if(!v[j]&&(k<0||d[j]<d[k]))k=j;
		v[k]=1;
		for(auto E : e[k])d[E.first]=min(d[E.first],d[k]+E.second);
	}
}
class FoxTheLinguist
{
	public:
		int minimalHours(int n,vector<string> M)//最小树形图		
{
			T=n*10;memset(d,9,sizeof(d));o=d[0][0];
			for(;i<M.size();i++)s+=M[i];
			for(i=0;i<n;i++)d[1<<i][i*10+9]=0;
			for(i=0;i<s.size();i+=12)for(j=s[i+1]-'0';j<10;j++)e[(s[i+4]-'A')*10+s[i+5]-'0'].push_back(make_pair((s[i]-'A')*10+j,stoi(s.substr(i+7,4)))); 
			for(i=0;i<n;i++)e[i*10].push_back(make_pair(T,0));
			for(i=1;i<(1<<n);dij(d[i]),i++)for(j=0;j<=T;j++)for(auto E : e[j])
			{
				x=E.first;
				for(y=i&(i-1);y;y=i&(y-1))d[i][x]=min(d[i][x],d[y][x]+d[i&~y][j]+E.second);
			}
			return d[i-1][T]==o?-1:d[i-1][T];
		}	
};
