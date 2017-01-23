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

const double eps=1e-9;
const int N=55;
int n;
double pr[N],pp[N],ps[N],pos[N][N][N],dp[N][N][N],f[2][N][N][N];

double calc(double a,double b,double c){
	return max(a*3+b,max(b*3+c,c*3+a));
}

class RockPaperScissors{
public:
	double bestScore(vector<int> rockProb, vector<int> paperProb, vector<int> scissorsProb){
		n=rockProb.size();
		for(int i=0;i<n;i++) pr[i]=(double)rockProb[i]/300.0;
		for(int i=0;i<n;i++) pp[i]=(double)paperProb[i]/300.0;
		for(int i=0;i<n;i++) ps[i]=(double)scissorsProb[i]/300.0;
		
		int k=0;
		memset(f,0,sizeof(f));
		f[0][0][0][0]=1.0;
		for(int i=0;i<n;i++){
			k^=1;
			for(int a=0;a<=n;a++)
				for(int b=0;a+b<=n;b++)
					for(int c=0;a+b+c<=n;c++){
						f[k][a][b][c]=f[k^1][a][b][c];
						if(a) f[k][a][b][c]+=f[k^1][a-1][b][c]*pr[i];
						if(b) f[k][a][b][c]+=f[k^1][a][b-1][c]*pp[i];
						if(c) f[k][a][b][c]+=f[k^1][a][b][c-1]*ps[i];						
					}
		}
		memcpy(pos,f[k],sizeof(pos));
		memset(dp,0,sizeof(dp));
		for(int a=n-1;~a;a--)
			for(int b=n-1-a;~b;b--)
				for(int c=n-1-a-b;~c;c--){
					if(pos[a][b][c]<eps) continue;
					double p1,p2,p3;
					p1=pos[a+1][b][c]*(a+1);
					p2=pos[a][b+1][c]*(b+1);
					p3=pos[a][b][c+1]*(c+1);
					dp[a][b][c]=(calc(p1,p2,p3)+p1*dp[a+1][b][c]+p2*dp[a][b+1][c]+p3*dp[a][b][c+1])/(p1+p2+p3);
				}
		return dp[0][0][0];
	}
};

