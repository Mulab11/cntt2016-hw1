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

const string pos="Possible",imp="Impossible";
vector<pii> a,b;

class FoxAndChess{
public:
	string ableToMove(string begin, string target){
		a.clear();b.clear();
		for(int i=0;i<begin.size();i++)
			if(begin[i]!='.') a.pb(mp(i,begin[i]=='L'));
		for(int i=0;i<target.size();i++)
			if(target[i]!='.') b.pb(mp(i,target[i]=='L'));
		if(a.size()!=b.size()) return imp;
		for(int i=0;i<a.size();i++){
			if(a[i].SS!=b[i].SS) return imp;
			if(a[i].SS&&a[i].FF<b[i].FF) return imp;
			if(!a[i].SS&&b[i].FF<a[i].FF) return imp;
		}
		return pos;
	}
};
