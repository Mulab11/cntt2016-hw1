#include<map>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
map<long long,long long>mp;
int g[55]={};
int a[55]={};int n;
bool check(int s,int t)
{
	if(a[s]==0)return 0;
	long long temp=0;
	for(int i=s;i<=t;i++)
		temp=temp*2+a[i];
	return mp[temp];
}
class CuttingBitString
{
	public:
	int getmin(string S)
	{
		n=S.size();
		for(int i=0;i<n;i++)
			a[i+1]=S[i]-'0';
		for(int i=1;i<=n;i++)
			g[i]=444;
		for(long long i=1;i<=3e+17;i=i*5)
			mp[i]=1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=i;j++)
				if(check(j,i))
					g[i]=min(g[i],g[j-1]+1);
		if(g[n]==444)g[n]=-1;
		return g[n];
	}
};
