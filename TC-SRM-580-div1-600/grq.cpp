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

int f[2505],dp[2505];
bool son[2505];
vi s,t;
vi make(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1){
	vi s;s.clear();
	for(int i=0;i<s1.size();i++)
		for(int j=0;j<s1[i].length();j++)
			s.pb(s1000[i][j]*1000+s100[i][j]*100+s10[i][j]*10+s1[i][j]-'0'*1111);
	return s;
}

class ShoutterDiv1{
public:
	int count(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1, vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1){
		s=make(s1000,s100,s10,s1);
		t=make(t1000,t100,t10,t1);
		memset(dp,0,sizeof(dp));
		int n=s.size(),end,start;
		for(int i=0;i<n;i++){
			son[i]=0;
			for(int j=0;j<n;j++){
				if(s[i]<s[j]||t[i]>t[j]) continue;
				if(s[i]==s[j]&&t[i]==t[j]){if(i<j) son[i]=1;}else son[i]=1;
			}
		}
//		if(n==3){for(int i=0;i<n;i++) printf("%d",son[i]);puts("");}
		end=0;
		for(int i=0;i<n;i++){
			end=max(end,s[i]);f[i]=-1;
			for(int j=0;j<n;j++)
				if(s[i]<=t[j]&&s[j]<=t[i]&&(f[i]==-1||t[f[i]]<t[j])) f[i]=j;
		}
		int ans=0;
		for(int i=0;i<n;i++){
			int k=i;
			while(t[k]<end&&f[k]!=k) k=f[k],dp[i]++;
			if(t[k]<end) return -1;
		}
		start=10005;
		for(int i=0;i<n;i++){
			start=min(start,t[i]);f[i]=-1;
			for(int j=0;j<n;j++)
				if(s[i]<=t[j]&&s[j]<=t[i]&&(f[i]==-1||s[f[i]]>s[j])) f[i]=j;
		}
		for(int i=0;i<n;i++){
			int k=i;
			while(s[k]>start&&f[k]!=k) k=f[k],dp[i]++;
			if(s[k]>start) return -1;
		}
		for(int i=0;i<n;i++){
			if(!son[i]||(s[i]<=start&&t[i]>=end)) continue;
			for(int j=0;j<n;j++){
				if(s[i]<s[j]||t[i]>t[j]) continue;
				if(s[i]==s[j]&&t[i]==t[j]){if(i<j) dp[i]=min(dp[i],dp[j]+1);}else dp[i]=min(dp[i],dp[j]+1);
			}
		}
		for(int i=0;i<n;i++) ans+=dp[i];
		return ans;
	}
};
