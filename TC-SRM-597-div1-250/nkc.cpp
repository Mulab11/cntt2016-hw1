#include<iostream>
#include<cstdio>
#define N 60
using namespace std;
int n,f[N];
struct LittleElephantAndString
{
int getNumber(string a,string b)
{
	n=a.size();
	for(int i=0;i<n;i++) f[a[i]-64]++,f[b[i]-64]--;
	for(int i=1;i<=26;i++) if(f[i]) return -1;
	for(int i=n;i;i--)
	{
		int now=n-i;
		for(int j=0;j<n;j++) if(now<n&&a[j]==b[now]) now++;
		if(now==n) return n-i;
	}
}
};