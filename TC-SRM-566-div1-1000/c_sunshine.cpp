#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
typedef double DB;
typedef long long LL;
const DB pi=DB(acosl(-1));
const DB eps=1e-8;
const int M=100007;

int dcmp(const DB &x)
{return x<-eps?-1:(x>eps);}

class FencingPenguins
{
	public:
	int n,m;
	int col[55];
	LL s[233][233],cs[233][233];
	bool can[233][233];
	int h[233][233][2],g[233][233],f[233][233];
	vector<int> x,y;
	DB px[233],py[233];
	
	DB cross(DB x0,DB y0,DB x1,DB y1,DB x2,DB y2)
	{
		return (x1-x0)*(y2-y0)-(y1-y0)*(x2-x0);
	}
	
	void getmask(DB x1,DB y1,DB x2,DB y2,LL &s,LL &cs)
	{
		s=cs=0;
		int t;
		for(int i=0;i<m;i++)
		{
			t=dcmp(cross(x1,y1,x2,y2,x[i],y[i]));
			if(t>=0)s|=1LL<<i,cs|=1LL<<col[i];
		}
	}
	
	int countWays(int numPosts,int radius,vector<int> x,vector<int> y,string color)
	{
		n=numPosts,m=x.size();this->x=x,this->y=y;
		for(int i=0;i<m;i++)col[i]=color[i]<='Z'?color[i]-'A':color[i]-'a'+26;
		for(int i=0;i<n;i++)
		{
			DB a=pi*2*i/n;
			px[i]=radius*cos(a);
			py[i]=radius*sin(a);
		}
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				getmask(px[i],py[i],px[j],py[j],s[i][j],cs[i][j]);
		if(s[0][n-1]!=0)return 0;
		//can[i][j]=1 if it is valid to place a fence between post i and j.
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				can[i][j]=((cs[i][j]&cs[j][i])==0);
		for(int i=0;i<n;i++)h[i][i][1]=1;
		for(int l=n-1;~l;l--)
			for(int r=l+1;r<n;r++)
			{
				for(int t=0;t<2;t++)
				{
					int &res=h[l][r][t];
					res=0;
					for(int nl=l+1;nl<=r;nl++)
						if(can[l][nl])
						{
							LL mask=s[l][nl]&s[nl][r]&s[r][l];//the set of penguins inside the polygon.
							int nt=t|(mask>0);//get new t.
							int p=h[nl][r][nt];
							if(!s[nl][l])res+=p;//range [l,nl] is empty.
							else if(nl-l>3&&!(s[nl][l]&s[l+1][nl-1]))//otherwise we should fence penguins there.
								res+=(LL)p*f[l+1][nl-1]%M;
						}
					res%=M;
				}
				int res=0;
				for(int nr=r;nr>l+1;nr--)//pick vertex nr connected to l.
					if(can[l][nr])
					{
						int p=h[l][nr][0];
						LL mask=s[r][l]&s[l][nr];
						if(!mask)res+=p;//triangle (l,r,nr) is empty.
						else if(nr+2<r&&!(mask&s[nr+1][r]))//otherwise we should fence penguins there.
							res+=(LL)f[nr+1][r]*p%M;
					}
				g[l][r]=res%M;
				res=0;
				//pick a vertex to fix as the lowest indexed active vertex.
				for(int nl=l;nl<=r;nl++)
				{
					LL mask=s[r][l]&s[nl][r];
					if(!mask)res+=g[nl][r];//Use g[nl][r] to count the number of ways.
				}
				f[l][r]=res%M;
			}
			return f[0][n-1];
	}
};

