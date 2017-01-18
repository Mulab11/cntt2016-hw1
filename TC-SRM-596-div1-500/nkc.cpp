#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define N 60
#define ll long long
using namespace std;
int n,m,w[70];
bool flag;
vector<ll> a,c;
void get()
{
	ll x=0;
	for(int i=0;i<m;i++)
	{
		bool f=false;
		for(int j=0;j<60;j++)
		if(a[i]&1ll<<j&&w[j]==1)
		{
			f=true;
			w[j]++;
			x+=1ll<<j;
			break;
		}
		if(!f)
		{
			flag=true;
			return;
		}
	}
	int s=0;
	if(n-m-1)
	for(int i=0;i<60;i++)
	if(!w[i])
	{
		x+=1ll<<i;
		w[i]++;
		if(++s==n-m-1) break;
	}
	if(s!=n-m-1)
	{
		flag=true;
		return;
	}
	a.push_back(x);
	m++;
}
struct BitwiseAnd
{
vector<ll> lexSmallest(vector<ll> b,int NN)
{
	a=b;
	n=NN;
	m=b.size();
	for(int i=0;i<m;i++)
	for(int j=i+1;j<m;j++)
	{
		if(!(a[i]&a[j])) return c;
		for(int k=j+1;k<m;k++) if((a[i]&a[j]&a[k])>0) return c;
	}
	for(int i=0;i<m;i++) for(int j=0;j<60;j++) if(a[i]&1ll<<j) w[j]++;
	while(m<NN)
	{
		get();
		if(flag) return c;
	}
	sort(a.begin(),a.end());
	return a;
}
};