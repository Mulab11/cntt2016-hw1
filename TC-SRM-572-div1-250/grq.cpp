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

int cnt[26];

class NewArenaPassword{
public:
	int minChange(string psw, int K){
		int n=psw.size(),k=n-K,ans=0;
		if(!k) return 0;
		for(int i=0;i<k;i++){
			memset(cnt,0,sizeof(cnt));
			for(int j=i;j<n;j+=k) cnt[psw[j]-'a']++;
			int res=0;
			for(int j=0;j<26;j++) res=max(res,cnt[j]);
			ans+=res;
		}
		return n-ans;
	}
};
