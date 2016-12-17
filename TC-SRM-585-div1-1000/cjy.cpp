#include<bits/stdc++.h>
using namespace std;
vector<int> x,y;
int n,m,K,x0,Y0,t0,x1,Y1,t1,x2,y2,t2,f[1<<19],g[1<<19],i,j,k;
long long s[1<<19],S;
void ne(int&x,int&y){if(!y&&x<m)x++;else if(x==m&&y<m)y++;else if(y==m&&x)x--;else if(y>0&&!x)y--;}
int ca(int x1,int Y1,int x2,int y2){for(int i=0;i<K;i++)if(1ll*(x2-x1)*(y[i]-Y1)-1ll*(x[i]-x1)*(y2-Y1)<0)return 0;return 1;}
class EnclosingTriangle
{
	public:
		long long getNumber(int M,vector<int> X,vector<int> Y)
		{
			for(K=X.size(),x=X,y=Y,m=M,n=4*m,x1=x2=m,t1=t2=m+1,i=1;i<n;ne(j,k),f[i]=t1,s[i]=s[i-1]+t1,g[i++]=t2)
			{
				while(t1<n)if(ne(x0=x1,Y0=Y1),ca(j,k,x0,Y0))x1=x0,Y1=Y0,t1++;else break;
				while(t2<=n&&!ca(x2,y2,j,k))ne(x2,y2),t2++;
			}
			for(i=t0=1;i<n;S+=max(f[f[i]]-max(g[i],f[i]+1)+1,0),i++)
			{
				while(t0<=n&&f[t0]<g[i])t0++;
				if(j=max(i+1,t0),k=f[i]-1,j<=k)S+=s[k]-s[j-1]-1ll*(g[i]-1)*(k-j+1);
			}
			return S;
		}
};
