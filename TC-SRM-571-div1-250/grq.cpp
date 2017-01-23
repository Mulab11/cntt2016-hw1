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

const int inf=1e9+9;
int calc(string a){
	if(a.size()>10||(a.size()==9&&a[0]>'1')) return inf;
	int ans=0;
	for(int i=0;i<a.size();i++) ans=ans*10+a[i]-'0';
	return ans;
}
string make(int x){
	string ans="";
	for(;x;) ans=(char)(x%10+'0')+ans;
	return ans;
}

class FoxAndMp3{
public:
	vector<string> playList(int n){
		string now="1";
		vector<string> res;res.clear();
		for(int i=1;i<=50;i++){
			res.pb(now+".mp3");
			if(i==n) break;
			if(calc(now+'0')<=n){now+='0';continue;}
			int m=now.size();
			for(int j=m-1;~j;j--){
				if(now[j]=='9'){now=now.substr(0,j);continue;}
				now[j]++;
				if(calc(now)<=n) break;
				now=now.substr(0,j);
			}
		}
		return res;
	}
};
