#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class TurnOnLamps{
	private:
		static const int maxn=60,inf=10000000;
		int dp[maxn][2];
		int head[maxn],list[maxn<<1],nxt[maxn<<1],mark[maxn<<1],tot=1;
		
		void add(int a,int b,int c){
//			printf("%d->%d %d\n",a,b,c);
			tot++;
			nxt[tot]=head[a];
			head[a]=tot;
			list[tot]=b;
			mark[tot]=c;
			return;
		}
		
		void dfs(int p,int fa){
			int x,y;
			dp[p][0]=0;
			dp[p][1]=1;
//			printf("dfs(%d,%d)\n",p,fa);
			for (int i=head[p];i;i=nxt[i])if (list[i]!=fa){
				int v=list[i];
				dfs(v,p);
				if (mark[i]){
					if (mark[i]==1){
						x=dp[p][0];
						y=dp[p][1];
						dp[p][0]=y+dp[v][1];
						dp[p][1]=x+dp[v][1];
					}
					else if (mark[i]==2){
						dp[p][0]+=dp[v][0];
						dp[p][1]+=dp[v][0];
					}
				}
				else{
					x=dp[p][0];
					y=dp[p][1];
					dp[p][0]=min(x+dp[v][0],y+dp[v][1]);
					dp[p][1]=min(x+dp[v][1],y+dp[v][0]);
				}
			}
//			printf("dp[%d][0]=%d , dp[%d][1]=%d\n",p,dp[p][0],p,dp[p][1]);
			return;
		}
	
	public:
		int minimize(vector <int> roads, string initState, string isImportant){
			memset(head,0,sizeof(head));
			tot=0;
			for (int i=0;i<roads.size();++i){
				int fl=0;
				if (isImportant[i]=='1'){
					if (initState[i]=='0') fl=1;
					else fl=2;
				}
				add(i+1,roads[i],fl);
				add(roads[i],i+1,fl);
			}
			dfs(0,0);
			return dp[0][0]>>1;
		}
};
