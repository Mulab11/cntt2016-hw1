#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
template<class T>inline bool ten(T &x,const T &y){return y<x?x=y,1:0;}
template<class T>inline bool rel(T &x,const T &y){return x<y?x=y,1:0;}

class EllysChessboard
{
	public:
	int R,C,n;
	vector<int> x,y;
	int f[18][18][18][18];
	
	inline int ABS(const int &xx){return xx<0?-xx:xx;}
	
	inline bool inside(const int &x,const int &y,const int &xl,const int &xr,const int &yl,const int &yr)
	{
		return x>=xl&&x<=xr&&y>=yl&&y<=yr;
	}
	
	int dp(int xl,int xr,int yl,int yr)
	{
		int &res=f[xl][xr][yl][yr];
		if(~res)return res;
		bool finished=1;
		res=1<<30;
		for(int i=0;i<n;i++)
		{
			if(!inside(x[i],y[i],xl,xr,yl,yr))//Find a new piece not placed
			{
				finished=0;
				int xl_=xl,xr_=xr,yl_=yl,yr_=yr;
				int xd=0,yd=0,d;
				//get new rectangle
				ten(xl_,x[i]);
				rel(xr_,x[i]);
				ten(yl_,y[i]);
				rel(yr_,y[i]);
				//Calculate the total cost of all new placed pieces.
				xd=max(ABS(x[i]-xl),ABS(x[i]-xr));
				yd=max(ABS(y[i]-yl),ABS(y[i]-yr));
				d=max(xd,yd);
				for(int j=0;j<n;j++)
					if(j!=i&&inside(x[j],y[j],xl_,xr_,yl_,yr_)&&!inside(x[j],y[j],xl,xr,yl,yr))
					{
						xd=max(ABS(x[j]-xl_),ABS(x[j]-xr_));
						yd=max(ABS(y[j]-yl_),ABS(y[j]-yr_));
						d+=max(xd,yd);
					}
				ten(res,dp(xl_,xr_,yl_,yr_)+d);
			}
		}
		if(finished)res=0;
		return res;
	}
	
	int minCost(vector<string> board)
	{
		//rotate the chess board 45 degrees to change Manhattan distance into Chebyshev distance
		R=board.size();
		C=board[0].size();
		for(int i=0;i<R;i++)
			for(int j=0;j<C;j++)
				if(board[i][j]=='#')
					x.push_back(i+j),
					y.push_back(i-j);
		if(x.empty())return 0;
		n=x.size();
		int miny=y[0];
		for(int i=1;i<n;i++)
			miny=min(miny,y[i]);
		for(int i=0;i<n;i++)
			y[i]-=miny;
		memset(f,-1,sizeof(f));
		int ans=1<<30;
		//f[xl][xr][yl][yr]: the minimum cost to place all pieces in the rectangle (xl,yl)-(xr,yr)
		for(int i=0;i<n;i++)
			ans=min(ans,dp(x[i],x[i],y[i],y[i]));
		return ans;
	}
};

