#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
int f[310],ans;
struct BinPacking
{
int minBins(vector<int> a)
{
	for(int i=0;i<a.size();i++) f[a[i]]++;
	for(int i=300;i>100;i--)
	while(f[i])
	{
		ans++;
		f[i]--;
		for(int j=300-i;j>=100;j--)
		if(f[j])
		{
			f[j]--;
			break;
		}
	}
	if(f[100]) ans+=(f[100]-1)/3+1;
	return ans;
}
};