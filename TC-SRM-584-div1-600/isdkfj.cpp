#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
int ra[55],tot,n;
LL f[55],g[55],h[55];
bool flag[55];

class Excavations {
public:
	long long count(vector <int> kind, vector <int> depth, vector <int> found, int K) {
		n=kind.size();
		for(int i=0;i<n;++i)ra[++tot]=depth[i];
		sort(ra+1,ra+tot+1);tot=unique(ra+1,ra+tot+1)-ra-1;
		for(int i=0;i<n;++i)depth[i]=lower_bound(ra+1,ra+tot+1,depth[i])-ra;//离散化 
		vector<int>a[55],b;
		for(int i=0;i<found.size();++i)flag[found[i]]=1;
		for(int i=0;i<n;++i)if(flag[kind[i]])a[kind[i]].push_back(depth[i]);//被发现的 
		else b.push_back(depth[i]);//没被发现的 
		LL ret=0;
		for(int d=1;d<=tot+1;++d){//最小的没被发现的深度 
			memset(f,0,sizeof f);
			f[0]=1;
			for(int i=0;i<found.size();++i){
				vector<int>&t=a[found[i]];
				memset(g,0,sizeof g);
				memset(h,0,sizeof h);
				h[0]=1;
				for(int j=0;j<t.size();++j)
				//g: 取到了<d的
				//h: 没取到 
					if(t[j]<d)for(int k=j+1;k>=1;--k)
						g[k]+=g[k-1]+h[k-1];
					else for(int k=j+1;k>=1;--k){
						g[k]+=g[k-1];
						h[k]+=h[k-1];
					}
				for(int j=n;j>=0;--j){
					f[j]=0;
					for(int k=1;k<=t.size()+1;++k)
					if(j-k>=0)f[j]+=f[j-k]*g[k];//枚举取了几个 
				}
			}
			memset(g,0,sizeof g);
			memset(h,0,sizeof h);
			h[0]=1;
			for(int i=0;i<b.size();++i)
			//g: 取到了d
			//h: 没取到d 
			if(b[i]>d)
				for(int j=n;j>=1;--j){
					g[j]+=g[j-1];
					h[j]+=h[j-1];
				}
			else if(b[i]==d)
				for(int j=n;j>=1;--j)g[j]+=g[j-1]+h[j-1];
			if(d<=tot)for(int i=0;i<=K;++i)ret+=f[i]*g[K-i];
			else for(int i=0;i<=K;++i)ret+=f[i]*h[K-i]; 
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
