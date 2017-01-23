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
int cnt[N][N];
bool vis[N],use[N];

class StringGame{
public:
	vector<int> getWinningStrings(vector<string> s){
		int n=s.size();
//		debug(n);
		vi ans;ans.clear();
		memset(cnt,0,sizeof(cnt));
//		debug(n);
		for(int i=0;i<n;i++)
			for(int j=0;j<s[i].size();j++) cnt[i][s[i][j]-'a']++;
//		debug(n);
		for(int i=0;i<n;i++){
			bool isok=0;
			memset(vis,0,sizeof(vis));
			memset(use,0,sizeof(use));
			while(1){
				bool ext=0;
				for(int j=0;j<26;j++){
					if(use[j]) continue;
					bool op=1,maxx=1;
					for(int k=0;k<n;k++){
						if(vis[k]||k==i) continue;
						if(cnt[i][j]<=cnt[k][j]) maxx=0;
						if(cnt[i][j]<cnt[k][j]){op=0;break;}
					}
					if(maxx){isok=1;break;}
					if(op){
						use[j]=1;
						for(int k=0;k<n;k++) 
							if(cnt[i][j]>cnt[k][j]) vis[k]=1;
						ext=1;
					}
				}
				if(isok) break;
				if(!ext) break;
			}
			if(isok) ans.pb(i);
		}
		return ans;
	}
};
