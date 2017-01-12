#include <bits/stdc++.h>

using namespace std;

int n,g[55][55],col[55],v[55],su[55];
int w[55],tot,cnt;
struct seg{
	int l,r;
}b[55];
namespace task1{
	bool vv[55];
	int dfs(int x){//染色 
		v[x]=1;int ret=1;
		for(int i=1;i<=cnt;++i)if(g[x][i]){
			if(!v[i]){col[i]=col[x]^1;ret&=dfs(i);}
			else ret&=col[i]!=col[x];
		}
		return ret;
	}
	int lian(int x){
		if(x>tot){
			memset(v,0,sizeof v);
			for(int i=1;i<=cnt;++i)
				for(int j=i+1;j<=cnt;++j)
				g[i][j]=g[j][i]=!((b[i].l>b[j].l&&b[i].r<b[j].r)||(b[j].l>b[i].l&&b[j].r<b[i].r)||(b[i].r<b[j].l)||(b[i].l>b[j].r));
				//判断是否相交 
			for(int i=1;i<=cnt;++i)if(!v[i]){
				col[i]=0;if(!dfs(i))return 0;
			}
			return 1;
		}
		if(vv[x])return lian(x+1);//已经连过 
		vv[x]=1;
		for(int i=x+1;i<=tot;++i)if(!vv[i]){//枚举连谁 
			b[++cnt].l=w[x];
			b[cnt].r=w[i];vv[i]=1;
			if(lian(x+1))return 1;
			vv[i]=0;--cnt;
		}
		vv[x]=0;
		return 0;
	}
	int work(){return lian(1);}
}
namespace task2{
	int dfs(int x){//染色 
		v[x]=1;int ret=1;
		for(int i=0;i<=tot;++i)if(g[x][i]!=-1){
			if(!v[i])col[i]=col[x]^g[x][i],ret&=dfs(i);
			else if(col[i]!=(col[x]^g[x][i]))return 0;
		}
		return ret;
	}
	int work(){
		for(int s=0;s<(1<<cnt);++s){
			bool flag=1;
			for(int i=1;i<=cnt;++i)
				for(int j=i+1;j<=cnt;++j)
				if(!((b[i].l>b[j].l&&b[i].r<b[j].r)||(b[j].l>b[i].l&&b[j].r<b[i].r)||(b[i].r<b[j].l)||(b[i].l>b[j].r))&&((s>>(i-1))&1)==((s>>(j-1))&1))
				flag=0;//判断是否相交 
			if(!flag)continue;
			memset(g,-1,sizeof g);
			memset(v,0,sizeof v);
			g[0][tot]=g[tot][0]=0;//偶数个 
			for(int i=1;i<=cnt;++i){
				int l=su[b[i].l],r=su[b[i].r+1],t;
				if(s&(1<<(i-1)))t=0;else t=(r-l)&1;
				if(g[l][r]!=-1&&g[l][r]!=t)flag=0;//冲突 
				else g[l][r]=g[r][l]=t;//区间内偶数个 
			}
			if(!flag)continue;
			for(int i=0;i<=tot;++i)if(!v[i]){
				col[i]=0;if(!dfs(i)){flag=0;break;}
			}
			if(flag)return 1;
		}
		return 0;
	}
}

class DisjointSemicircles {
public:
	string getPossibility(vector <int> labels) {
		n=labels.size()/2;
		int last[55];
		memset(last,-1,sizeof last);
		for(int i=0;i<2*n;++i)if(labels[i]==-1)w[++tot]=i;
		else if(last[labels[i]]!=-1)b[++cnt].l=last[labels[i]],b[cnt].r=i;
		else last[labels[i]]=i;//求出每一段 
		for(int i=1;i<=2*n;++i)su[i]=su[i-1]+(labels[i-1]==-1);//第几个-1 
		int ret=233;
		if(tot<=12)ret=task1::work();
		else ret=task2::work();
		return ret?"POSSIBLE":"IMPOSSIBLE";
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
