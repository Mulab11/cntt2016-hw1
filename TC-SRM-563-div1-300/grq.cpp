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

const int N=55;
int n,s[26][N],now[26],cnt[26];

class FoxAndHandle{
public:
	string lexSmallestName(string S){
		n=S.size();
		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<n;i++) cnt[S[i]-'a']++;
		for(int i=0;i<n;i++)
			for(int j=0;j<26;j++) 
				if(S[i]=='a'+j) s[j][i]=i?s[j][i-1]+1:1; else s[j][i]=i?s[j][i-1]:0;
		int k=0;
		memset(now,0,sizeof(now));
		string ans="";
		for(int i=0;i<n/2;i++){
			for(char c='a';c<='z';c++){
				int nex=-1,isok=1;
				for(int j=k;j<n;j++) if(S[j]==c){nex=j;break;}
				if(nex==-1||now[c-'a']==cnt[c-'a']/2) continue;
				now[c-'a']++;
				for(int j=0;j<26;j++) if(s[j][n-1]-s[j][nex]+now[j]<cnt[j]/2) isok=0;
				if(!isok) now[c-'a']--; else{k=nex+1;ans=ans+c;break;}
			}
		}
		return ans;
	}
};
