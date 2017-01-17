#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 60;
int b[N];
bool cmp1(const int &x,const int &y){
	return b[x] > b[y];
}
bool cmp2(const int &x,const int &y){
	return x>y;
}
/*
orz CJK大爷的位运算技巧 
*/


class MagicMolecule{
	public:
		ll a[N];
		int n,L,ans,p[N];
	
		int maxMagicPower(vector <int> magicPower, vector <string> magicBond){
			n = magicPower.size();ans = -1;
			L = (n+n+2)/3;
			for (int i = 0;i < n;i++) b[i] = magicPower[i];				
			for (int i = 0;i < n;i++) p[i] = i;
			sort(p,p+n,cmp1);//先选权值大的 
			sort(b,b+n,cmp2);			
			for (int i = 0;i < n;i++)
				for (int j = 0;j < n;j++)	
					if (magicBond[p[i]][p[j]] == 'Y')
						a[i] |= 1LL<<j;	
			dfs(0,0,(1LL<<n)-1);
			return ans;
		}

		void dfs(int x,int y,ll S){
			if (x >= L && y > ans) ans = y;
			if (!S || x + __builtin_popcountll(S) < L || y + value(S) <= ans) return;//最优性剪枝 
	
			for (int i = 0;S;S -= 1LL<<i){
				while (!(S & (1LL<<i))) i++;
				dfs(x+1,y+b[i],S&a[i]);//可选数集合 
			}
			/*
			for(int i; S; S -= 1ll << i){
				i = __builtin_ctzll(S);
				dfs(x + 1, y + b[i], S & a[i]);
			}*/
		}
		inline int cnt(ll S){
			int tot = 0;
			while (S){
				tot++;
				S -= S&(-S);
			}
			return tot;
		}
		/*
		inline int value(ll S){
			int tot = 0;
			for (int i = 0;i < n;i++)
				if (S & (1LL<<i)) tot += b[i];
			return tot;			
		}*/
		
		inline int value(ll S){
			int ret = 0;
			for(int k; S; S -= 1ll << k)
				ret += b[k = __builtin_ctzll(S)];
			return ret;
		}
};
