#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<string>
#include<cmath>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair

#define N 1505
#define M 200005
#define seed 23333

const int Mo=(int)1e9+9;

using namespace std;
string C1,C2;
int P(char c)
{
	 if (c<='Z') return c-'A';
	 return c-'a'+26;
}
int power(int x,int y)
{
	 int sum=1;
	 for (;y;y>>=1)
	 {
	 	 if (y&1) sum=1ll*sum*x%Mo;
	 	 x=1ll*x*x%Mo;
	 }
	 return sum;
}
int i,j,n,g[N*3][N],f[N][N],sum[N],col[N],fac[N],inv[N];
void ins(int x)
{
	  int i;
	 for (i=0;i<=x;++i)
	   (sum[i]+=1ll*f[x][i]*fac[n-x-1]%Mo)%=Mo,
	   (g[col[x]][i]+=1ll*f[x][i]*fac[n-x-1]%Mo)%=Mo;
}
class ColorfulBuilding{
public:
int count(vector<string> a,vector<string> b,int L)
{ 
      fac[0]=1;
      for (i=1;i<N;++i) fac[i]=1ll*fac[i-1]*i%Mo;
      inv[N-1]=power(fac[N-1],Mo-2);
      for (i=N-2;i>=0;--i) inv[i]=1ll*inv[i+1]*(i+1)%Mo;
      for (i=0;i<a.size();++i) C1+=a[i];
      for (i=0;i<b.size();++i) C2+=b[i];
      n=C1.size();	
      for (i=n;i;--i) C1[i]=C1[i-1],C2[i]=C2[i-1];
      C1[0]=C2[0]='0';
      f[0][0]=1;
      col[0]=3000;
      for (i=1;i<=n;++i) col[i]=P(C1[i])*52+P(C2[i]);
      ins(0);
      for (i=1;i<=n;++i)
      {
      	 for (j=1;j<=i;++j)
      	 {
      	 	f[i][j]=sum[j-1];
      	 	f[i][j]=(f[i][j]-g[col[i]][j-1]+Mo)%Mo;
      	 	f[i][j]=(f[i][j]+g[col[i]][j])%Mo;
      	 	f[i][j]=1ll*f[i][j]*inv[n-i]%Mo;
      	 }
      	  if (i!=n) 
      	  ins(i);
      }
      return f[n][L];
      //printf("%d\n",f[n][L]);
}
};
