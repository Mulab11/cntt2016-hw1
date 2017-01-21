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
#define pq priority_queue
#define rf random_shuffle
#define np next_permutation
#define lb lower_bound
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int N=55;
int n,m,a[N][N],match[N];
bool vis[N];

bool hungary(int x){
	for(int i=1;i<=m;i++){
		if(!a[x][i]) continue;
		if(vis[i]) continue;
		vis[i]=1;
		if(!match[i]||hungary(match[i])){match[i]=x;return 1;}
	}
	return 0;
}

class PointyWizardHats{
public:
	int getNumHats(vector <int> topHeight, vector <int> topRadius, vector <int> bottomHeight, vector <int> bottomRadius){
		n=topHeight.size();m=bottomHeight.size();
		int ans=0;
		memset(a,0,sizeof(a));
		memset(match,0,sizeof(match));
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(topHeight[i]>bottomHeight[j]*topRadius[i]/bottomRadius[j]&&topRadius[i]<bottomRadius[j]) a[i+1][j+1]=1;
		for(int i=1;i<=n;i++){
			memset(vis,0,sizeof(vis));
			ans+=hungary(i);
		}
		return ans;
	}
};
