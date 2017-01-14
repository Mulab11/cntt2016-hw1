#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
const double eps=1e-10;

double dist(int x1,int y1,int x2,int y2)
{return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));}

class Constellation
{
	public:
	int n;
	double p[55];
	double expectation(vector<int> x,vector<int> y,vector<int> prob)
	{
		//If we have determined the convex hull, the area is 1/2 \sum OP_i <cross> OP_{i+1 mod n}
		//The expected value is a linear operator,
		//so the answer can be written like 1/2 \sum pr(i,j) OP_i <cross> OP_j.
		//While pr(i,j) is the possibility that P_i,P_j is a side of the convex hull,
		//and it is anticlockwise from P_i to P_j 
		n=prob.size();
		for(int i=0;i<n;i++)
			p[i]=1.*prob[i]/1000.;
		double ans=0,pr;
		int cs;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(i!=j)
				{
					//P_i and P_j should occur in the final set
					pr=p[i]*p[j];
					for(int k=0;k<n;k++)
					{
						cs=(x[j]-x[i])*(y[k]-y[i])-(y[j]-y[i])*(x[k]-x[i]);
						//Any point on the right of P_i -> P_j or exactly on line P_i - P_j but not on segment P_i - P_j
						//must not occur in the final set. 
						if(cs<0||(cs==0&&dist(x[k],y[k],x[i],y[i])+dist(x[k],y[k],x[j],y[j])>dist(x[i],y[i],x[j],y[j])+eps))
							pr*=1.-p[k];
					}
					ans+=pr*(x[i]*y[j]-y[i]*x[j]);
				}
		return ans/2;
	}
};

