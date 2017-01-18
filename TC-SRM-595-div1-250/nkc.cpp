#include<iostream>
#include<cstdio>
#include<vector>
#define N 1010
#define ll long long
using namespace std;
int a[N];
bool f[N];
struct LittleElephantAndIntervalsDiv1
{
ll getNumber(int m,vector<int> l,vector<int> r)
{
	for(int i=0;i<l.size();i++) for(int j=l[i];j<=r[i];j++) a[j]=i+1;
	ll ans=1;
	for(int i=1;i<=m;i++) if(a[i]&&!f[a[i]]) f[a[i]]=true,ans*=2;
	return ans;
}
};