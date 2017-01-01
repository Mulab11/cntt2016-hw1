#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int f[111]={};int n;int m;
int g[111]={};bool cmpp(int m,int n){return m>n;}
int h[1111]={},tot=0;
class TomekPhone
{
public:
	int minKeystrokes(vector <int> frequencies, vector <int> keySizes)
	{
		n=frequencies.size(),m=keySizes.size();
		for(int i=0;i<n;i++)
			f[i]=frequencies[i];
		for(int i=0;i<m;i++)
			g[i]=keySizes[i];
		sort(f,f+n,cmpp);
		for(int i=0;i<m;i++)
			for(int j=1;j<=g[i];j++)
				h[tot++]=j;
		sort(h,h+tot);
		if(n>tot)return -1;
		int ans=0;
		for(int i=0;i<n;i++)
			ans+=f[i]*h[i];
		return ans;
	}
};
