#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>

using namespace std;

#define N 2000005
const int Mo=(int)1e9+7;
int Min[N],vis[N],Sum[N],Q[N],j,ans,sum,k;
class BigFatInteger{
  public:
  int minOperations(int A,int B)
  {
  	   int i;
  	   for (i=2;i<=A;++i)
  	     if (!vis[i])
  	     {
  	     	   for (j=i;j<=A;j+=i) 
  	     	   {
  	     	   	   vis[j]=1;
  	     	   	   if (!Min[j]) Min[j]=i;
			   }
	     }
	  for (;A>1;A/=Min[A])
	  {
	  	    if (!Q[0]||Q[Q[0]]!=Min[A]) ++Q[0],Q[Q[0]]=Min[A];
	  	    ++Sum[Q[0]];
	  }
	  for (i=1;i<=Q[0];++i) Sum[i]*=B;
	  ans+=Q[0]; sum=0;
	  for (i=1;i<=Q[0];++i)
	  {
	  	   for (j=0,k=Sum[i]>>1;k;++j,k>>=1);
	  	   if ((1<<j)!=Sum[i]) ++j;
	  	   sum=max(sum,j);
	  }
	  ans+=sum;
	  return ans;
  }
}R;
int main()
{ 
     R.minOperations(162,1);
}
