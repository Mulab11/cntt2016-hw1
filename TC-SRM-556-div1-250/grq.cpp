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
vi c;
bool vis[N],now[N],go[N][N];
int dep[N],n,ans;
struct bi{
	int a[10];
	void clear(){memset(a,0,sizeof(a));}
	void ins(int x){
		for(int i=9;i>=0;i--){
			if(!(x&(1<<i))) continue;
			if(!a[i]){a[i]=x;break;} else x^=a[i];
		}
	}
	int get(int x){
		for(int i=9;i>=0;i--)
			if(!(x&(1<<i))&&a[i]) x^=a[i];
		return x;
	}
}test;

void dfs(int x){
	vis[x]=now[x]=1;
	for(int y=0;y<n;y++){
		if(y==x||!go[x][y]) continue;
		if(vis[y]){
			if(now[y]) test.ins(dep[y]^dep[x]^c[y]);
			continue;
		}
		dep[y]=dep[x]^c[y];
		dfs(y);
	}
	now[x]=0;
}

class XorTravelingSalesman{
public:
	int maxProfit(vector <int> cityValues, vector <string> roads){
		n=cityValues.size();c=cityValues;
		test.clear();
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(roads[i][j]=='Y') go[i][j]=1; else go[i][j]=0;
		memset(vis,0,sizeof(vis));
		dep[0]=c[0];dfs(0);
		int ans=0;
		for(int i=0;i<n;i++) ans=max(ans,test.get(dep[i]));
		return ans;
	}
};
