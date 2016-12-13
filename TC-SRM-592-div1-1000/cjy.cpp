#include<bits/stdc++.h>
#define cd complex<double>
using namespace std;
int n,i,j,k;
vector<cd> dft(vector<cd> a,bool F)
{
	cd w=polar(1.,(2-4*F)*acos(-1)/n),x=1,y;
	vector<cd> b(n);
	int i,j;
	for(i=0;i<n;x*=w,i++)for(y=1,j=0;j<n;j++)b[i]+=y*a[j],y*=x;
    return b;
}
class SplittingFoxes2
{
	public:
		vector<int> getPattern(vector<int>a)
		{
			n=a.size();
			vector<int> f(n),s={-1},e(n),r;
			vector<cd> b(a.begin(),a.end()),c;
			for(b=dft(b,0),i=0;i<n;i++)b[i]=sqrt(b[i]);
			for(i=0;i<(1<<n/2+1);i++)
			{
				for(c=b,j=0;j<n;j++)if(i>>min(j,n-j)&1)c[j]=-c[j];
				for(c=dft(c,1),j=0;j<n;j++)if(f[j]=c[min(j,n-j)].real()/n+.5,f[j]<0)goto E;
				for(r=e,j=0;j<n;j++)for(k=0;k<n;k++)r[(j+k)%n]+=f[j]*f[k];
				if(r==a)s=(s[0]==-1)?f:min(s,f);E:;
			}
			return s;
		}
};
