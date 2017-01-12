#include <bits/stdc++.h>

using namespace std;

int n,m,p[55];bool g[55][55],v[55];
bool xyl(int x){//匈牙利求最大匹配 
	for(int i=0;i<m;++i)if(g[x][i]&&!v[i]){v[i]=1;
		if(p[i]==-1||xyl(p[i])){p[i]=x;return 1;}}return 0;}
bool ck(int h1,int r1,int h2,int r2){//判断是否满足条件 
	return r1<r2&&h1*r2>r1*h2;
}

class PointyWizardHats {
public:
	int getNumHats(vector <int> topHeight, vector <int> topRadius, vector <int> bottomHeight, vector <int> bottomRadius) {
		n=topHeight.size(); m=bottomHeight.size();
		memset(p,-1,sizeof p);
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j)//建图 
			g[i][j]=ck(topHeight[i],topRadius[i],bottomHeight[j],bottomRadius[j]);
		int ans=0;
		for(int i=0;i<n;++i){
			memset(v,0,sizeof v);
			if(xyl(i))++ans;
		}
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
