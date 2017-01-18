#include<iostream>
#include<cstdio>
#include<vector>
#define N 15
#define dd double
using namespace std;
int n,x,y,a[N][N],d[N],f[N],q[N];
dd ans;
string s;
bool ch(int x)
{
	for(int i=0;i<n;i++) if(!(x&d[i])) for(int j=i+1;j<n;j++) if(!(x&d[j])&&!a[i][j]) return false;
	return true; 
}
struct BoundedOptimization
{
double maxValue(vector<string> c,vector<int> L,vector<int> R,int m)
{
	n=L.size();
	d[0]=1;
	for(int i=1;i<=n;i++) d[i]=d[i-1]*2;
	for(int i=0;i<c.size();i++) s+=c[i];
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='+') a[x][y]=a[y][x]=1,x=y=0;
		else if(!x) x=s[i]-'a';
		else y=s[i]-'a';
	}
	a[x][y]=a[y][x]=1;
	for(int i=0;i<d[n];i++)
	if(ch(i))
	for(int j=i;;j--)
	{
		if(j<0) break;
		j&=i;
		dd sum=0,o=m,t=0;
		int u=n;
		for(int p=0;p<n;p++)
		if(i&d[p])
		{
			u--;
			f[p]=j&d[p]?L[p]:R[p];
			o-=f[p];
		}
		if(o<0) continue;
		for(int p=0;p<n;p++)
		if(!(i&d[p]))
		{
			q[p]=0;
			for(int r=0;r<n;r++) if(i&d[r]&&a[p][r]) q[p]+=f[r];
			t+=q[p]+o/2;
		}
		t=(o-t)/u;
		bool flag=true;
		for(int p=0;p<n;p++)
		if(!(i&d[p]))
		{
			dd w=q[p]+o/2+t;
			if(w<L[p]||w>R[p])
			{
				flag=false;
				break;
			}
			sum+=w*(q[p]+(o-w)/2);
		}
		if(!flag) continue;
		for(int p=0;p<n;p++) if(i&d[p]) for(int r=p+1;r<n;r++) if(i&d[r]&&a[p][r]) sum+=f[p]*f[r];
		ans=max(ans,sum);
	}
	return ans;
}
};