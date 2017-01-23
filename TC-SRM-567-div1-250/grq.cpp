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

const int N=100005;
int ans,a[N],cnt[N];

class TheSquareRootDilemma{
public:
	int countPairs(int N, int M){
		for(int i=1;i<=max(N,M);i++){
			int t=i,r=1;
			for(int j=2;j*j<=t;j++)
				if(t%j==0){
					int k=0;
					while(t%j==0) t/=j,k^=1;
					if(k) r*=j;
				}
			a[i]=r*t;
		}
		ans=0;memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=M;i++) cnt[a[i]]++;
		for(int i=1;i<=N;i++) ans+=cnt[a[i]];
		return ans;
	}
};
