#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>

using namespace std;

#define N 2000005
const int Mo=(int)1e9+7;
int A[5],fac[N],inv[N];
int C(int x,int y)
{
	    if (x==y) return 1;
	    if (x<y) return 0; 
	    return 1ll*fac[x]*inv[y]%Mo*inv[x-y]%Mo; 
}
void jia(int &x,int y)
{
	 x+=y; if (x>=Mo) x-=Mo;
}
int work(int x)
{
	    int i,j,k,ans=0;
		for (i=0;i<=min(x,A[2]);++i)
		{
			   int sum=C(x,i),resty=A[2]-i;
			   sum=1ll*sum*C(i+resty-1,resty)%Mo;
			   int restz=A[1]-resty-(x-i);
			   if (restz<0) continue;
			   sum=1ll*sum*C(2*i,restz)%Mo;
			   jia(ans,sum);
		}
		return ans;
}
int power(int x,int y)
{
	   int sum=1;
	   for (;y;y>>=1,x=1ll*x*x%Mo) if(y&1) sum=1ll*sum*x%Mo;
	   return sum;
}
class LittleElephantAndBoard{
  public:
  int getNumber(int M,int R,int G,int B)
  {
  	   int i;
  	   fac[0]=1;
  	   for (i=1;i<N;++i) fac[i]=1ll*fac[i-1]*i%Mo;
	   inv[N-1]=power(fac[N-1],Mo-2);
	   for (i=N-1;i;--i) inv[i-1]=1ll*inv[i]*i%Mo;
  	   A[1]=M-R; A[2]=M-G; A[3]=M-B;
  	   sort(A+1,A+4); if (A[1]<0) return 0;
  	   int ans=0;
	   jia(ans,work(A[3]-1));
	   jia(ans,work(A[3])*2%Mo);
	   jia(ans,work(A[3]+1));
	   return ans*2%Mo;
  }
}R;
int main()
{
	 printf("%d\n",R.getNumber(10,7,7,6));
}
