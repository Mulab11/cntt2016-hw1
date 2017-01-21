// BEGIN CUT HERE

// END CUT HERE
#line 5 "RockPaperScissors.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=51;

double f[maxn][maxn][maxn][maxn];

class RockPaperScissors{
	double P[maxn][3];
	int n;
	void init(){
		memset(f,0,sizeof(f));
		for (int i=1;i<=n;++i){
			f[i][0][0][0]=1;
			for (int j=1;j<=n;++j)
				for (int t=j;t>=0;--t)for (int r=0;r<=t;++r)for (int p=0,s;(s=t-p-r)>=0;++p){
//					printf("%d %d %d %d %d\n",i,j,r,p,s);
					double k=1.0*t/j;
//					printf("k=%.2f\n",k);
					f[i][r][p][s]*=1.0-k;
					if (j==i) continue;
//					puts("qwq");
					f[i][r][p][s]+=k*(P[j][0]*(r?f[i][r-1][p][s]:0)+P[j][1]*(p?f[i][r][p-1][s]:0)+P[j][2]*(s?f[i][r][p][s-1]:0));
//					printf("%.3f\n",f[i][r][p][s]);
				}
		}
	}
	double calc(){
		double ret=0;
		for (int t=n-1;t>=0;--t)for (int r=0;r<=t;++r)for (int p=0,s;(s=t-p-r)>=0;++p){
			double pr=0,pp=0,ps=0;
			for (int i=1;i<=n;++i){
				double tmp=f[i][r][p][s]/(n-t);
				pr+=tmp*P[i][0];
				pp+=tmp*P[i][1];
				ps+=tmp*P[i][2];
			}
//			printf("%d %d %d %.3f %.3f %.3f\n",r,p,s,pr,pp,ps);
			ret+=max(pr+ps*3,max(pp+pr*3,ps+pp*3));
		}
		return ret;
	}
	public:
	double bestScore(vector <int> rockProb, vector <int> paperProb, vector <int> scissorsProb){
		n=rockProb.size();
		for (int i=1;i<=n;++i){
			P[i][0]=1.0*rockProb[i-1]/300.0;
			P[i][1]=1.0*paperProb[i-1]/300.0;
			P[i][2]=1.0*scissorsProb[i-1]/300.0;
		}
		init();
		return calc();
	}
};
