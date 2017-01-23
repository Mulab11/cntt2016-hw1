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

const int mod=1e9+9;

int k,u,dp[2][1<<16];
inline void ch(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void get(int a,int x,int y,int j,int si){
	int xx=a&(1<<j*2),yy=a&(1<<j*2+1),rem=a&(u^(1<<j*2)^(1<<j*2+1));
	if(j) xx|=(a&(1<<j*2-2))<<2,yy|=(a&(1<<j*2-1))<<2;
	xx&=x<<j*2,yy&=y<<j*2+1;
	ch(dp[k][rem|xx|yy],(ll)dp[k^1][a]*si%mod);
}

class StringPath{
public:
	int countBoards(int n, int m, string A, string B){
		u=(1<<m*2)-1;
		memset(dp,0,sizeof(dp));
		k=0;dp[k][3]=1;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				k^=1;memset(dp[k],0,sizeof(dp[k]));
				for(int a=0;a<=u;a++){
					if(!dp[k^1][a]) continue;
					if(A[i+j]==B[i+j]) get(a,1,1,j,1),get(a,0,0,j,25); 
					else get(a,1,0,j,1),get(a,0,1,j,1),get(a,0,0,j,24);
				}
			}
		int ans=0;
		for(int i=0;i<=u;i++)
			if((i&(1<<m*2-2))&&(i&(1<<m*2-1))) ch(ans,dp[k][i]);
		return ans;
	}
};
