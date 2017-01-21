// BEGIN CUT HERE

// END CUT HERE
#line 5 "ShoutterDiv1.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=2505;
int s[maxn],t[maxn];
bool cmp_s(int x,int y){return s[x]<s[y];}
bool cmp_t(int x,int y){return t[x]>t[y];}
bool cmp_len(int x,int y){return t[x]-s[x]>t[y]-s[y];}
class ShoutterDiv1{
	int a[maxn],b[maxn],c[maxn],ans[maxn],n;
	public:
	int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1){
		memset(s,0,sizeof(s));
		for (int i=n=0;i<s1000.size();++i)for (int j=0;j<s1000[i].size();++j)(s[++n]*=10)+=s1000[i][j]-48;
		for (int i=n=0;i<s100.size();++i)for (int j=0;j<s100[i].size();++j)(s[++n]*=10)+=s100[i][j]-48;
		for (int i=n=0;i<s10.size();++i)for (int j=0;j<s10[i].size();++j)(s[++n]*=10)+=s10[i][j]-48;
		for (int i=n=0;i<s1.size();++i)for (int j=0;j<s1[i].size();++j)(s[++n]*=10)+=s1[i][j]-48;
		memset(t,0,sizeof(t));
		for (int i=n=0;i<t1000.size();++i)for (int j=0;j<t1000[i].size();++j)(t[++n]*=10)+=t1000[i][j]-48;
		for (int i=n=0;i<t100.size();++i)for (int j=0;j<t100[i].size();++j)(t[++n]*=10)+=t100[i][j]-48;
		for (int i=n=0;i<t10.size();++i)for (int j=0;j<t10[i].size();++j)(t[++n]*=10)+=t10[i][j]-48;
		for (int i=n=0;i<t1.size();++i)for (int j=0;j<t1[i].size();++j)(t[++n]*=10)+=t1[i][j]-48;
		
		for (int i=1;i<=n;++i) a[i]=i,b[i]=i,c[i]=i;
		sort(a+1,a+n+1,cmp_s);
		sort(b+1,b+n+1,cmp_t);
		sort(c+1,c+n+1,cmp_len);
		int ret=0;
		for (int i=1;i<=n;++i){
			ans[c[i]]=0;
			int r=t[c[i]],nr=r;
			for (int j=1;j<=n;++j){
				if (s[a[j]]>nr) return -1;
				if (s[a[j]]>r) ++ans[c[i]],r=nr;
				nr=max(nr,t[a[j]]);
			}
			int l=s[c[i]],nl=l;
			for (int j=1;j<=n;++j){
				if (t[b[j]]<nl) return -1;
				if (t[b[j]]<l) ++ans[c[i]],l=nl;
				nl=min(nl,s[b[j]]);
			}
			for (int j=1;j<i;++j)if (s[c[j]]<=s[c[i]]&&t[c[i]]<=t[c[j]])ans[c[i]]=min(ans[c[i]],ans[c[j]]+1);
			ret+=ans[c[i]];
		}
		return ret;
	}
};
