#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<sstream>
using namespace std;
typedef long long LL;

vector<int> get_vi(vector<string> str)
{
	stringstream s;
	for(int i=0;i<str.size();i++)s<<str[i];
	vector<int> res;
	int u;
	while(s>>u)res.push_back(u);
	return res;
}

class CheckerFreeness
{
	public:
	
	struct point
	{
		int x,y;
		point(const int &_x=0,const int &_y=0):x(_x),y(_y){}
		point operator-(const point &o)const{return point(x-o.x,y-o.y);}
		LL operator*(const point &o)const{return (LL)x*o.y-(LL)y*o.x;}
	}w[233],b[233];
	
	unsigned bwl[233][233][10],bwr[233][233][10],wwl[233][233][10];
	int nw,nb;
	
	string isFree(vector<string> whiteX,vector<string> whiteY,vector<string> blackX,vector<string> blackY)
	{
		vector<int> tx=get_vi(whiteX),ty=get_vi(whiteY);
		nw=tx.size();
		for(int i=0;i<nw;i++)
			w[i]=point(tx[i],ty[i]);
		tx=get_vi(blackX),ty=get_vi(blackY);
		nb=tx.size();
		for(int i=0;i<nb;i++)
			b[i]=point(tx[i],ty[i]);
		for(int i=0;i<nb;i++)
			for(int j=0;j<nw;j++)
				for(int k=0;k<nb;k++)
				{
					LL t=(w[j]-b[i])*(b[k]-b[i]);
					if(t>0)bwl[i][j][k>>5]|=1u<<(k&31);//The set of points on the left of the line b[i]-w[j]
					if(t<0)bwr[i][j][k>>5]|=1u<<(k&31);//The set of points on the right of the line b[i]-w[j]
				}
		for(int i=0;i<nw;i++)
			for(int j=0;j<nw;j++)
				for(int k=0;k<nb;k++)
				{
					LL t=(w[j]-w[i])*(b[k]-w[i]);
					if(t>0)wwl[i][j][k>>5]|=1u<<(k&31);//The set of points on the left of the line w[i]-w[j]
				}
		int sz=(nb-1>>5)+1;
		unsigned *x,*y,*z;
		for(int i=0;i<nb;i++)
			for(int l=0;l<nw;l++)
				for(int r=0;r<nw;r++)
					if(l!=r&&(w[r]-b[i])*(w[l]-b[i])>0)
					{
						//Pick all possible triples of two white points and one black point.
						x=bwl[i][r];
						y=bwr[i][l];
						z=wwl[l][r];
						//Check if there is at least one valid black point for the last vertex.
						for(int j=0;j<sz;j++)
							if(x[j]&y[j]&z[j])
								return "NO";
					}
		return "YES";
	}
	
};

