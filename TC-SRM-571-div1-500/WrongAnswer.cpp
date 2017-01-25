#include <vector>
#include <string>
#define ll long long
#define INF 10000000
using namespace std;
class MagicMolecule{
public:
	int n,v[51];
	ll G[51];
	int max(int a,int b){return a>b?a:b;}
	int dfs(ll S,int m){
		if(!S)return m>0?-INF:0;
		if(__builtin_popcountll(S)<m)return-INF;
		int x=0;while(!(S>>x&1))++x;
		if(!(G[x]&S))return dfs(S-(1ll<<x),m-1)+v[x];
		return max(dfs(S-(1ll<<x),m),dfs(S&~(1ll<<x|G[x]),m-1)+v[x]);
	}
	int maxMagicPower(vector <int> magicPower, vector <string> magicBond){
		n=magicPower.size();
		for(int i=0;i<n;i++)v[i]=magicPower[i];
		for(int i=0;i<n;i++)
			for(int j=G[i]=0;j<n;j++)if(i!=j&&magicBond[i][j]=='N')G[i]|=1ll<<j;
		int ans=dfs((1ll<<n)-1,2*(n+1)/3);
		return ans<0?-1:ans;
	}
};
