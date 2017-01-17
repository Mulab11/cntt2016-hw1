#include <bits/stdc++.h>
#define FF(x) (x)*(x)
#define VI vector<int>
#define PB A.push_back(make_pair
using namespace std;
int n,i;vector<pair<double,double> >A;
double pi=acos(-1);VI R;struct P{double x,y;}O[55];
double DIS(P a,P b){return sqrt(FF(a.x-b.x)+FF(a.y-b.y));}
void ADD(double l,double r)
{
	while(l<-pi)l+=2*pi;
	while(r>pi)r-=2*pi;
	if(l<=r)PB(l,r));else PB(l,pi)),PB(-pi,r));
}
int CAN(double D)
{
	for(A.clear(),i=1;i<n;i++)
	{
		double d=DIS(O[i],O[0]),l=sqrt(FF(d)-FF(R[0])),a=atan2(O[i].y-O[0].y,O[i].x-O[0].x),b,e;
		if(D>l-R[i]){if(e=b=acos((FF(d)+FF(R[0])-FF(l))/2/R[0]/d),b+=(D-l+R[i])/R[0],ADD(a-b,a+b),D>l-R[i]+(pi-e)*R[0])return 0;}
		else if(D>=d-R[0]-R[i])b=acos((FF(d)+FF(R[0])-FF(D+R[i]))/2/R[0]/d),ADD(a-b,a+b);
	}sort(A.begin(),A.end());D=-pi;
	for(auto x:A){if(x.first>D)return 1;D=max(D,x.second);}
	return D<pi;
}
class CircusTents
{
	public:
		double findMaximumDistance(VI x,VI y,VI r)
		{
			for(R=r,n=x.size();i<n;i++)O[i]=P{x[i],y[i]};
			double L=0,R=1e9,M;
			while(R-1e-9>L)M=(L+R)/2,CAN(M)?L=M:R=M;
			return L;
		}
};
