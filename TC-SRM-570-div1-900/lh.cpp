#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class CurvyonRails{
	static const int maxn=25*25*4,maxm=25*25*4*6,inf=1000000000;
	int num[30][30][3],S,T;
	int head[maxn],list[maxm<<1],nxt[maxm<<1],flow[maxm<<1],cost[maxm<<1],tot;
	int pre[maxn],dis[maxn],flw[maxn],q[100000];
	bool vis[maxn];
	
	void add(int a,int b,int f,int c){
		++tot;
		nxt[tot]=head[a];
		head[a]=tot;
		list[tot]=b;
		flow[tot]=f;
		cost[tot]=c;
		return;
	}
	
	void adde(int a,int b,int f,int c){
//		printf("adde %d->%d flow=%d,cost=%d\n",a,b,f,c);
		add(a,b,f,c);
		add(b,a,0,-c);
		return;
	}
	
	bool spfa(){
		int h=0,t=0;
		for (int i=0;i<=T;++i) dis[i]=inf;
		q[t++]=S;
		dis[S]=0;
		flw[S]=inf;
		while(h<t){
			int u=q[h++];
			vis[u]=false;
//			printf("getin %d, dis=%d\n",u,dis[u]);
			for (int i=head[u];i;i=nxt[i]) if (flow[i]){
//				printf("goto %d\n",list[i]);
				if (dis[list[i]]>dis[u]+cost[i]){
//					printf("pushin\n");
					pre[list[i]]=i;
					dis[list[i]]=dis[u]+cost[i];
					flw[list[i]]=min(flw[u],flow[i]);
					if (!vis[list[i]]){
						q[t++]=list[i];
						vis[list[i]]=true;
					}
				}
//				else puts("failed");
			}
		}
		return dis[T]<inf;
	}
	
	public:
	int getmin(vector<string> field){
		tot=1;
		S=1;
		int n=field.size(),m=field[0].length();
		for (int i=0;i<n;++i)
		for (int j=0;j<m;++j)
		for (int k=0;k<3;++k){
			num[i][j][k]=S++;
//			printf("num[%d][%d][%d]=%d\n",i,j,k,num[i][j][k]);
		}
		T=S+1;
		int num1=0,num2=0;
		for (int i=0;i<n;++i)
		for (int j=0;j<m;++j){
			if ((i+j)&1){
				if (field[i][j]=='.'){
					adde(S,num[i][j][0],2,0);
					num1+=2;
					adde(num[i][j][0],num[i][j][1],2,0);
					adde(num[i][j][0],num[i][j][2],2,0);
					if (i!=0) adde(num[i][j][2],num[i-1][j][2],1,0);
					if (i!=n-1) adde(num[i][j][2],num[i+1][j][2],1,0);
					if (j!=0) adde(num[i][j][1],num[i][j-1][1],1,0);
					if (j!=m-1) adde(num[i][j][1],num[i][j+1][1],1,0);
				}
				else if (field[i][j]=='C'){
					num1+=2;
					adde(S,num[i][j][0],2,0);
					adde(num[i][j][0],num[i][j][1],1,0);
					adde(num[i][j][0],num[i][j][1],1,1);
					adde(num[i][j][0],num[i][j][2],1,0);
					adde(num[i][j][0],num[i][j][2],1,1);
					if (i!=0) adde(num[i][j][2],num[i-1][j][2],1,0);
					if (i!=n-1) adde(num[i][j][2],num[i+1][j][2],1,0);
					if (j!=0) adde(num[i][j][1],num[i][j-1][1],1,0);
					if (j!=m-1) adde(num[i][j][1],num[i][j+1][1],1,0);
				}
			}
			else{
				if (field[i][j]=='.'){
					num2+=2;
					adde(num[i][j][0],T,2,0);
					adde(num[i][j][1],num[i][j][0],2,0);
					adde(num[i][j][2],num[i][j][0],2,0);
				}
				else if (field[i][j]=='C'){
					num2+=2;
					adde(num[i][j][0],T,2,0);
					adde(num[i][j][1],num[i][j][0],1,0);
					adde(num[i][j][1],num[i][j][0],1,1);
					adde(num[i][j][2],num[i][j][0],1,0);
					adde(num[i][j][2],num[i][j][0],1,1);
				}
			}
		}
		if (num1!=num2) return -1;
		int ans=0;
		while(spfa()){
			num1-=flw[T];
			ans+=dis[T]*flw[T];
			int p=T;
			while(p!=S){
				flow[pre[p]]-=flw[T];
				flow[pre[p]^1]+=flw[T];
				p=list[pre[p]^1];
			}
		}
		if (num1>0) return -1;
		return ans;
	}
};
