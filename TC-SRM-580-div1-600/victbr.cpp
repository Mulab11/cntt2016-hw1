#include <bits/stdc++.h>

using namespace std;

const int N = 2510;

struct Edge{
	int end,next;
};
struct Node{
	int x,y;
	Node(){}
	Node(int x,int y):x(x),y(y){}
};
bool operator < (const Node &a,const Node &b){
	return a.x < b.x;
}

class ShoutterDiv1{
	public:
		string ss1000,ss100,ss10,ss1,tt1000,tt100,tt10,tt1;
		int s[N],t[N],ans,u,v;
		int first[N],efn,n,dis[2][N];
		struct Edge edge[N*N];
		Node nod[N];
		int count(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1, vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1){			
			
			for (int i = 0;i < s1.size();i++){
				ss1000 = ss1000 + s1000[i];
				ss100 = ss100 + s100[i];
				ss10 = ss10 + s10[i];
				ss1 = ss1 + s1[i];
				tt1000 = tt1000 + t1000[i];
				tt100 = tt100 + t100[i];
				tt10 = tt10 + t10[i];
				tt1 = tt1 + t1[i];
			}
			
			n = ss1000.size();
			for (int i = 0;i < n;i++){
				s[i] = (ss1000[i]-'0')*1000 + (ss100[i]-'0')*100 + (ss10[i]-'0')*10 + (ss1[i]-'0');
				t[i] = (tt1000[i]-'0')*1000 + (tt100[i]-'0')*100 + (tt10[i]-'0')*10 + (tt1[i]-'0');
				if (s[i] > s[u] || (s[i] == s[u] && t[i] )) u = i;
				if (t[v] > t[i]) v = i;
			}
			for (int i = 0;i < n;i++)
				for (int j = i+1;j < n;j++)
					if (max(s[i],s[j]) <= min(t[i],t[j])) addedge(i,j);
			bfs(u,0);
			bfs(v,1);
			for (int i = 0;i < n;i++){
				dis[0][i] = max(dis[0][i]-1,0)+max(dis[1][i]-1,0);
				nod[i] = Node(dis[0][i],i);
			}
			sort(nod,nod+n);
			bfs2();
			for (int i = 0;i < n;i++) {
				if (dis[0][i] >= 0x3f3f3f3f-1) {ans = -1;break;}
				ans += dis[0][i];
//				printf("%d ",dis[0][i]);
			}
			return ans;//答案为转发次数而不是总用时
		}
		void addedge(int x,int y){
			edge[++efn].end = y;
			edge[  efn].next = first[x];
			first[x] = efn;
			edge[++efn].end = x;
			edge[  efn].next = first[y];
			first[y] = efn;			
		}
		void bfs(int x,int y){
			static int e[N];
			int t = 1,w = 1;
			memset(dis[y],0x3f,sizeof(dis[y]));
			e[1] = x;dis[y][x] = 0;
			while (t <= w){
				int u = e[t];
				for (int h = first[u];h;h = edge[h].next){
					int v = edge[h].end;
					if (dis[y][v] >= 0x3f3f3f3f-1){
						dis[y][v] = dis[y][u]+1;
						e[++w] = v;
					}
				}
				t++;
			}
		}
		void bfs2(){
			static int e[N];
			int t = 1,w = 1,k = 0;
			e[1] = nod[0].y;
			while (t <= w){
				int u = e[t];
				while (k < n){
					if (dis[0][nod[k].y] != nod[k].x) k++;
					else if (nod[k].x == dis[0][u]) {e[++w] = nod[k].y;k++;}
					else break;
				}
				for (int h = first[u];h;h = edge[h].next){
					int v = edge[h].end;
					if (dis[0][v] > dis[0][u]+1){
						dis[0][v] = dis[0][u]+1;
						e[++w] = v;
					}
				}
				t++;
			}
		}
};

