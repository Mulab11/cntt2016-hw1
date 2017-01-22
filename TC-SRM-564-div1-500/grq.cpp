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

class AlternateColors2{
public:
	long long countWays(int n, int k){
		ll ans=0;
		for(int i=0;i<=n/3;i++){
			if(k<=i*3){
				if(k%3!=1) continue;
				int a=n-i*3;
				if(!a) ans++; else ans+=a*3;
				continue;
			}
			int a=n-i*3,b=k-i*3;
			if(b&1) ans+=(a<<1)-b; else ans+=b-1;
		}
		return ans;
	}
};
