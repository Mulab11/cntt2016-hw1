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

const ld eps=1e-10;
const int N=55;

queue<int> q;
vi x,y,r;
int n;
bool vis[N],ign[N];
ld l[N],h[N];

ld dis(ld x1,ld y1,ld x2,ld y2){
	return sqrt(sqr(x1-x2)+sqr(y1-y2));
}
bool merge(ld x,ld y,ld l,ld r){
	return x-eps<r&&l-eps<y;
}
void spfa(){
	for(int i=0;i<n;i++) if(l[i]-eps<h[i]) q.push(i),vis[i]=1;
	while(!q.empty()){
		int i=q.front();q.pop();
		vis[i]=0;
		for(int j=0;j<n;j++){
			if(i==j||ign[j]) continue;
			ld d=dis(x[i],y[i],x[j],y[j]);
			if(merge(d-r[j],d+r[j],l[i],h[i])){
				bool isok=0;
				if(l[j]-eps>max(d-r[i],(ld)0.0)) l[j]=max(d-r[i],(ld)0.0),isok=1;
				if(h[j]+eps<min((ld)r[j],d+r[i])) h[j]=min((ld)r[j],d+r[i]),isok=1;
				if(isok&&!vis[j]) q.push(j),vis[j]=1;
			}
		}
	}
}

class CandyOnDisk{
public:
	string ableToAchieve(vector<int> x, vector<int> y, vector<int> r, int sx, int sy, int tx, int ty){
		if(dis(sx,sy,tx,ty)<eps) return "YES";
		n=x.size();
		memset(ign,0,sizeof(ign));
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				if(i==j) continue;
				if(dis(x[i],y[i],x[j],y[j])<eps){
					if(mp(r[i],i)>mp(r[j],j)) ign[j]=1; else ign[i]=1;
				}
			}
		::x=x;::y=y;::r=r;
		for(int i=0;i<n;i++){
			l[i]=r[i];h[i]=0;
			if(ign[i]) continue;
			ld d=dis(x[i],y[i],sx,sy);
			if(d-eps<r[i]) l[i]=h[i]=d;
		}
		spfa();
//		for(int i=0;i<n;i++) printf("%.3f %.3f\n",l[i],h[i]);
		for(int i=0;i<n;i++){
			ld d=dis(tx,ty,x[i],y[i]);
			if(d>l[i]-eps&&d-eps<h[i]) return "YES";
		}
		return "NO";
	}
};

