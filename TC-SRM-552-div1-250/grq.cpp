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
#define pq priority_queue
#define rf random_shuffle
#define np next_permutation
#define lb lower_bound
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

ll k;
inline bool check(ll r,ll g,ll b,ll x,ll k){
	if((r+g+b)/k<x) return 0;
	if(k/3>r/x||k/3>b/x||k/3>g/x) return 0;
	return 1;
}

class FoxPaintingBalls{
public:
	long long theMax(long long R, long long G, long long B, int N){
		k=(ll)N*(N+1)/2;
		ll l=0,r=R+G+B;
		while(l<r){
			ll mid=l+r+1>>1;
			if(check(R,G,B,mid,k)) l=mid; else r=mid-1;
		}
		return r;
	}
};
