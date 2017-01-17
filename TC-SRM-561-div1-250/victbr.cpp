#include <bits/stdc++.h>

using namespace std;

const int N = 60;

class ICPCBalloons{
	public:
		int big[N],small[N];
		int n,m,a[N],l1,l2;
		int minRepaintings(vector <int> balloonCount, string balloonSize, vector <int> maxAccepted){
			n = balloonCount.size();
			for (int i = 0;i < n;i++){
				if (balloonSize[i] == 'M') big[++l1] = balloonCount[i]; 
				else small[++l2] = balloonCount[i]; 
			}
			sort(big+1,big+l1+1);
			sort(small+1,small+l2+1);
			
			m = maxAccepted.size();
			for (int i = 0;i < m;i++)
				a[i] = maxAccepted[i];
			sort(a,a+m);
			int ans = dfs(m-1,0,0,l1,l2);
			if (ans >= 0x3f3f3f3f) ans = -1;
			return ans;
		}
		int dfs(int x,int y,int z,int u,int v){
			int ans;
			if (u < 0) return 0x3f3f3f3f;
			if (v < 0) return 0x3f3f3f3f;
			if (x < 0){
				while (u > 0) {y += big[u];u--;}//最后可能剩很多种气球未处理。
				while (v > 0) {z += small[v];v--;} 
				if (x < 0 && (y < 0 || z < 0)) return 0x3f3f3f3f;					
				if (x < 0) return 0;
			}
			ans = min(dfs(x-1,y+big[u]-a[x],z,u-1,v)+max(0,a[x]-big[u]),dfs(x-1,y,z+small[v]-a[x],u,v-1)+max(0,a[x]-small[v]));
			if (u == 0) ans = min(ans,dfs(x-1,y-a[x],z,u,v)+a[x]);
			if (v == 0) ans = min(ans,dfs(x-1,y,z-a[x],u,v)+a[x]);
			return ans;
		}
};
