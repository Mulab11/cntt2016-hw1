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

int l,r,m,n,second,num[100];
vector<string> a;
vi b;
map<vi,int> s;
vector<vi> res;

void dfs(int x,int now){
	if(x>r){
		bool isok=1;
		vi tmp;tmp.clear();
		for(int i=0;i<m;i++){
			int cnt=0;
			for(int j=l;j<=r;j++)
				if(a[i][j]==num[j]+'0') cnt++;
			if(cnt>b[i]){isok=0;break;}
			tmp.pb(cnt);
		}
		if(!second){
			tmp.pb(now);
			if(isok) res.pb(tmp);
			return;
		}
		if(!isok) return;
		if(s[tmp]) s[tmp]=-1; else s[tmp]=now;
		return;
	}
	for(int i=0;i<10;i++){
		num[x]=i;
		dfs(x+1,now*10+i);
	}
}

string make(int x,int l){
	stringstream ss;
string str;
ss<<x;
ss>>str;
while(str.size()<l) str='0'+str;
return str;
}

class EllysBulls{
public:
	string getNumber(vector<string> guesses, vector<int> bulls){
		a=guesses;b=bulls;s.clear();
		n=a[0].size();m=a.size();
		l=0,r=n/2-1;
		second=0;dfs(l,0);
		l=n/2;r=n-1;
		second=1;dfs(l,0);
		string ans="";int isok=0;
		for(int i=0;i<res.size();i++){
			vi tmp;tmp.clear();
			for(int j=0;j<m;j++)
				tmp.pb(b[j]-res[i][j]);
			if(s.find(tmp)!=s.end()){
				if(isok) return "Ambiguity";
				if(s[tmp]==-1) return "Ambiguity";
				isok=1;
				ans=make(res[i][m],n/2)+make(s[tmp],n-n/2);
			}
		}
		if(ans=="") return "Liar"; return ans;
	}
};
