// BEGIN CUT HERE

// END CUT HERE
#line 5 "EllysBulls.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define N 500005
const int maxn=55;

class EllysBulls{
	int n,K[2];
	string st[2][maxn];
	int bull[maxn];
	ll tot;
	string ans;
	
	int _rt,_sz;
	int _nxt[N][10];
	string _last[N];
	int _cnt[N];
	
	void solve(string now,int type){
		int s[maxn];
		for (int i=0;i<n;++i){
			s[i]=0;
			for (int j=0;j<now.size();++j)
				if (st[type][i][j]==now[j]) ++s[i];
			if (s[i]>bull[i]||bull[i]-s[i]>K[type^1]){/*cout<<now<<' '<<i<<' '<<s[i]<<endl;*/return;}
			if (type) s[i]=bull[i]-s[i];
		}
//		cout<<now<<" : "<<type<<endl;
		int u=_rt;
		for (int i=0;i<n;++i){
			if (!_nxt[u][s[i]]){
				if (type) return;
				_nxt[u][s[i]]=++_sz;
			}
			u=_nxt[u][s[i]];
		}
		if (type){
			ans=_last[u]+now;
			tot+=_cnt[u];
		}
		else{
			_last[u]=now;
			++_cnt[u];
		}
	}
	void dfs(int u,string now,int type){
		if (u==K[type]) solve(now,type);
		else for (char i='0';i<='9';++i) dfs(u+1,now+i,type);
	}
	public:
	string getNumber(vector <string> guesses, vector <int> bulls){
		n=guesses.size();
		K[0]=guesses[0].size()/2;
		K[1]=guesses[0].size()-K[0];
		for (int i=0;i<n;++i){
			st[0][i]=st[1][i]="";
			for (int j=0;j<guesses[i].size();++j)
				if (j<K[0]) st[0][i]+=guesses[i][j];
				else st[1][i]+=guesses[i][j];
//			cout<<st[0][i]<<endl<<st[1][i]<<endl<<endl;
		}
		for (int i=0;i<n;++i) bull[i]=bulls[i];
		ans="Liar";tot=0;
		_rt=_sz=1;
		memset(_nxt,0,sizeof(_nxt));
		memset(_cnt,0,sizeof(_cnt));
		dfs(0,"",0);
		dfs(0,"",1);
		if (tot>1) return "Ambiguity";
		return ans;
	}
};
