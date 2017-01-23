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

const int N=105;
const double pi=acos(-1),eps=1e-11;
struct node{double x,y;}p[N];

int n,tot;

inline bool cmp(node a,node b){return a.x<b.x;}
bool check(double d,vi x,vi y,vi r){
	tot=0;
	for(int i=1;i<n;i++){
		double dis=sqrt(sqr((double)x[i]-x[0])+sqr((double)y[i]-y[0])),
		len=sqrt(sqr(dis)-sqr(r[0]))-r[i],
		a0=atan2((double)y[i]-y[0],(double)x[i]-x[0]);
		if(r[0]+r[i]+d<dis) continue;
		if(d>=len){
			double a1=atan2(len+r[i],(double)r[0]),pd=d-len,a2=pd/r[0];
			if(a1+a2>=pi) p[++tot]=(node){-pi*4,pi*4}; else p[++tot]=(node){a0-a1-a2,a0+a1+a2};
		}
		else{
			double a1=acos((sqr(dis)-sqr(r[i]+d)+sqr(r[0]))/2.0/dis/r[0]);
			p[++tot]=(node){a0-a1,a0+a1};
		}
	}
	int tmp=tot;
	for(int i=1;i<=tmp;i++)
		if(p[i].x<0) p[++tot]=(node){p[i].x+pi*2,p[i].y+pi*2};
	sort(p+1,p+tot+1,cmp);
	double maxy=0.0;
	for(int i=1;i<=tot;i++)
		if(p[i].x<=maxy) maxy=max(p[i].y,maxy);
	return maxy<pi*2;
}

class CircusTents{
public:
	double findMaximumDistance(vector<int> x, vector<int> y, vector<int> R){
		n=x.size();
		double l=0,r=1e5;
		while(l+eps<r){
			double mid=(l+r)/2.0;
			if(check(mid,x,y,R)) l=mid; else r=mid;
		}
		return r;
	}
};
