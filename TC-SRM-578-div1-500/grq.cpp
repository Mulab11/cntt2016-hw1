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

const int N=305,mod=1e9+7;
vi l,r;
int n,m,p[N],sum[N][N];
vi make(vector<string> a){
	string s="";
	int now=0;
	vi res;res.clear();
	for(int i=0;i<a.size();i++) s+=a[i];
	for(int i=0;i<s.length();i++)
		if(s[i]>='0'&&s[i]<='9') now=now*10+s[i]-'0'; else res.pb(now),now=0;
	res.pb(now);
	return res;
}

class WolfInZooDivOne{
public:
	int count(int N, vector<string> L, vector<string> R){
		l=make(L);r=make(R);
		n=N;m=l.size();
		for(int i=0;i<m;i++) l[i]++,r[i]++;
		for(int i=1;i<=n;i++){
			p[i]=i-1;
			for(int j=0;j<m;j++)
				if(l[j]<=i&&i<=r[j]) p[i]=min(l[j]-1,p[i]);
		}
		memset(sum,0,sizeof(sum));
		sum[0][0]=1;
		for(int i=1;i<=n;i++){
			sum[i][0]=1;
			for(int j=1;j<i;j++)
				sum[i][j]=(sum[i][j-1]+sum[j][min(j-1,p[i])])%mod;
		}
		int ans=1;
		for(int i=1;i<=n;i++) ans=(ans+sum[i][i-1])%mod;
		return ans;
	}
};
