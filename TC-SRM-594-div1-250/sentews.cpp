#include<algorithm>
#include<vector>
using namespace std;
long long f[111]={},g[111]={};
long long ff[111]={},gg[111]={};
int codeforces=0;int n,m;
void check(long long a,long long b)
{
	for(int i=0;i<n;i++)
		ff[i+1]=f[i]*b;
	for(int i=0;i<m;i++)
		gg[i+1]=g[i]*a;
	int h[55][55]={};
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(ff[i]==gg[j])
				h[i][j]=max(h[i][j],h[i-1][j-1]+1);
			else
				h[i][j]=max(h[i-1][j],h[i][j-1]);
	if(h[n][m]>codeforces)
		codeforces=h[n][m];
}
class AstronomicalRecords
{
public:
	int minimalPlanets(vector <int> A, vector <int> B)
	{
		n=A.size(),m=B.size();
		for(int i=0;i<n;i++)
			f[i]=A[i];
		for(int i=0;i<m;i++)
			g[i]=B[i];
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				check(f[i],g[j]);
		return n+m-codeforces;
	}
};
