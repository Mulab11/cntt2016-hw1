#include <vector>
#include <string>
#include <algorithm>
#define INF 100000000000000ll
using namespace std;
class SkiResorts{
public:
	int N,a[51];
	long long G[51][51],D[51];
	bool vis[51];
	long long diff(long long x,long long y){return x>y?x-y:y-x;}
	long long minCost(vector <string> road, vector <int> altitude){
		N=road.size();
		for(int i=0;i<N;i++)a[i]=altitude[i],D[i]=INF;
		sort(a,a+N);
		long long ans=INF;
		for(int T=0;T<N;T++){
			for(int i=0;i<N;i++)
				for(int j=0;j<N;j++)G[i][j]=road[i][j]=='Y'?diff(altitude[i],a[T]):INF;
			for(int i=0;i<N;i++)
				D[i]<G[N-1][i]?G[N-1][i]=D[i]:1,D[i]=INF,vis[i]=0;
			D[N-1]=0;
			for(int t=N;t--;){
				int i=0;for(int j=1;j<N;j++)!vis[j]&&D[j]<D[i]?i=j:1;
				vis[i]=1;for(int j=0;j<N;j++)!vis[j]&&D[i]+G[i][j]<D[j]?D[j]=D[i]+G[i][j]:1;
			}
			if(vis[0]&&D[0]+diff(altitude[0],a[T])<ans)ans=D[0]+diff(altitude[0],a[T]);
		}
		return ans==INF?-1:ans;
	}
};
