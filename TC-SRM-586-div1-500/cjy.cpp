#include<bits/stdc++.h>
#define vs vector <string>
using namespace std;
class History
{
	int G(string s,int&j)
	{
		int r=0;
		while(s[j]>47&&s[j]<58)r=r*10+s[j]-48,j++;
		return r;
	}
	public:
		string verifyClaims(vs a,vs b,vs q)
		{
			string s="";
			int n=a.size(),i,l,j,c[50][50],t[50],d[50][50],Q=q.size(),k,m=b.size();
			for(i=0;i<n;i++)
			{
				for(j=0;j<n;j++)d[i][j]=-1<<29;
				l=a[i].size();
				t[i]=0;
				for(j=0;j<l;j++)c[i][t[i]++]=G(a[i],j);
			}
			for(i=1;i<m;i++)b[0]=b[0]+b[i];
			m=b[0].size();
			for(i=0;i<m;i++)
			{
				int x=b[0][i]-'A',u=i+1,e=G(b[0],u),y=b[0][++u]-'A',v=u+1,f=G(b[0],v);
				i=v;
				d[x][y]=max(d[x][y],c[y][f]+1-c[x][e+1]);
				d[y][x]=max(d[y][x],c[x][e]+1-c[y][f+1]);
			}
			for(k=0;k<n;k++)for(i=0;i<n;i++)for(j=0;j<n;j++)d[i][j]=max(d[i][j],d[i][k]+d[k][j]);
			for(i=0;i<Q;i++)
			{
				int x=q[i][0]-'A',u=1,e=G(q[i],u),y=q[i][++u]-'A',v=u+1,f=G(q[i],v);
				if(d[x][y]>c[y][f+1]-1-c[x][e]||d[y][x]>c[x][e+1]-1-c[y][f])s=s+'N';else s=s+'Y';
			}
			return s;
		}
};
