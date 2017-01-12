#include <bits/stdc++.h>

using namespace std;

const int dx[]={0,-1,0,1},dy[]={1,0,-1,0};
int R,C,d[55][55][55][55],X[555],Y[555],n,g[555][555];
double zh[555];
vector<string>mp;
void dfs(int sx,int sy,int x,int y,int px,int py,int dist){//求出两点间距离 
	d[sx][sy][x][y]=dist;
	for(int i=0;i<4;++i){
		int xx=x+dx[i],yy=y+dy[i];
		if(0<=xx&&xx<R&&0<=yy&&yy<C&&mp[xx][yy]!='#'&&(xx!=px||yy!=py))dfs(sx,sy,xx,yy,x,y,dist+1);
	}
}

class Orienteering {
public:
	double expectedLength(vector <string> field, int K) {
		mp=field;
		R=mp.size();C=mp[0].size();
		for(int i=0;i<R;++i)
			for(int j=0;j<C;++j)if(mp[i][j]!='#')dfs(i,j,i,j,-1,-1,0);
		for(int i=0;i<R;++i)
			for(int j=0;j<C;++j)if(mp[i][j]=='*'){
				++n;X[n]=i;Y[n]=j;
			}
		zh[n]=1;
		for(int i=n-1;i>=0;--i)zh[i]=zh[i+1]*(i+1-K)/(i+1);//c(i,k)/c(n,k)
		double r1=0,r2=0;
		for(int i=0;i<R;++i)
			for(int j=0;j<C;++j)
			if(mp[i][j]!='#')
				for(int k=0;k<2;++k){
					int x=i+dx[k],y=j+dy[k],z=0;
					if(0<=x&&x<R&&0<=y&&y<C&&mp[x][y]!='#'){
						for(int l=1;l<=n;++l)
						if(d[X[l]][Y[l]][x][y]<d[X[l]][Y[l]][i][j])++z;//两部分的结点数 
						r1+=1-zh[z]-zh[n-z];
					}
				}
		zh[n-2]=1;
		for(int i=n-3;i>=0;--i)zh[i]=zh[i+1]*(i+3-K)/(i+1);//c(i,k-2)/c(n-2,k-2);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)g[i][j]=d[X[i]][Y[i]][X[j]][Y[j]];
		for(int i=1;i<=n;++i)
			for(int j=i+1;j<=n;++j){
				int l=0;
				for(int k=1;k<=n;++k){
					if(k==i||k==j)continue;
					if(g[i][k]>g[i][j]||(g[i][k]==g[i][j]&&k<j))continue;
					if(g[j][k]>g[i][j]||(g[j][k]==g[i][j]&&k<i))continue;//要求(i,j)最小 
					++l;
				}
				r2+=g[i][j]*zh[l];
			}
		return 2*r1-r2*K*(K-1)/(n-1)/n;//2*边数-最远距离 
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
