#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class TheTilesDivOne{
	static const int maxn=50*50*2,maxm=maxn*100;
	int head[maxn],list[maxm],nxt[maxm],flow[maxm],tot;
	int num[50][50][2],dis[maxn],q[maxn],S,T;
	
	void add(int a,int b,int f){
		tot++;
		nxt[tot]=head[a];
		head[a]=tot;
		list[tot]=b;
		flow[tot]=f;
		return;
	}
	
	void adde(int a,int b,int f){
//		printf("adde %d->%d f=%d\n",a,b,f);
		add(a,b,f);
		add(b,a,0);
		return;
	}
	
	bool tell(){
		int h=0,t=0;
		memset(dis,0,sizeof(dis));
		dis[S]=1;
		q[t++]=S;
//		printf("S=%d,T=%d\n",S,T);
		while(h<t){
			int u=q[h++];
//			printf("u=%d\n",u);
			for (int i=head[u];i;i=nxt[i]) if (flow[i]&&!dis[list[i]]){
//				printf("%d->%d %d\n",u,list[i],flow[i]);
				dis[list[i]]=dis[u]+1;
				q[t++]=list[i];
			}
		}
		return dis[T]>0;
	}
	
	int dinic(int p,int f){
		if (p==T) return f;
		int ret=0,tmp;
		for (int i=head[p];i&&f;i=nxt[i]) if (dis[list[i]]==dis[p]+1&&flow[i]){
			tmp=dinic(list[i],min(f,flow[i]));
			flow[i]-=tmp;
			flow[i^1]+=tmp;
			f-=tmp;
			ret+=tmp;
		}
		if (f) dis[p]=-1;
		return ret;
	}
	
	public:
		TheTilesDivOne(){
			memset(head,0,sizeof(head));
			tot=1;
		}
		
		int find(vector<string> board){
			int n=board.size(),m=board[0].length();
			S=1;
			for (int i=0;i<n;++i)
			for (int j=0;j<m;++j){
				num[i][j][0]=S++;
				num[i][j][1]=S++;
			}
			T=S+1;
			for (int i=0;i<n;++i)
			for (int j=0;j<m;++j) if (board[i][j]=='.') adde(num[i][j][0],num[i][j][1],1);
			for (int i=0;i<n;++i)
			for (int j=0;j<m;++j){
//				printf("i=%d,j=%d\n",i,j);
				if ((i+j)&1){
					if (i&1){
						adde(S,num[i][j][0],1);
						if (i>0) adde(num[i][j][1],num[i-1][j][0],1);
						if (i<n-1) adde(num[i][j][1],num[i+1][j][0],1);
						if (j>0) adde(num[i][j][1],num[i][j-1][0],1);
						if (j<m-1) adde(num[i][j][1],num[i][j+1][0],1);
					}
					else{
						adde(num[i][j][1],T,1);
					}
				}
				else{
					if (i&1){
						if (i>0) adde(num[i][j][1],num[i-1][j][0],1);
						if (i<n-1) adde(num[i][j][1],num[i+1][j][0],1);
					}
					else{
						if (j>0) adde(num[i][j][1],num[i][j-1][0],1);
						if (j<m-1) adde(num[i][j][1],num[i][j+1][0],1);
					}
				}
			}
//			return 0;
			int ans=0;
			while(tell()){
				ans+=dinic(S,1000000);
//				printf("ans=%d\n",ans);
			}
			return ans;
		}
};
