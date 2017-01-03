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
#define VS vector<string>
#define MC(a,b) memcpy(a,b,sizeof b)
#define MS(a,b) memset(a,b,sizeof a)

using namespace std;

const int maxn=55;
struct circle{
	int x,y,r;
	circle(int X=0,int Y=0,int R=0){x=X,y=Y,r=R;}
	bool operator <(const circle&w)const{return r<w.r;}
}a[maxn];
int blt[maxn],sg[maxn];
VI ins[maxn];
bool contain(circle a,circle b){
	return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y)<=b.r*b.r;
}
int n;
/*
把图转成森林模型，然后转COT3
*/
struct CirclesGame{
	string whoCanWin(VI x,VI y,VI r){
		n=x.size();
		rep(i,0,n-1) a[i+1]=circle(x[i],y[i],r[i]);
		sort(a+1,a+n+1);
		rep(i,1,n) rep(j,i+1,n){
			if (contain(a[i],a[j])){
				blt[i]=j;ins[j].pb(i);
				break;
			}
		}
		rep(i,1,n){
			if (!ins[i].size()){sg[i]=1;continue;}
			sg[i]=0;
			rep(j,0,ins[i].size()-1){
				int tmp=sg[i];
				rep(_,0,sg[i]) rep(k,0,sg[ins[i][j]]) tmp=max(tmp,_^k);
				sg[i]=tmp;
			}
			sg[i]++;
		}
		int ans=0;
		rep(i,1,n) if (!blt[i]) ans^=sg[i];
		if (ans) return "Alice";
			else return "Bob";
	}
};
