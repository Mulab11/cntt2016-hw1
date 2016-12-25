#include<bits/stdc++.h>
using namespace std;
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0},d,i,n;
long long x,y;
class RobotHerb
{
	public:
		long long getdist(int T,vector<int> a)
		{
			for(n=a.size();i<4*n;i++)x+=dx[d]*a[i%n],y+=dy[d]*a[i%n],d=(d+a[i%n])%4;
			for(x*=T/4,y*=T/4,T%=4,i=0;i<T*n;i++)x+=dx[d]*a[i%n],y+=dy[d]*a[i%n],d=(d+a[i%n])%4;
			return abs(x)+abs(y);
		}
};
