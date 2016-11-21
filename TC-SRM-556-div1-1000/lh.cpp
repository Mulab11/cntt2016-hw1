#include<vector>
#include<string>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class OldBridges{
	private:
		static const int maxn=55,maxm=50000,inf=1000000000;
		int head[maxn],list[maxm],nxt[maxm],flow[maxm],tot=1;
		int n,S,T,que[100],h,t,dis[maxn];
		
		void add(int a,int b,int c){
			tot++;
			nxt[tot]=head[a];
			head[a]=tot;
			list[tot]=b;
			flow[tot]=c;
			return;
		}
		
		void adde1(int a,int b,int c){
			add(a,b,c);
			add(b,a,c);
			return;
		}
		
		void adde(int a,int b,int c){
			add(a,b,c);
			add(b,a,0);
			return;
		}
		
		bool tell(){
			memset(dis,0,sizeof(dis));
			dis[S]=1;
			h=t=0;
			que[t++]=S;
			while(h<t){
				int u=que[h++];
				for (int i=head[u];i;i=nxt[i]) if (flow[i]&&dis[list[i]]==0){
					dis[list[i]]=dis[u]+1;
					que[t++]=list[i];
				}
			}
			return dis[T]!=0;
		}
		
		int dinic(int p,int f){
			if (p==T) return f;
			int rec=0;
			for (int i=head[p];i&&f;i=nxt[i]) if (dis[list[i]]==dis[p]+1&&flow[i]){
				int tmp=dinic(list[i],min(f,flow[i]));
				rec+=tmp;
				f-=tmp;
				flow[i]-=tmp;
				flow[i^1]+=tmp;
			}
			if (f) dis[p]=-1;
			return rec;
		}
	
	public:
		string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn){
			n=bridges.size();
			for (int i=0;i<n;++i)
			for (int j=0;j<i;++j) if (bridges[i][j]=='N') adde1(i,j,inf);
			else if (bridges[i][j]=='O') adde1(i,j,2);
			S=n+1,T=S+1;
			an<<=1;
			bn<<=1;
			adde(S,a1,an);
			adde(a2,T,an);
			adde(S,b1,bn);
			adde(b2,T,bn);
			int ret=0;
			while(tell()) ret+=dinic(S,inf);
			if (ret<an+bn) return "No";
			for (int i=2;i<=tot-8;i+=2) flow[i+1]=flow[i]=(flow[i]+flow[i+1])/2;
			for (int i=tot-7;i<=tot;i+=2){
				flow[i]+=flow[i+1];
				flow[i+1]=0;
			}
//			for (int i=0;i<=T;++i) for (int j=head[i];j;j=nxt[j]) printf("%d->%d %d\n",i,list[j],flow[j]);
			head[S]=nxt[head[S]];
			head[T]=nxt[head[T]];
			head[b1]=nxt[head[b1]];
			head[b2]=nxt[head[b2]];
			adde(S,b2,bn);
			adde(b1,T,bn);
			ret=0;
			while(tell()) ret+=dinic(S,inf);
			if (ret<an+bn) return "No";
			return "Yes";
		}
};
