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

const int N=1e6+5,mod=1e9+7;
int f[N],n;

class TrafficCongestion{
public:
	int theMinCars(int treeHeight){
		f[1]=1;n=treeHeight;
		if(n==0) return 1;
		if(n==1) return 1;
		int sum=1;
		for(int i=2;i<n;i++){
			f[i]=(sum*2+1)%mod;
			sum=(sum+f[i-1])%mod;
		}
		return (sum*2+1)%mod;
	}
};
