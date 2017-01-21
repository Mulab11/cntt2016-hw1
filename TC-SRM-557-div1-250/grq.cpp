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

string yes="YES",no="NO";

bool check(int x,int y,string use){
	for(int i=0;i<use.size();i++){
		if(use[i]=='U') x++; else x--;
		if(x<0) return 0;
	}
	return 1;
}

class FoxAndMountainEasy{
public:
	string possible(int n, int h0, int hn, string history){
		int m=hn-h0;
		if(abs(m%2)!=abs(n%2)) return no;
		int u=0,d=0;
		if(m<0) d=-m; else u=m;
		d+=(n-abs(m))/2,u+=(n-abs(m))/2;
		for(int i=0;i<history.size();i++) if(history[i]=='U') u--; else d--;
		if(u<0||d<0) return no;
		for(int i=0;i<u;i++) history='U'+history;
		for(int i=0;i<d;i++) history=history+'D';
		if(check(h0,hn,history)) return yes;
		return no;
	}
};
