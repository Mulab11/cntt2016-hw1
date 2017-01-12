#include <bits/stdc++.h>

using namespace std;

const int inf=0x3f3f3f3f;
int f[1<<16][55],g[55][55],l[55],r[55],c[55];
int get(int x){//1的个数 
	int ret=0;
	while(x)x-=x&-x,++ret;
	return ret;
}

class TravellingPurchasingMan {
public:
	int maxStores(int N, vector <string> interestingStores, vector <string> roads) {
		int m=interestingStores.size();
		memset(g,0x3f,sizeof g);
		for(int i=0;i<N;++i)g[i][i]=0;
		for(int i=0;i<roads.size();++i){
			stringstream ss(roads[i]);
			int x,y,z;
			ss>>x;ss>>y;ss>>z;
			g[x][y]=g[y][x]=z;
		}//读入 
		for(int k=0;k<N;++k)
			for(int i=0;i<N;++i)
				for(int j=0;j<N;++j)
				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);//floyd
		for(int i=0;i<m;++i){
			stringstream ss(interestingStores[i]);
			ss>>l[i];
			ss>>r[i];
			ss>>c[i];
		}//读入 
		memset(f,0x3f,sizeof f);
		for(int i=0;i<m;++i)if(g[N-1][i]<=r[i])
			f[1<<i][i]=max(g[N-1][i],l[i])+c[i];//初始化 
		int ans=0;
		for(int s=0;s<(1<<m);++s)
			for(int i=0;i<m;++i)
			if(f[s][i]!=inf){
				ans=max(ans,get(s));
				for(int j=0;j<m;++j)//枚举不在s中的点j 
				if(!((s>>j)&1)&&f[s][i]+g[i][j]<=r[j])
					f[s|(1<<j)][j]=min(f[s|(1<<j)][j],max(f[s][i]+g[i][j],l[j])+c[j]);
			}
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
