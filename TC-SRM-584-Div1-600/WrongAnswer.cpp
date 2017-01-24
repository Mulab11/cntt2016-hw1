#include <vector>
#include <algorithm>
using namespace std;
class Excavations{
public:
	long long C[60][60],f[60][60];
	int tmp[60],cnt[60];
	struct item{int d,t;bool operator<(const item&it)const{return d<it.d||d==it.d&&t<it.t;}}S[60];
	long long count(vector <int> kind, vector <int> depth, vector <int> found, int K){
		int n=kind.size(),m=found.size();
		for(int i=0;i<=n;i++)
			for(int j=*C[i]=1;j<=i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
		for(int i=0;i<m;i++)tmp[found[i]]=i+1;
		for(int i=0;i<n;i++)S[i]=(item){depth[i],tmp[kind[i]]};
		sort(S,S+n);S[n].t=0;
		long long ans=0;
		bool need=1;
		for(int i=0;i<=n;i++){
			if(S[i].t)cnt[S[i].t]++,need=1;
			else{
				if(need){
					f[0][0]=1;
					for(int i=1;i<=m;i++)
						for(int j=0;j<=K;j++)
							for(int k=(f[i][j]=0)+1;k<=cnt[i]&&k<=j;k++)f[i][j]+=C[cnt[i]][k]*f[i-1][j-k];
					need=0;
				}
				if(i==n)ans+=f[m][K];
				else for(int x=0;x<K;x++)ans+=f[m][x]*C[n-i-1][K-x-1];
			}
		}
		return ans;
	}
};
