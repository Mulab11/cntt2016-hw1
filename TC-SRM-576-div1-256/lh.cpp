#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class ArcadeManao{
	private:
		static const int maxn=55;
		int n,m,ax,ay;
		bool vis[maxn][maxn],mp[maxn][maxn];
		typedef pair<int,int> POS;
		queue<POS> q;
		bool judge(int len){
			while(!q.empty()) q.pop();
			memset(vis,0,sizeof(vis));
			for (int i=1;i<=m;++i)if (mp[n][i]){
				vis[n][i]=true;
				q.push(POS(n,i));
			}
			while(!q.empty()){
				POS u=q.front();
				q.pop();
				int x=u.first,y=u.second;
//				printf("(%d,%d)\n",x,y);
				if (x==ax&&y==ay) return true;
				if (y!=1&&!vis[x][y-1])if (mp[x][y-1]){
					vis[x][y-1]=true;
					q.push(POS(x,y-1));
				}
				if (y!=m&&!vis[x][y+1])if (mp[x][y+1]){
					vis[x][y+1]=true;
					q.push(POS(x,y+1));
				}
				for (int i=-min(n-x,len);i<x&&i<=len;++i)if (mp[x-i][y]){
					if (!vis[x-i][y]){
						vis[x-i][y]=true;
						q.push(POS(x-i,y));
					}
				}
			}
			return false;
		}
	public:
		int shortestLadder(vector <string> level, int coinRow, int coinColumn){
			n=level.size();
			m=level[0].length();
			ax=coinRow;
			ay=coinColumn;
			if (ax==n) return 0;
			for (int i=0;i<n;++i)
			for (int j=0;j<m;++j) if (level[i][j]=='X') mp[i+1][j+1]=true;
			int l=0,r=n,mid;
			while(l<r){
//				printf("[%d,%d]\n",l,r);
				mid=(l+r)/2;
				if (judge(mid)) r=mid;
				else l=mid+1;
			}
			return l;
		}
};
