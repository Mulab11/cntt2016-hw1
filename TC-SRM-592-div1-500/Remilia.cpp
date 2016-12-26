#include <bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
using namespace std;
const int maxn=51;
#define mod 1000000007
int f[2][maxn*maxn][maxn];
void upd(int &x,int y){
	x+=y,x-=x>=mod?mod:0;
}

/*
先固定$a_i=i$，最后答案乘以$n!$。
考虑把$b$的$1\dots n$依次填好位置。
设$dp_{i,j,k}$表示已经把$1\dots i$都填好，填在$(i,n]$的有$j$个，目前已经得到的贡献是$k$的方案数。
考虑$i+1$填的位置：
\begin{enumerate}
  \item 填在位置$i+1$。
  \item 填在$[1,i]$并且把$i+1$暂时空出来。
  \item 填在$[1,i]$并且把要填在$(i,n]$的某个数填在$i+1$这个位置。
  \item 填在$(i,n]$并且把$i+1$暂时空出来。
  \item 填在$(i,n]$并且把要填在$(i,n]$的某个数填在$i+1$这个位置。
\end{enumerate}
复杂度$O(n^2K)$。
*/

class LittleElephantAndPermutationDiv1{
public:
	int getNumber(int n,int k){
		f[0][0][n]=1;
		int fr=0,to=1,sx=0;
		drp(i,n,1){
			memset(f[to],0,sizeof f[to]);
			rep(j,0,sx) rep(k,0,i){
				if (!f[fr][j][k]) continue;
				int l=(i-k)*2;
				if (k>=2) upd(f[to][j+i*2][k-2],(ll)f[fr][j][k]*k*(k-1)%mod);
				if (k) upd(f[to][j+i][k-1],(ll)f[fr][j][k]*k%mod);
				if (k&&j) upd(f[to][j+i][k-1],(ll)f[fr][j][k]*k*l%mod);
				if (l>=2) upd(f[to][j][k],(ll)f[fr][j][k]*(l/2)*(l/2)%mod);
			}
			sx+=i*2;
			fr^=1,to^=1;
		}
		int ans=0;
		rep(j,k,sx) upd(ans,f[fr][j][0]);
		return ans;
	}
};
