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

int n,sum,ans;
bitset<1000000> dp;

class MayTheBestPetWin{
public:
	int calc(vector <int> A, vector <int> B){
		n=A.size();sum=0;ans=1e9;
		for(int i=0;i<n;i++) sum+=B[i]-A[i];
		dp=0;dp[500000]=1;
		for(int i=0;i<n;i++) 
			dp=(dp>>A[i])|(dp<<B[i]);
		for(int i=0;i<1000000;i++)
			if(dp[i]) ans=min(ans,max(i-500000,sum-i+500000));
		return ans;
	}
};
