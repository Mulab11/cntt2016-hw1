#include<algorithm>
#include<cstdio>
#include<vector>
int f[55]={};int n;int codeforces=0;
using namespace std;
bool vis[111]={};
class BinPacking
{
public:
	int minBins(vector <int> item)
	{
		n=item.size();
		for(int i=0;i<n;i++)
			f[i]=item[i];
		sort(f,f+n);
		for(int i=n-1;i>0;i--)
			if(vis[i])
				continue;
			else if(f[i]==100)
				break;
			else
				for(int j=i-1;j>=0;j--)
					if(f[i]+f[j]<=300&&!vis[j]){
						vis[i]=vis[j]=1;codeforces++;break;}
		int cnt=2;
		for(int i=0;i<n;i++)
			if(f[i]==100&&!vis[i])
				cnt++;
			else if(!vis[i]&&f[i]>100)
			codeforces++;
		return codeforces+cnt/3;
	}
}
;
