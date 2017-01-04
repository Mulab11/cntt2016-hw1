#include<algorithm>
#include<vector>
using namespace std;
long long codeforces=0;int n,m;
struct ff{int x,y;}f[11111]={};
bool g[55][55]={};
class PenguinSledding
{
public:
	long long countDesigns(int numCheckpoints, vector <int> checkpoint1, vector <int> checkpoint2)
	{
		n=numCheckpoints;
		m=checkpoint1.size();
		for(int i=0;i<m;i++)
			f[i].x=checkpoint1[i],f[i].y=checkpoint2[i];
		for(int i=0;i<m;i++)
			g[f[i].x][f[i].y]=g[f[i].y][f[i].x]=1;
		for(int i=1;i<=n-2;i++)
			for(int j=i+1;j<=n-1;j++)
				for(int k=j+1;k<=n;k++)
					if(g[i][j]&&g[j][k]&&g[i][k])codeforces++;
		for(int i=1;i<=n;i++)
		{
			long long temp=1;
			for(int j=1;j<=n;j++)
				if(i!=j&&g[i][j])
					temp*=2;
			codeforces+=temp;
		}
		return codeforces-m-n+1;
	}
};
