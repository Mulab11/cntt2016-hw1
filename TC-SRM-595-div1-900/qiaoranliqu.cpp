#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<cmath>

#define pb push_back

using namespace std; 

#define N 2505

struct Point{int x,y,prob;}A[N];
int n,i,j,k;
double ans;
inline Point operator -(Point a,Point b){ return (Point){a.x-b.x,a.y-b.y,0}; }
int cha(Point x,Point y)
{
	 return x.x*y.y-x.y*y.x;
}
int cross(Point x,Point y,Point z)
{
	  return cha(y-x,z-x);
}
class Constellation{
	 public:
	 	double expectation (vector<int> x,vector<int> y,vector<int> prob)
	 	{
	 		   n=x.size();
	 		   for (i=1;i<=n;++i)
	 		   A[i]=(Point){x[i-1],y[i-1],prob[i-1]};
	 		   for (i=1;i<=n;++i)
	 		     for (j=i+1;j<=n;++j)
	 		     {
	 		     	    double k1=A[i].prob/1000.*A[j].prob/1000.,k2=k1;
						for (k=1;k<=n;++k)
						  if (k!=i&&k!=j)
						  {  
						      int K=cross(A[i],A[j],A[k]);
						      if (K>0) k1=k1*(1000-A[k].prob)/1000.; 
						      else if (K<0) k2=k2*(1000-A[k].prob)/1000.;
							  else if (A[k].x>=min(A[i].x,A[j].x)&&A[k].x<=max(A[i].x,A[j].x)&&A[k].y>=min(A[i].y,A[j].y)&&A[k].y<=max(A[i].y,A[j].y))
							  {
							        k1*=(1000-A[k].prob)/1000.;
							        k2*=(1000-A[k].prob)/1000.;
							  }
						  }
							  ans+=cross((Point){0,0,0},A[i],A[j])*(k1-k2);
				  }
				  return fabs(ans/2.); 
	 	}
}FFT;
