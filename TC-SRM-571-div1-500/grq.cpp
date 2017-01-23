#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int N=55;
vi a;
vector<string> go;
int ans,n,m,k,u[N*N],v[N*N];
bool vis[N];

void dfs(int x,int r,int now){
	if(r>n/3) return;
	if(now<ans) return;
	if(x==m){
		ans=max(ans,now);
		return;
	}
	if(!vis[u[x]]||!vis[v[x]]) dfs(x+1,r,now);
	else{
		vis[u[x]]=0;dfs(x+1,r+1,now-a[u[x]]);vis[u[x]]=1;
		vis[v[x]]=0;dfs(x+1,r+1,now-a[v[x]]);vis[v[x]]=1;		
	}
}

class MagicMolecule{
public:
	int maxMagicPower(vector<int> magicPower, vector<string> magicBond){
		a=magicPower;go=magicBond;
		n=a.size();m=k=0;
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++)
				if(go[i][j]=='N') u[m]=i,v[m++]=j;
		for(int i=0;i<n;i++) k+=a[i];
		memset(vis,-1,sizeof(vis));
		ans=-1;dfs(0,0,k);
		return ans;
	}
};

