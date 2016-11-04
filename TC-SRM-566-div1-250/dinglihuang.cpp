#include<vector>
using namespace std;

class PenguinSledding{
	public:
	bool a[51][51];
	int d[51];
	long long countDesigns(int n,vector<int> x,vector<int> y){
		int m=x.size();
		for(int i=0;i<m;i++){
			a[x[i]][y[i]]=a[y[i]][x[i]]=1;
			d[x[i]]++;d[y[i]]++;
		}
		long long ans=1+m;
		for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)if(a[i][j])for(int k=j+1;k<=n;k++)if(a[j][k]&&a[k][i])ans++;
		for(int i=1;i<=n;i++)ans+=(1LL<<d[i])-1-d[i];
		return ans;
	}
};