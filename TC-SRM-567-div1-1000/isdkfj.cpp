#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int mo=1000000009;
int h[11],n,m,qj[11][2],a[12][55];
map<vector<int>,int>dp;

int dfs(int x){
	if(x==0)return 1;
	vector<int>tmp;
	tmp.push_back(x);
	for(int i=1;i<=m;++i)tmp.push_back(a[x][i]);
	if(dp.find(tmp)!=dp.end())return dp[tmp];//记忆化 
	int&ret=dp[tmp];
	if(!qj[x][0]){//不可见 
		LL sum=0;
		for(int i=1;i<=m;++i)if(a[x][i]>=h[x])++sum;//可以放的位置 
		memcpy(a[x-1],a[x],sizeof a[x]);
		return ret=sum*dfs(x-1)%mo;
	}
	int l=1,r=m,s=qj[x][0],t=qj[x][1],w=h[x]-1-a[x][s];
	if(w<0)return ret=0;
	if(s-w>l)l=s-w;if(s+w<r)r=s+w;//左端点可见 
	if(s!=1){ 
		w=h[x]-a[x][s-1];//左端点左边不可见 
		if(s-1+w>l)l=s-1+w;
	}
	w=h[x]-1-a[x][t]; 
	if(w<0)return ret=0;
	if(t-w>l)l=t-w;if(t+w<r)r=t+w;//右端点可见 
	if(t!=m){
		w=h[x]-a[x][t+1];//右端点右边不可见 
		if(t+1-w<r)r=t+1-w;
	}
	for(int i=l;i<=r;++i){
		memcpy(a[x-1],a[x],sizeof a[x]);
		for(int j=max(i+1-h[x],1);j<=i;++j)
		if(a[x-1][j]<h[x]-i+j)a[x-1][j]=h[x]-i+j;
		for(int j=i+1;j<=h[x]+i-1&&j<=m;++j)
		if(a[x-1][j]<h[x]+i-j)a[x-1][j]=h[x]+i-j;//更新覆盖的高度 
		if((ret+=dfs(x-1))>=mo)ret-=mo;
	}
	return ret;
}

class Mountains {
public:
	int countPlacements(vector <int> heights, vector <string> visibility) {
		n=heights.size();
		for(int i=1;i<=n;++i)h[i]=heights[i-1];
		for(int i=1;i<=n;++i){//求可见的区间 
			for(int j=0;j<visibility[i-1].size();++j)if(visibility[i-1][j]=='X'){qj[i][0]=j+1;break;}
			if(qj[i][0]){
				for(int j=qj[i][0];j<visibility[i-1].size();++j)if(visibility[i-1][j]=='-'){qj[i][1]=j;break;}
				if(!qj[i][1])qj[i][1]=visibility[i-1].size();
			}
		}
		m=visibility[0].size();//宽度 
		return dfs(n);
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
