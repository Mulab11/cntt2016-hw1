#include <bits/stdc++.h>

using namespace std;

const int N = 60;

class PointyWizardHats{
	public:
		int ans,used[N],len1,len2,first[N],efn;
		bool vist[N];
		struct Edge{
			int end,next;
		}edge[N*N];
 		int getNumHats(vector <int> topHeight, vector <int> topRadius, vector <int> bottomHeight, vector <int> bottomRadius){
 			memset(used,0,sizeof(used));
 			len1 = topHeight.size();len2 = bottomHeight.size();
 			efn = 0;

 			for (int i = 0;i < len1;i++)
 				for  (int j = 0;j < len2;j++)
 					if ((double)topHeight[i]/topRadius[i] > (double)bottomHeight[j]/bottomRadius[j] && topRadius[i] < bottomRadius[j])
 						insert(i+1,j+1);
 			for (int i = 1;i <= len1;i++){
 				memset(vist,0,sizeof(vist)); 				
				if (dfs(i)) ans++;
			}
 			return ans;
 				
 		}
 		void insert(int x,int y){
 			edge[++efn].end = y;
 			edge[  efn].next = first[x];
 			first[x] = efn;
 		}
 		bool dfs(int x){
 			for (int h = first[x];h;h = edge[h].next){
				int y = edge[h].end;
				if (!vist[y]){
					vist[y] = 1;					
					if (used[y] == 0) {used[y] = x;return 1;}
					if (dfs(used[y])){
						used[y] = x;
						return 1;
					}
				}
			}
			return 0;
		}
};
