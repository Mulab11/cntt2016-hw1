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

const int N=105;
int n,vis;
ll a[N];

class XorCards{
public:
	long long numberOfWays(vector<long long> number, long long limit){
		n=number.size();
		memset(a,0,sizeof(a));
		for(int i=0;i<n;i++)
			for(int j=50;~j;j--)
				if(number[i]&(1ll<<j)){
					if(!a[j]){a[j]=number[i];break;} else number[i]^=a[j];
				}
		for(int i=0;i<50;i++){
			if(!a[i]) continue;
			for(int j=0;j<50;j++)
				if(i!=j&&(a[j]&(1ll<<i))) a[j]^=a[i];
		}
		ll ans=0;
		for(int j=50;~j;j--)
			if(limit&(1ll<<j)){
				ll tmp=0,vis=limit^(1ll<<j);int use=n;
				for(int k=50;k>=j;k--){
					if(a[k]) use--;
					if(vis&(1ll<<k)) tmp^=a[k];
				}
				if((tmp>>j)==(vis>>j)) ans+=1ll<<use;
			}
		ll tmp=0;int use=n;
		for(int k=50;k>=0;k--){
			if(a[k]) use--;
			if(limit&(1ll<<k)) tmp^=a[k];
		}
		if(limit==tmp) ans+=1ll<<use;
		return ans;
	}
};

