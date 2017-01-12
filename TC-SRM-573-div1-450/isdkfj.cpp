#include <bits/stdc++.h>

using namespace std;

int n,m,ra[55],a[55];
long long dp[55][55];
bool inq[55][55];

class SkiResorts {
public:
	long long minCost(vector <string> road, vector <int> altitude) {
		n=altitude.size();
		for(int i=0;i<n;++i)ra[i+1]=altitude[i];
		sort(ra+1,ra+n+1);
		m=unique(ra+1,ra+n+1)-ra-1;
		for(int i=0;i<n;++i)a[i]=lower_bound(ra+1,ra+m+1,altitude[i])-ra;//高度离散化 
		memset(dp,0x3f,sizeof dp);
		for(int i=1;i<=m;++i)dp[0][i]=abs(ra[i]-ra[a[0]]);//初始化 
		queue<pair<int,int> >q;
		for(int i=1;i<=m;++i)q.push(make_pair(0,i)),inq[0][i]=1;
		while(!q.empty()){//spfa
			pair<int,int>x=q.front();
			q.pop();
			inq[x.first][x.second]=0;
			for(int i=0;i<n;++i)
			if(road[x.first][i]=='Y')
				for(int j=1;j<=x.second;++j)
				if(dp[x.first][x.second]+abs(ra[a[i]]-ra[j])<dp[i][j]){
					dp[i][j]=dp[x.first][x.second]+abs(ra[a[i]]-ra[j]);
					if(!inq[i][j]){
						inq[i][j]=1;
						q.push(make_pair(i,j));
					}
				}
		}
		long long ans=0x3f3f3f3f3f3f3f3fll;
		for(int i=1;i<=m;++i)ans=min(ans,dp[n-1][i]);
		if(ans==0x3f3f3f3f3f3f3f3fll)ans=-1;//不可达 
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
