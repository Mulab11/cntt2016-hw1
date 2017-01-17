#include <bits/stdc++.h>

using namespace std;

const int N = 14;


class MagicalHats{
	public:
		int xx[N],yy[N],f[2001000],len,base[N],ans,num,a[N];
		bool bx[N],by[N]; 
		void init(){
			len = 0;base[0] = 1;ans = 0;
			for (int i = 1;i <= 13;i++) base[i] = base[i-1]*3;
		}
		int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses){
			init();num = coins.size();
			for (int i = 0;i < num;i++) a[i] = coins[i];
			for (int i = 0;i < board.size();i++)
				for (int j = 0;j < board[i].size();j++)
					if (board[i][j] == 'H'){
						xx[++len] = i+1;
						yy[  len] = j+1; 
					}
			sort(a,a+num);
			for (int i = base[len]-1;i >= 0;i--){
				int opt = check(i,numGuesses);
			//	if (i == 0) return opt;
				if (opt == 0) f[i] = 0x3fffffff;
				if (opt == 1) f[i] = 0;
				if (opt == 2){
					int u = i;f[i] = 0x3fffffff;
					for (int j = 0;j < len;j++){
						if (u % 3 == 0)
							f[i] = min(f[i],min(f[i+base[j]],f[i+base[j]+base[j]]));
						u /= 3;
					}
				}
				if (opt == 3){
					int u = i;f[i] = -1;
					for (int j = 0;j < len;j++){
						if (u % 3 == 0)
							f[i] = max(f[i],min(f[i+base[j]],f[i+base[j]+base[j]]+1));
						u /= 3;
					}
				}
			}
			if (f[0] == 0x3fffffff) return -1;
			else{
				for (int i = 0;i < f[0];i++) ans += a[i];
				return ans;
			}
		}
		int check(int x,int y){
			int cnt0 = 0,cnt1 = 0,cnt2 = 0;
			memset(bx,0,sizeof(bx));memset(by,0,sizeof(by));
			for (int j = 0;j < len;j++){
				if (x % 3 == 0) cnt0++;
				if (x % 3 == 1) {
					cnt1++;
					bx[xx[j+1]] ^= 1;
					by[yy[j+1]] ^= 1;				
				}
				if (x % 3 == 2) cnt2++;
				x /= 3;
			}
			
			if (cnt0 == 0){
				if (cnt2 != num) return 0;
				for (int i = 1;i <= 13;i++){
					if (bx[i]) return 0;
					if (by[i]) return 0;
				}
				return 1;
			}
			if (cnt2+cnt1 >= y) return 2;
			return 3;
		}
};
