#include<vector>
#include<algorithm>
#include<string>
using namespace std;
int f[5555555]={},g[5111555]={};
bool vis[11111111]={};
class MayTheBestPetWin
{
public:
	int calc(vector <int> A, vector <int> B)
	{
		int n=A.size();
		for(int i=0;i<n;i++)
			f[i]=A[i],g[i]=B[i];
		int ta=0,tb=0;
		vis[0]=1;
		for(int i=0;i<n;i++)
		{
			tb+=g[i],ta+=f[i];
			for(int j=ta+tb;j>=f[i]+g[i];j--)
				vis[j]|=vis[j-f[i]-g[i]];
		}
		int codeforces=989898989;
		for(int i=0;i<=ta+tb;i++)
			if(vis[i])
				codeforces=min(codeforces,max(tb-i,i-ta));
		return codeforces;
	}
};
