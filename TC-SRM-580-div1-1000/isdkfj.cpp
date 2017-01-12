#include <bits/stdc++.h>

using namespace std;

int n,m,mp[55][55],su[55][55];
struct info{
	int x,y,l,r;
	info(int x,int y,int l,int r):x(x),y(y),l(l),r(r){}
	bool operator<(const info&rhs)const{
		if(x!=rhs.x)return x<rhs.x;
		if(y!=rhs.y)return y<rhs.y;
		if(l!=rhs.l)return l<rhs.l;
		return r<rhs.r;
	}
};
map<info,int>f1,f2;
int get(int x,int l,int r){//计算一段的和 
	if(l==0)return su[x][r];
	return su[x][r]-su[x][l-1];
}

int dfs2(int x,int y,int l,int r);

int dfs1(int x,int y,int l,int r){
	info cur(x,y,l,r);
	if(f1.count(cur))return f1[cur];
	int&ret=f1[cur];
	if(y<l||y>=r)ret=mp[x+1][y]+dfs2(x+1,y,y,y);//直接往下走 
	else {
		ret=999999999;
		if(l>0)ret=min(ret,get(x,l-1,y-1)+dfs2(x,l-1,l,r));//走到最左边 
		if(r<m)ret=min(ret,get(x,y+1,r)+dfs2(x,r,l,r));//走到最右边 
	}
	return ret;
}

int dfs2(int x,int y,int l,int r){
	info cur(x,y,l,r);
	if(f2.count(cur))return f2[cur];
	int&ret=f2[cur];
	if(x==n-1)ret=0;//到最后一行了 
	else {
		ret=dfs1(x,y,l,r);//不动 
		if(r-l<m-1)ret=max(ret,dfs1(x,y,min(l,y),max(r,y+1)));//放满
	}
	return ret;
}

class WallGameDiv1 {
public:
	int play(vector <string> costs) {
		n=costs.size();
		m=costs[0].size();
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j){
				su[i][j]=mp[i][j]=costs[i][j]-'0';
				if(j)su[i][j]+=su[i][j-1];
			}
		int ans=999999999;
		for(int i=0;i<m;++i)//初始位置 
			ans=min(ans,mp[0][i]+dfs2(0,i,i,i));
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
