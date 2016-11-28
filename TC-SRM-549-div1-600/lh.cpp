#include<map>
#include<set>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class MagicalHats{
	static const int maxn=13;
	typedef pair<int,int> pii;
	int dp[1594323];
	int ro[maxn+5],co[maxn+5],n,m,h,coin,all,lim;
	int x[maxn],y[maxn];
	int nzeros[1594323],ones[1594323];
	int use[2][15],pw[20];
	bool leg[1594323];
	
	bool check(int sta){
		memset(use,0,sizeof(use));
		for (int i=0;sta;++i,sta/=3) if (sta%3==2){
			use[0][x[i]]++;
			use[1][y[i]]++;
		}
		for (int i=0;i<n;++i) if ((use[0][i]+ro[i])&1) return false;
		for (int i=0;i<m;++i) if ((use[1][i]+co[i])&1) return false;
		return true;
	}
	
	bool ask(int sta){
		if (nzeros[sta]-ones[sta]>coin) return leg[sta]=false;
		if (nzeros[sta]==h){
			if (nzeros[sta]-ones[sta]!=coin) return leg[sta]=false;
			else return leg[sta]=check(sta);
		}
		for (int i=0;i<h;++i) if (sta/pw[i]%3==0)
			return leg[sta]=leg[sta+pw[i]]|leg[sta+pw[i]*2];
	}
	
	public:
		int findMaximumReward(vector<string> board, vector<int> coins, int numGuesses){
			pw[0]=1;
			for (int i=1;i<16;++i) pw[i]=pw[i-1]*3;
			lim=numGuesses;
			h=0;
			coin=coins.size();
			n=board.size();
			m=board[0].length();
			for (int i=0;i<n;++i)
			for (int j=0;j<m;++j) if (board[i][j]=='H'){
				x[h]=i;
				y[h]=j;
				++h;
				ro[i]++;
				co[j]++;
			}
			if (h<coin) return -1;
			ones[0]=nzeros[0]=0;
			for (int i=1;i<pw[h];++i){
				if (i%3) nzeros[i]=nzeros[i/3]+1;
				else nzeros[i]=nzeros[i/3];
				if (i%3==1) ones[i]=ones[i/3]+1;
				else ones[i]=ones[i/3];
			}
			for (int i=pw[h]-1;i>=0;--i){
				if (!ask(i)) dp[i]=1000000;
				else if (nzeros[i]<lim){
					for (int j=0;j<h;++j) if ((i/pw[j])%3==0)
					dp[i]=max(dp[i],min(dp[i+pw[j]],dp[i+pw[j]*2]+1));
				}
				else if (nzeros[i]==lim) dp[i]=0;
			}
			int tmp=dp[0],ans=0;
			if (tmp>coin) return -1;
			sort(coins.begin(),coins.end());
			for (int i=0;i<tmp;++i) ans+=coins[i];
			return ans;
		}
};
