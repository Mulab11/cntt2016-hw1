#include<queue>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class ColorfulWolves{
	private:
		static const int maxn=55,maxm=55*55;
		static int dis[maxn],head[maxn],list[maxm],nxt[maxm],cost[maxm],tot,n;
		static queue<int> q;
		static bool vis[maxn];
		
		void add(int a,int b,int c){
			tot++;
			nxt[tot]=head[a];
			head[a]=tot;
			list[tot]=b;
			cost[tot]=c;
			return;
		}
	
	public:
		int getmin(vector<string> colormap){
			n=colormap.size();
			for (int i=0;i<n;++i){
				int c=0;
				for (int j=0;j<n;++j) if (colormap[i][j]=='Y') add(i,j,c++);
			}
			q.push(0);
			for (int i=1;i<n;++i) dis[i]=1000000000;
			while(!q.empty()){
				int a=q.front();
				q.pop();
				vis[a]=false;
				for (int i=head[a];i;i=nxt[i]) if (dis[list[i]]>dis[a]+cost[i]){
					dis[list[i]]=dis[a]+cost[i];
					if (!vis[list[i]]){
						q.push(list[i]);
						vis[list[i]]=true;
					}
				}
			}
			if (dis[n-1]<1000000000) return dis[n-1];
			else return -1;
		}
};

int ColorfulWolves::head[maxn],ColorfulWolves::list[maxm],ColorfulWolves::nxt[maxm];
int ColorfulWolves::cost[maxm],ColorfulWolves::tot,ColorfulWolves::n;
int ColorfulWolves::dis[maxn];
bool ColorfulWolves::vis[maxn];
queue<int> ColorfulWolves::q;

