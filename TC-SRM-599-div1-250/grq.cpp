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

int tot,p[1005],cnt[1005];
int calc(int x){
	int ans=0,isok=0;
	while(x!=1){
		if(x!=1&&(x&1)) isok=1;
		ans++;x>>=1;
	}
	return ans+isok;
}

class BigFatInteger{
public:
	int minOperations(int A, int B){
		int t=A;
		tot=0;
		for(int i=2;i*i<=t;i++)
			if(t%i==0){
				p[++tot]=i,cnt[tot]=0;
				while(t%i==0)
					cnt[tot]++,t/=i;
			}
		if(t>1) p[++tot]=t,cnt[tot]=1;
		int ans=0;
		for(int i=1;i<=tot;i++) cnt[i]=calc(cnt[i]*B);
		for(int i=1;i<=tot;i++) ans=max(cnt[i],ans);
		ans+=tot;
		return  ans;
	}
};