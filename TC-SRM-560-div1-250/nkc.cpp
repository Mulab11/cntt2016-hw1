#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int n,m,s,f[60],ans;
struct TomekPhone
{
int minKeystrokes(vector<int> a,vector<int> b)
{
	n=a.size();
	m=b.size();
	sort(a.begin(),a.end());
	for(int i=0;i<m;i++) for(int j=1;j<=b[i];j++) f[j]++,s++;
	if(s<n) return -1;
	int now=1;
	for(int i=n-1;~i;i--)
	{
		ans+=now*a[i];
		f[now]--;
		while(!f[now]) now++;
	}
	return ans;
}
};