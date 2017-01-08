#include<bits/stdc++.h>
using namespace std;
int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1},v[200][200],x=99,y=x,k,i,j,l=x,r=x,u=x,d=x,C;
class RotatingBot//模拟
{
	public:
		int minArea(vector<int> a)
		{
			for(auto c:a)x+=dx[k]*c,y+=dy[k]*c,k=k+1&3,l=min(l,x),r=max(r,x),d=min(d,y),u=max(u,y);
			k=0;v[x=99][y=99]=1;
			for(C=0;C<a.size();C++)
			{
				while(a[C]--){if(x+=dx[k],y+=dy[k],v[x][y])return -1;v[x][y]=1;}
				if(C<a.size()-1&&!v[i=x+dx[k]][j=y+dy[k]]&&i>=l&&i<=r&&j>=d&&j<=u)return -1;k=(k+1)%4;
			}
			return(r-l+1)*(u-d+1);
		}
};
