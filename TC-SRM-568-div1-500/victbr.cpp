#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 60,mod = 1e9+7;
/*
1.不可能有一列为空
2.每个联通块内差值最小的-c和b的差值一定不大于K
3.-c<=0,b>=0，又b+c<=9 
 
第0行1~n-1编号为1~n-1
第0列1~n-1编号为n+1~2n-1
(0,0)编号为2n
数值0编号为2n+1
*/
class EqualSums{
	public:
		bool noanswer;
		int x0,n,xxx,fa[N<<1],dis[N<<1];
		int vb[N<<1],vc[N<<1],ans; 
		int count(vector <string> board){
			noanswer = 0;
			n = board.size();x0 = n*2+1;
			int u = 0;
			for (int i = 0;i <= n+n+1;i++) fa[i] = i;
			for (int i = 0;i < n;i++)
				if (board[i][0] != '-') {u = i;break;} 
			swap(board[u],board[0]);
			link(x0,n*2,board[0][0]-'0');
			xxx = board[0][0]-'0';
			
			for (int i = 1;i < n;i++){
				if (board[i][0] != '-')
					link(n+i,x0,board[i][0]-'0');		
				if (board[0][i] != '-') 
					link(x0,i,board[0][i]-'0');					
			}

			for (int i = 1;i < n;i++)
				for (int j = 1;j < n;j++)
					if (board[i][j] != '-')
						link(n+i,j,board[i][j]-'0'+xxx);

			for (int i = 0;i <= x0;i++) getfa(i);
			
//			for (int i = 0;i <= x0;i++)
//				printf("%d %d %d\n",i,fa[i],dis[i]);
			for (int i = 0;i <= x0;i++){
				vb[i] = 0x3fffffff;
				vc[i] = - vb[i];
			}
			if (noanswer) return 0;

			for (int i = 0;i < n;i++)
				vb[fa[i]] = min(vb[fa[i]],dis[i]);
			for (int i = n;i < n+n;i++)
				vc[fa[i]] = max(vc[fa[i]],dis[i]);
			for (int i = 0;i <= x0;i++)
				if (fa[i] == i){
					if (vb[i]-vc[i] < xxx) return 0;
				}

			for (int i = -18;i <= 18;i++){
				ll ans1 = 1,ans2 = 1;
				for (int j = 0;j <= x0;j++)
					if (fa[j] == j && j != 0 && j != n){
						if (fa[j] == fa[x0]){
							if (min(i,0) < vc[j]-dis[x0] || vb[j]-dis[x0] < max(0,i+xxx)) {
								ans1 = 0;ans2 = 0;
								break;
							}
							if (min(i-1,0) < vc[j]-dis[x0] || vb[j]-dis[x0] < max(0,i+xxx))
								ans2 = 0;
						}
						else{
							int mx=0x7fffffff,mn=-mx;
							if (vc[j] >= 0) mx = i-vc[j];
							if (vb[j] != 0x3fffffff) mn = i+xxx-vb[j];
							mx = min(mx,-vc[j]);
							mn = max(mn,-vb[j]);
							
							if (mx < mn){
								ans1 = 0;ans2 = 0;break;
							}
							ans1 = ans1*(mx-mn+1)%mod; 
							
							mx=0x7fffffff,mn=-mx;
							if (vc[j] >= 0) mx = i-vc[j]-1;
							if (vb[j] != 0x3fffffff) mn = i+xxx-vb[j];
							mx = min(mx,-vc[j]);
							mn = max(mn,-vb[j]);
							
							if (mx < mn){
								ans2 = 0;
							}
							
							ans2 = ans2*(mx-mn+1)%mod;
						}
					}
//				printf("%d %d %d\n",i,ans1,ans2);
				ans = ((ll)ans+ans1-ans2+mod)%mod;
			}
			return ans;
		}
		void link(int x,int y,int z){
			if (noanswer) return;
			getfa(x);
			getfa(y);					
			if (fa[x] == fa[y]) {
				if (dis[x]+z != dis[y]) noanswer = 1;
				return;
			}
			if (dis[x]+z>dis[y]) {
				dis[fa[y]] = dis[x]+z-dis[y];
				fa[fa[y]] = fa[x];
			}
			else{
				dis[fa[x]] = dis[y]-dis[x]-z;
				fa[fa[x]] = fa[y];				
			}
		}
		void getfa(int x){
			if (x == fa[x]) return;
			getfa(fa[x]);
			dis[x] += dis[fa[x]];
			fa[x] = fa[fa[x]];
		}
};
