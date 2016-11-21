#include<vector>
#include<string>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class FoxTheLinguist{
	private:
		static const int maxn=13,inf=1000000000;
		int head[maxn*maxn],list[100000],nxt[100000],cost[100000],tot;
		int trs[maxn][maxn],S;
		int dis[1<<10][maxn*maxn];
		int q[1000000],h,t;
		bool vis[1000];
		
		void add(int a,int b,int c){
			tot++;
			nxt[tot]=head[a];
			head[a]=tot;
			cost[tot]=c;
			list[tot]=b;
			return;
		}
		
		void adde(string &s){
			int len=s.length();
			for (int i=0;i<len;i+=12){
				int s0=s[i]-'A',s1=s[i+1]-'0';
				int t0=s[i+4]-'A',t1=s[i+5]-'0';
				int cost=(s[i+7]-'0')*1000+(s[i+8]-'0')*100+(s[i+9]-'0')*10+(s[i+10]-'0');
				for (int i=s1;i<10;++i) add(trs[t0][t1],trs[s0][i],cost);
			}
			return;
		}
		
		void spfa(int *d){
			h=t=0;
			for (int i=0;i<=S;++i) vis[q[t++]=i]=true;
			while(h<t){
				int u=q[h++];
				vis[u]=false;
				for (int i=head[u];i;i=nxt[i]) if (d[list[i]]>d[u]+cost[i]){
//					printf("d[%d]=%d\n",list[i],d[list[i]]);
					d[list[i]]=d[u]+cost[i];
					if (!vis[list[i]]) vis[q[t++]=list[i]]=true;
				}
			}
			return;
		}
	
	public:
		int minimalHours(int n, vector <string> courseInfo){
			S=0;
			for (int i=0;i<n;++i) trs[i][9]=S++;
			for (int i=0;i<n;++i)
			for (int j=0;j<9;++j) trs[i][j]=S++;
			string tmp="";
			for (int i=0;i<courseInfo.size();++i) tmp+=courseInfo[i];
			adde(tmp);
			for (int i=0;i<n;++i) add(trs[i][0],S,0);
			for (int sta=1;sta<(1<<n);++sta)
			for (int i=0;i<=S;++i) dis[sta][i]=inf;
			for (int sta=1;sta<(1<<n);++sta){
//				for (int i=0;i<=S;++i) printf("dis[%d][%d]=%d  %d\n",sta,i,dis[sta][i],dis[sta+1][i]);
				for (int i=0;i<=S;++i){
					int now=0;
					if (i<n&&(sta&(1<<i))) now=1<<i;
					
					for (int j=(sta-1)&sta;;j=(j-1)&sta){
//						if (sta==2&&i==0) printf("j=%d, %d + %d  (%d)\n",j,dis[j][i],dis[sta^now^j][i],sta^now^j);
						dis[sta][i]=min(dis[sta][i],dis[j][i]+dis[sta^now^j][i]);
						if (j==0) break;
					}
				}
				spfa(dis[sta]);
//				for (int i=0;i<=S;++i) printf("dis[%d][%d]=%d  %d\n",sta,i,dis[sta][i],dis[sta+1][i]);
//				break;
			}
			int t=(1<<n)-1;
			if (dis[t][S]==inf) return -1;
			return dis[t][S];
		}
};
