#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int mo=1000000007;
map<int,int>ha;
int f[55][1<<16],d[2][1<<16],w[55],a[1<<16],b[1<<16],tot,m;
vector<int>v[55],z[1<<16];

void dfs(int x){
	for(int i=0;i<v[x].size();++i)dfs(v[x][i]);
	int *g=d[0],*h=d[1];
	memset(g,0,(1<<m)<<2);g[0]=1;
	for(int i=0;i<v[x].size();++i){//背包 
		int u=v[x][i];
		memset(h,0,(1<<m)<<2);
		for(int j=1;j<=tot;++j){
			int s=a[j];
			for(int k=0;k<z[s].size();++k)
				h[s]=(h[s]+LL(f[u][z[s][k]])*g[s^z[s][k]])%mo;
		}
		swap(h,g);
	}
	memcpy(f[x],g,(1<<m)<<2);
	if(x!=51){
		for(int i=tot;i>=1;--i){ 
			int s=a[i];
			for(int j=0;j<m;++j)if((s>>j)&1)f[x][s]=(f[x][s]+f[x][s^(1<<j)])%mo;
			//不是根的话可以放在某个位置 
		}
	}
}

class SimilarNames {
public:
	int count(vector <string> names, vector <int> info1, vector <int> info2) {
		sort(names.begin(),names.end());
		for(int i=0;i<names.size();++i){
			int p=51;
			for(int j=i-1;j>=0;--j)
				if(names[i].substr(0,names[j].size())==names[j]){p=j;break;}//前缀 
			v[p].push_back(i);//建成树 
		}
		int n=names.size();
		for(int i=0;i<info1.size();++i){
			if(!ha.count(info1[i]))ha[info1[i]]=m++;
			if(!ha.count(info2[i]))ha[info2[i]]=m++;//把特殊的位置标号 
		}
		for(int s=0;s<1<<m;++s){
			bool flag=1;
			for(int i=0;i<info1.size();++i)
			if(((s>>ha[info1[i]])&1)&&!((s>>ha[info2[i]])&1))flag=0;
			if(flag)a[++tot]=s,b[s]=tot;//存下合法的状态 
		}
		for(int s=0;s<1<<m;++s)if(b[s])
			for(int s0=s;;s0=(s0-1)&s){
				if(b[s0]&&b[s^s0])z[s].push_back(s0);//合法的子集 
				if(!s0)break;
			}
		dfs(51);
		LL ret=f[51][(1<<m)-1];
		for(int i=1;i<=n-m;++i)ret=ret*i%mo;//其他位置可以随意放 
		return int(ret);
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
