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

int dp[55],n;
string s;
bool check(int x,int y){
	if(s[x]=='0') return 0;
	ll now=0;
	for(int i=x;i<=y;i++) now=now*2+s[i]-'0';
	if(!now) return 0;
	while(now!=1) if(now%5!=0) return 0; else now/=5;
	return 1;
}

class CuttingBitString{
public:
	int getmin(string S){
		s=S;n=s.length();
		s=' '+s;
		dp[0]=0;
		for(int i=1;i<=n;i++){
			dp[i]=n*2;
			for(int j=0;j<i;j++)
				if(check(j+1,i)) dp[i]=min(dp[i],dp[j]+1);
		}
		if(dp[n]<=n) return dp[n];
		return -1;
	}
};
