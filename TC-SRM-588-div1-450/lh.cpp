#include<ctime>
#include<cstdio>
#include<cstring>
#include<sstream>
#include<fstream>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=20;

namespace Solve{
	int n;
	int id[maxn],cost[maxn][2],w[maxn][3];
	int a,b,c;
	bool vis[maxn];
	inline int f(){
		for (int i=0;i<n;++i) id[i]=i;
		int ret=a+b+c;
		for (int i=0;i<3000000;++i){
			random_shuffle(id,id+n);
			int x=a,y=b,z=c;
			memset(vis,0,sizeof(vis));
	//		printf("i=%d")
			for (;;){
				bool fl=false;
				for (int k=0;k<n;++k) if (!vis[id[k]]){
					int rec1=x,rec2=y,rec3=z;
					if (x<cost[id[k]][0]){
						if (x+z<cost[id[k]][0]) continue;
						z-=cost[id[k]][0]-x;
						x=0;
					}
					else x-=cost[id[k]][0];
					if (y<cost[id[k]][1]){
						if (y+z<cost[id[k]][1]){
							x=rec1;
							y=rec2;
							z=rec3;
							continue;
						}
						z-=cost[id[k]][1]-y;
						y=0;
					}
					else y-=cost[id[k]][1];
					x+=w[id[k]][0];
					y+=w[id[k]][1];
					z+=w[id[k]][2];
					fl=true;
					ret=max(ret,x+y+z);
					vis[id[k]]=true;
					break;
				}
				if (!fl) break;
			}
		}
		return ret;
	}
}

class KeyDungeonDiv1{
	public:
	int maxKeys(vector<int> dr,vector<int> dg,vector<int> rr,vector<int> rg,vector<int> rw,vector<int> keys){
		using namespace Solve;
		a=keys[0];
		b=keys[1];
		c=keys[2];
		n=dr.size();
		for (int i=0;i<n;++i){
			cost[i][0]=dr[i];
			cost[i][1]=dg[i];
			w[i][0]=rr[i];
			w[i][1]=rg[i];
			w[i][2]=rw[i];
		}
		return f();
	}
};
