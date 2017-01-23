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
int cnt[N],g[N][N];

class PenguinSledding{
public:
	long long countDesigns(int n, vector<int> a, vector<int> b){
		memset(cnt,0,sizeof(cnt));
		memset(g,0,sizeof(g));
		for(int i=0;i<a.size();i++) g[a[i]][b[i]]=g[b[i]][a[i]]=1,cnt[a[i]]++,cnt[b[i]]++;
//		for(int i=1;i<=n;i++) pr
		ll ans=1-n-(ll)a.size();
		for(int i=1;i<=n;i++) ans+=1ll<<cnt[i];
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				for(int k=j+1;k<=n;k++)
					ans+=g[i][j]&&g[i][k]&&g[k][j];
		return ans;
	}
};
