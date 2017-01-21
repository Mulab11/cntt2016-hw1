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

const int N=5005,M=N*N;
int a[N];
short s[M];
vector<pii> b;
vi c;
int calc(int x){return upper_bound(a,a+5001,x)-a-1;}
int check(int x){
	if(x>5000*5000) return 0;
	int t=s[x];
	if(t) return t;
	return 0;
}

class FindPolygons{
public:
	double minimumPolygon(int L){
		if(L&1) return -1;
		if(L==2) return -1;
		for(int i=1;i<=5000;i++) s[i*i]=i;
		b.clear();c.clear();
		for(int i=1;i<=5000;i++){
			int to=calc(sqr(5000)-sqr(i));
			for(int j=i+1;j<=to;j++){
				int t=check(sqr(i)+sqr(j));
				if(!t) continue;
				b.pb(mp(i,j));b.pb(mp(j,i));
				c.pb(t);c.pb(t);
			}
		}
		for(int i=1;i<=5000;i++) b.pb(mp(i,0)),c.pb(i);
		debug(b.size());
		int ans=L+3;
		for(int i=0;i<b.size();i++){
			if(c[i]>L) continue;
			for(int j=i+1;j<b.size();j++){
				if(c[j]>L) continue;
				if(b[i].FF*b[j].SS==b[i].SS*b[j].FF) continue;
				int len=check(sqr(b[i].FF-b[j].FF)+sqr(b[i].SS-b[j].SS));
				if(len&&len+c[i]+c[j]==L) ans=min(ans,max(abs(c[i]-c[j]),max(abs(len-c[i]),abs(len-c[j]))));
			}
		}
		if(ans<L) return ans;
		if(L&3) return 1; 
		return 0;
	}
};