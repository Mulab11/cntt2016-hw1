#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int N=105,M=29,inf=1e7;
int g[M][N][M][M],dp[2][M][M];
int mn1[M][M][M],mn2[M][M][M];
//g[fir][i][a][b]表示开始有fir个字母已经用过，组成长度为i的一个light串，新加a个字母，b个字母结束使用的最小代价
//dp[i][a][b]表示做到第i个字符串，a个字母没用完，b个字母用完了的最小代价 
//mn1,mn2为优化转移时使用 

inline void upt(int &x,int y){if(x>y) x=y;}
inline void solve(int fir){
	for(int a=0;a<=26;a++)
		for(int b=0;b<=26;b++)
			for(int c=0;c<=26;c++){
				mn1[a][b][c]=mn2[a][b][c]=inf;
				for(int i=0;i<=100;i++)
					g[fir][i][a][b]=inf;
			}
	mn1[0][0][0]=-1;mn2[0][0][0]=0;
	for(int i=1;i<=100;i++)
		for(int a=26;~a;a--)
			for(int b=26;~b;b--){
				if(b>a+fir) continue;
				for(int c=26;c;c--){
					if(c-a>fir) continue;
					int tmp=inf;
					//这里的tmp表示f[i][a][b][c]：长度为i的任意串用了c个字母，a个新用，b个结束的最小代价 
					if(a) upt(tmp,mn1[a-1][b][c-1]);
					if(b) upt(tmp,mn2[a][b-1][c-1]+i);
					if(a&&b) upt(tmp,mn1[a-1][b-1][c-1]+i);
					upt(tmp,mn2[a][b][c-1]);
					//分新用、结束、新用并结束、既不新用也不结束四种情况转移 
					upt(mn1[a][b][c],tmp-i-1);
					upt(mn2[a][b][c],tmp);
					if(c==min(26,i)) upt(g[fir][i][a][b],tmp);
				}
			}
}

class StringWeight{
public:
	int getMinimum(vector<int> L){
		for(int i=0;i<=26;i++) solve(i);
		int k=0,ans=inf,maxx=0,len=0;
		for(int a=0;a<=26;a++)
			for(int b=0;b<=26-a;b++)
				dp[k][a][b]=inf;
		dp[k][0][0]=0;
		for(int i=0;i<L.size();i++){
			maxx=max(maxx,L[i]);
			k^=1;
			for(int a=0;a<=26;a++)
				for(int b=0;b<=26-a;b++)
					dp[k][a][b]=inf;
			for(int a=0;a<=26;a++)
				for(int b=0;b<=26-a;b++){
					if(dp[k^1][a][b]>=inf) continue;
					for(int l=0;l<=26;l++){
						if(l+a<min(L[i],26)||l+a+b>26) continue;
						for(int r=0;r<=26;r++)
							if(a+l>=r) upt(dp[k][a+l-r][b+r],dp[k^1][a][b]+g[a][L[i]][l][r]+(r-l)*len);
					}
				}//枚举字符串i新用几个字符，结束几个字符来转移 
			len+=L[i];
		}
		for(int i=min(26,maxx);i<=26;i++) ans=min(ans,dp[k][0][i]);
		return ans;
	}
};
