#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
const int M=1000000007;
const int N=100000;
class WolfPack
{
	public:
	int n,m;
	int fc[N*4+5],fi[N*4+5];
	
	int pow(int a,int b)
	{
		int s=1;
		for(;b;b>>=1,a=(LL)a*a%M)
			if(b&1)s=(LL)s*a%M;
		return s;
	}
	
	int comb(int n,int k)//number of combination
	{
		if(k<0||k>n)return 0;
		return (LL)fc[n]*fi[k]%M*fi[n-k]%M;
	}
	
	int get(vector<int> &x,const int &p)//number of ways to rally at p
	{
		int res=1;
		for(int i=0;i<n;i++)
		{
			if(p-x[i]+m&1)return 0;//Impossible
			//the number of ways for i-th wolf is C(m,(p-x[i]+m)/2)
			res=(LL)res*comb(m,p-x[i]+m>>1)%M;
		}
		return res;
	}
	
	int calc(vector <int> x, vector <int> y, int m)
	{
		//We use (x+y,x-y) to represent the original point(x,y)
		//and at each step the absolute change to the new x and y coordinates are both 1.
		//So the x-coordinate and y-coordinate are independent.
		//We can solve them individually and simply multiply the number of ways.
		n=x.size();this->m=m;
		for(int xx,yy,i=0;i<n;i++)
		{
			xx=x[i],yy=y[i];
			x[i]=xx+yy;
			y[i]=xx-yy;
		}
		for(int i=fc[0]=1;i<=N<<2;i++)fc[i]=(LL)fc[i-1]*i%M;
		fi[N<<2]=pow(fc[N<<2],M-2);
		for(int i=N<<2;i;i--)fi[i-1]=(LL)fi[i]*i%M;
		int ansx,ansy;
		ansx=ansy=0;
		//Pick the coordinates of the rally point.
		for(int X=-N-N;X<=N+N;X++)
			ansx=(ansx+get(x,X))%M;
		for(int Y=-N-N;Y<=N+N;Y++)
			ansy=(ansy+get(y,Y))%M;
		return (LL)ansx*ansy%M; 
	}
};

