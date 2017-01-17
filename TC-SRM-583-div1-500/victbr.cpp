#include <bits/stdc++.h>

using namespace std;

const int N = 60;

struct Edge{
	int end,next,color;
};

class TurnOnLamps{	
	public:
		bool flag[N];
		int sum,cnt,first[N],efn,first2[N],efn2,ans;
		string nitState,sImportant;
		Edge edge[N<<1],edge2[N<<1];
		int minimize(vector <int> roads, string initState, string isImportant){
			nitState = initState;
			sImportant = isImportant;
			for (int i = 0;i < roads.size();i++)
				addedge(roads[i],i+1);
			cnt = 1;dfs(0,1);
			for (int i = 1;i <= cnt;i++)
				if (!flag[i]){
					sum = 0;
					dfs2(i,0);
					ans += sum/2;
				}
			return ans;
		}
		void addedge(int x,int y){
			edge[++efn].end = y;
			edge[  efn].next = first[x];
			first[x] = efn;	
		}
		void addedge(int x,int y,int z){
		//	printf("%d %d %d\n",x,y,z);
			edge2[++efn2].end = y;
			edge2[  efn2].color = z;
			edge2[  efn2].next = first2[x];
			first2[x] = efn2;				
			edge2[++efn2].end = x;
			edge2[  efn2].color = z;
			edge2[  efn2].next = first2[y];
			first2[y] = efn2;				
		}
		void dfs(int x,int y){
			for (int h = first[x];h;h = edge[h].next){
				int u = edge[h].end;
				if (sImportant[u-1] == '1') {
					cnt++;
					addedge(y,cnt,nitState[u-1]-'0');
					dfs(u,cnt);
				}
				else dfs(u,y);
			}
		}
		void dfs2(int x,int y){
			flag[x] = 1;int tot = (y != 0);
			for (int h = first2[x];h;h = edge2[h].next){
				int u = edge2[h].end;
				//printf("%d %d %d\n",x,u,edge2[h].color);
				if (edge2[h].color == 0 && u != y){
					dfs2(u,x);tot++;
				}
			}
		//	printf("%d %d\n",x,tot);
			sum += (tot&1);
		}
};
