#include <vector>
#include <string>
#include <cmath>
using namespace std;
class CandyOnDisk{
public:
	int n,x[55],y[55],r[55];
	long double L[55],R[55],d[55][55];
	bool vis[55];
	long double dist(int x1,int y1,int x2,int y2){
		long long dx=x1-x2,dy=y1-y2;
		return sqrtl(dx*dx+dy*dy);
	}
	long double max(long double a,long double b){return a>b?a:b;}
	long double min(long double a,long double b){return a<b?a:b;}
	bool upd(int i,int j){
		bool c=0;
		long double ll=max(d[i][j]-r[i],0),rr=min(r[j],d[i][j]+r[i]);
		if(!vis[j])c=vis[j]=1,L[j]=ll,R[j]=rr;
		else{
			if(ll<L[j])c=1,L[j]=ll;
			if(rr>R[j])c=1,R[j]=rr;
		}	
		return c;
	}
	bool solve(int sx,int sy,int tx,int ty){
		if(sx==tx&&sy==ty)return 1;
		bool changed=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)d[i][j]=dist(x[i],y[i],x[j],y[j]);
		for(int i=0;i<n;i++)
			if(dist(x[i],y[i],sx,sy)<=r[i])vis[i]=1,L[i]=R[i]=dist(x[i],y[i],sx,sy),changed=1;
		while(changed)
			for(int i=changed=0;i<n;i++)if(vis[i])
				for(int j=0;j<n;j++)if(j!=i)
					if(R[i]+r[j]>=d[i][j]&&L[i]-r[j]<=d[i][j])changed|=upd(i,j),changed|=upd(j,i);
		for(int i=0;i<n;i++)if(vis[i]&&dist(x[i],y[i],tx,ty)>=L[i]&&dist(x[i],y[i],tx,ty)<=R[i])return 1;
		return 0;
	}
	string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty){
		for(int i=0;i<x.size();i++){
			bool find=0;
			for(int j=0;j<n&&!find;j++)if(this->x[j]==x[i]&&this->y[j]==y[i])find=1,r[i]>this->r[j]?this->r[j]=r[i]:1;
			if(!find)this->x[n]=x[i],this->y[n]=y[i],this->r[n++]=r[i];
		}
		return solve(sx,sy,tx,ty)?"YES":"NO";
	}
};
