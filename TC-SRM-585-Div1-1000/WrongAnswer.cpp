#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
class EnclosingTriangle{
public:
	struct Point{
		int x,y;
		bool operator<(const Point&p)const{return x<p.x||x==p.x&&y<p.y;}
		bool onleft(Point a,Point b){return 1ll*(b.x-a.x)*(y-a.y)>1ll*(x-a.x)*(b.y-a.y);}
		bool onright(Point a,Point b){return 1ll*(b.x-a.x)*(y-a.y)<1ll*(x-a.x)*(b.y-a.y);}
	}R[234444],P[22],S[44];
	int l[234444],r[234444];
	long long sum[234444];
	long long getNumber(int m, vector <int> x, vector <int> y){
		for(int i=0;i<m;i++)R[i]=(Point){i,0},R[i+m]=(Point){m,i},R[i+2*m]=(Point){m-i,m},R[i+3*m]=(Point){0,m-i};
		int n=x.size(),s=-1;m*=4;
		for(int i=0;i<n;i++)P[i]=(Point){x[i],y[i]};
		sort(P,P+n);
		for(int i=0;i<n;S[++s]=P[i++])
			while(s>0&&!P[i].onright(S[s-1],S[s]))--s;
		for(int i=n,t=s;i--;S[++s]=P[i])
			while(s>t&&!P[i].onright(S[s-1],S[s]))--s;
		l[0]=r[0]=1;
		int pl=0,pr=0;
		for(int i=1;i<s;i++)S[i].onleft(R[0],S[pr])?pr=i:1,S[i].onright(R[0],S[pl])?pl=i:1;
		for(int i=0;i<m;l[i+1]=l[i],r[i+1]=r[i],i++){
			while(S[(pl+s-1)%s].onright(R[i],S[pl]))pl=(pl+s-1)%s;
			while(S[(pr+s-1)%s].onleft(R[i],S[pr]))pr=(pr+s-1)%s;
			while(l[i]<m&&!S[pl].onright(R[i],R[l[i]]))++l[i];
			while(r[i]<m&&S[pr].onleft(R[i],R[r[i]]))++r[i];
		}
		long long ans=*sum=0;
		for(int i=0;i<m;i++)sum[i+1]=sum[i]+l[i];
		for(int i=0,p=0;i<m;i++){
			while(p<=i||p<l[i]&&l[p]<=r[i])++p;
			ans+=sum[l[i]]-sum[p]-r[i]*(long long)(l[i]-p);
			if(r[i]<l[i]&&p<l[i])ans--;
		}
		return ans;
	}
};
