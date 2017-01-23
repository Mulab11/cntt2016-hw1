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

const int inf=1<<30;

namespace firstX{
	string s;
	int m,n,u,g[305],dp[2][2];
	int cost(int x,int y){
		x^=y;int ans=0;
		while(x) ans++,x^=x&-x;
		return ans;
	}
	int Main(){
		n=s.length();u=(1<<m)-1;
		memset(g,0,sizeof(g));
		for(int i=0;i<n;i+=m)
			for(int j=i;j<i+m&&j<n;j++)
				g[i]=g[i]<<1|(s[j]-'0');
		int ans=inf;
		for(int i=0;i<(1<<m);i++){
			int k=1;dp[0][0]=dp[0][1]=0;
			for(int j=0;j<n;j+=m,k^=1)
				if(j+m<=n){
					dp[k][0]=min(dp[k^1][0],dp[k^1][1]+1)+cost(g[j],i);
					dp[k][1]=min(dp[k^1][1],dp[k^1][0]+1)+cost(g[j]^u,i);
				}
				else dp[k][0]=min(dp[k^1][0],dp[k^1][1]+1)+cost(g[j],i>>j+m-n);
			ans=min(ans,dp[k^1][0]);
		}
		return ans;
	}
	int solve(string S,int M){s=S,m=M;return Main();}
}
namespace secondX{
	string s;
	int m,n,g[305][2];
	int cost(int x,int k){
		int now=-1,last=0,ans=0;
		for(int i=k-1;i>=0;i--){
			if(!(x&(1<<i))&&now==-1) continue;
			if(x&(1<<i)) now=1; else now=0;
			ans+=last^now;last=now;
		}
		return ans;
	}
	int Main(){
		n=s.length();
		int ans=inf;
		for(int i=0;i<(1<<n/m);i++){
			int tmp=cost(i,n/m);
			printf("%d %d\n",i,tmp);
			for(int j=0;j<m;j++) g[j][0]=g[j][1]=0;
			for(int j=0;j<n;j+=m)
				for(int k=0;k<m&&j+k<n;k++)
					if(j+m<=n) g[k][(s[j+k]-'0')^((i&(1<<j/m))>>j/m)]++; else g[k][s[j+k]-'0']++;
			for(int j=0;j<m;j++) tmp+=min(g[j][0],g[j][1]);
			ans=min(ans,tmp);
		}
		return ans;
	}
	int solve(string S,int M){s=S,m=M;return Main();}
}

class FlippingBitsDiv1{
public:
	int getmin(vector <string> S, int M){
		for(int i=1;i<S.size();i++) S[0]=S[0]+S[i];
		if(M<=20) return firstX::solve(S[0],M); 
		return secondX::solve(S[0],M);
	}
};
