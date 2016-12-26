// by ξ

#include <bits/stdc++.h>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define sqr(x) (x)*(x)
#define ALL(V) V.begin(),V.end()
#define pb push_back
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> PDD;
typedef vector<int> VI;
typedef vector<PII> VII;

class RandomPaintingOnABoard{
	public:
		int n,m,T,A[27][27],row[27],F[2][1505],G[2][1505],Num[2][1505];
		void Change(vector<string>&prob){
			// 把小的那维作为n
			n=prob.size();
			m=prob[0].size();
			if(n>m){
				rep(i,0,n)
				rep(j,0,m)
				A[j][i]=prob[i][j]-48;
				swap(n,m);
			}else{
				rep(i,0,n)
				rep(j,0,m)
				A[i][j]=prob[i][j]-48;
			}
			rep(i,0,n)rep(j,0,m)T+=A[i][j];
		}
		int Cnt(int x){
			// 二进制1的个数
			return __builtin_popcount(x);
		}
		void Calculate(){
			// 01枚举n小的那一维的状况，dp另一维
			// dp出所有权值和的方案数
			rep(i,0,n)rep(j,0,m)row[i]+=A[i][j];
			int lim=1<<n;
			rep(i,0,lim){
				int SM=0;
				rep(j,0,n)if(i>>j&1)SM+=row[j];
				memset(F,0,sizeof F);
				F[Cnt(i)&1][T-SM]=1;
				rep(j,0,m){
					int tm=0;
					rep(k,0,n)if(~i>>k&1)tm+=A[k][j];
					memcpy(G,F,sizeof F);
					rep(k,0,2)
					For(l,tm,T)F[k^1][l-tm]+=G[k][l];
				}
				rep(j,0,2)
				For(k,0,T)Num[j][k]+=F[j][k];
			}
		}
		db expectedSteps(vector<string> prob){
			Change(prob);
			Calculate();
			db Ans=0;
			// 等比数列
			rep(x,0,T)Ans+=1.*T/(T-x)*(Num[1][x]-Num[0][x]);
			return Ans;
		}
};