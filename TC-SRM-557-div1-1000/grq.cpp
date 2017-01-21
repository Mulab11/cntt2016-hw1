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

const int N=66;
int n;ll a[N];

class XorAndSum{
public:
	long long maxSum(vector<long long> number){
		ll tot=0,ans=0;int fir=0,si=0;
		memset(a,0,sizeof(a));
		n=number.size();
		for(int i=0;i<n;i++)
			for(int j=60;j>=0;j--)
				if(number[i]&(1ll<<j)){
					fir=max(fir,j);
					if(a[j]) number[i]^=a[j]; else{a[j]=number[i];break;}
				}
		for(int i=0;i<=fir;i++){
			for(int j=0;j<=fir;j++)
				if(j!=i&&a[j]&(1ll<<i)) a[j]^=a[i];
		}
//		printf("%lld\n",a[fir]);
		for(int i=fir-1;i>=0;i--)
			if((a[fir]^a[i])>a[fir]) a[fir]^=a[i];
		ans=a[fir]*n;
		for(int i=0;i<fir;i++)
			if(a[i]) ans+=(a[i]^a[fir])-a[fir];
		return ans;
	}
};
