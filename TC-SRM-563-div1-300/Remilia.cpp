#include<bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>

using namespace std;

const int maxn=55;
int cnt[maxn][26];
vector<int>ex[26];
string ans;
int n,need[26];
struct FoxAndHandle{
	/*
	每种字符出现次数为一半。
	逐位贪心即可。
	*/
	string lexSmallestName(string s){
		n=s.size();
		drp(i,n-1,0){
			memcpy(cnt[i],cnt[i+1],sizeof cnt[i+1]);
			cnt[i][s[i]-'a']++;
		}
		rep(i,0,25) need[i]=cnt[0][i]/2;
		int mn='z'+1,pos,len=0;
		rep(i,0,n){
			if (i==n){
				if (len==n/2) return ans;
				ans+=mn,i=pos,mn='z'+1,len++;
				continue;
			}
			if (!need[s[i]-'a']) continue;
			int f=1;
			rep(k,0,25) if (cnt[i][k]<need[k]){f=0;break;}
			if (f){
				if (s[i]<mn) mn=s[i],pos=i;
			}
			else ans+=mn,need[mn-'a']--,mn='z'+1,len++,i=pos;
		}
		return ans;
	}
};
