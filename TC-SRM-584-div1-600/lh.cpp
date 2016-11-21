#include<cstdio>
#include<map>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class Excavations{
	private:
		static const int maxn=55;
		long long dp[maxn],fz[maxn];
		int num[maxn];
		int n,m;
		long long C[maxn][maxn];
		int id[maxn];
	public:
		static vector<int> dep,kd;
		static bool ex[maxn];
		static bool opt(int,int);
		
		long long count(vector <int> kind, vector <int> depth, vector <int> found, int K){
			kd=kind;
			long long ans=0;
			n=kind.size();
			m=found.size();
			dep=depth;
			
			memset(C,0,sizeof(C));
			memset(dp,0,sizeof(dp));
			memset(ex,0,sizeof(ex));
			C[0][0]=1;
			for (int i=1;i<=n;++i){
				C[i][0]=1;
				for (int j=1;j<=i;++j) C[i][j]=C[i-1][j-1]+C[i-1][j];
			}
			for (int i=0;i<m;++i) ex[found[i]]=true;
			
			for (int i=0;i<n;++i) id[i]=i;
			sort(id,id+n,opt);
//			for (int i=0;i<n;++i) printf("%d: type %d, deep %d\n",i,kind[id[i]],depth[id[i]]);
			
			for (int i=0;i<n;++i) if (ex[kind[id[i]]]){
				
				memset(num,0,sizeof(num));
				memset(dp,0,sizeof(dp));
				dp[0]=1;
				for (int j=0;j<i;++j) if (ex[kind[id[j]]]) ++num[kind[id[j]]];
				for (int j=0;j<m;++j){
					memcpy(fz,dp,sizeof(dp));
					memset(dp,0,sizeof(dp));
					int ttt=num[found[j]];
					if (found[j]==kind[id[i]]){
						for (int nn=0;nn<=ttt;++nn)
						for (int k=nn;k<=K;++k) dp[k]+=fz[k-nn]*C[ttt][nn];
					}
					else{
						for (int nn=1;nn<=ttt;++nn)
						for (int k=nn;k<=K;++k) dp[k]+=fz[k-nn]*C[ttt][nn];
					}
				}
//				if (i==11) for (int j=0;j<=K;++j) printf("dp[%d]=%lld\n",j,dp[j]);
				for (int j=i+1;j<n;++j) if (!ex[kind[id[j]]])
				if (depth[id[i]]<depth[id[j]]){
//					printf("");
					for (int k=1;k<=K-m;++k) ans+=dp[K-k-1]*C[n-j-1][k-1];
				}
				ans+=dp[K-1];
//				printf("i=%d,ans=%lld\n",i,ans);
			}
			return ans;
		}
};

vector<int> Excavations::dep,Excavations::kd;
bool Excavations::ex[maxn];
bool Excavations::opt(int a,int b){
	if (dep[a]!=dep[b]) return dep[a]<dep[b];
	return ex[kd[a]]<ex[kd[b]];
}

