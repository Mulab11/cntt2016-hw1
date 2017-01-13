#include<bits/stdc++.h>
#define A(a,b,c) E[a].push_back({b,c}),E[b].push_back({a,c})
using namespace std;
int n,i,j,k,m,l[99],r[99],d[99],v[99],c[99],y,f;
vector<pair<int,int> >E[99];
int D(int x)
{
	v[x]=1;
	for(auto p:E[x])if(y=p.first,f=c[x]^p.second,v[y]){if(c[y]^f)return 0;}else if(c[y]=f,!D(y))return 0;
	return 1;
}
struct DisjointSemicircles
{
	public:
		string getPossibility(vector<int> a)
		{
			for(n=a.size();i<a.size();i++)if(~a[i])
			{
				if(!d[a[i]])d[a[i]]=++m;
				l[d[a[i]]]?r[d[a[i]]]=i+1:l[d[a[i]]]=i+1;
			}
			for(i=0;i<1<<m;i++)
			{
				for(j=0;j<=n;j++)c[j]=v[j]=0,E[j].clear();
				for(A(0,n,0),j=1;j<=m;j++)
				{
					for(k=j+1;k<=m;k++)if((i>>j-1&1)==(i>>k-1&1)&&((r[k]>l[j]&&r[k]<r[j])^(l[k]>l[j]&&l[k]<r[j])))goto S;
					f=i>>j-1&1;A(l[j]-1,l[j],f);A(r[j]-1,r[j],f);A(l[j]-1,r[j],!f&&(r[j]-l[j]+1&1));
				}
				for(j=0;j<=n;j++)if(!v[j]&&!D(j))goto S; 
				return"POSSIBLE";S:;
			}return"IMPOSSIBLE";
		}
};
