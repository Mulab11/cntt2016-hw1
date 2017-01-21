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

bool a[55][55],vis[55];
int n,match[55];

bool dfs(int x){
	for(int i=0;i<n;i++){
		if(vis[i]||!a[x][i]) continue;
		vis[i]=1;
		if(match[i]==-1||dfs(match[i])){
			match[i]=x;
			return 1;
		}
	}
	return 0;
}

class Incubator{
public:
	int maxMagicalGirls(vector <string> love){
		n=love.size();
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(love[i][j]=='Y') a[i][j]=1; else a[i][j]=0;
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					a[i][j]|=a[i][k]&a[k][j];
		int ans=0;
		memset(match,-1,sizeof(match));
		for(int i=0;i<n;i++){
			memset(vis,0,sizeof(vis));
			ans+=dfs(i);
		}
		return n-ans;
	}
};
