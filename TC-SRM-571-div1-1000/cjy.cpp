#include<bits/stdc++.h>
#define LD long double
#define D(a,b,x,y) sqrt((LD)(a-x)*(a-x)+(LD)(b-y)*(b-y))
using namespace std;
int n,i,u,v[50];
LD l[50],h[50],d,l1,h1;
queue<int> Q;
class CandyOnDisk
{
	public:
		string ableToAchieve(vector<int> x,vector<int> y,vector<int> r,int sx,int sy,int tx,int ty)
		{
			if(sx==tx&&sy==ty)return"YES";
			for(n=x.size();i<n;i++)if(d=D(sx,sy,x[i],y[i]),d<=r[i])l[i]=h[i]=d,Q.push(i),v[i]=1;else l[i]=1e9,h[i]=0;
			while(!Q.empty())for(v[u=Q.front()]=0,Q.pop(),i=0;i<n;i++)
			{
				if(d=D(x[u],y[u],x[i],y[i]),x[u]==x[i]&&y[u]==y[i])l1=l[u],h1=min(h1,(LD)r[i]);else l1=max(d-r[u],(LD)0),h1=min(d+r[u],(LD)r[i]);
				if(l1<=h1&&(l1<l[i]||h1>h[i]))if(l[i]=min(l[i],l1),h[i]=max(h[i],h1),!v[i])Q.push(i),v[i]=1;
			}
			for(i=0;i<n;i++)if(d=D(tx,ty,x[i],y[i]),l[i]<=d&&d<=h[i])return"YES";
			return"NO";
		}
};
