#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 55
#define M 16
#define seed 23333
#define Mo 998244353

using namespace std;
const int inf=(int)1e9;
int i,j,m,n,p,k,f[N][1<<M],open[N],End[N],T[N],fox[N],k1,bit,vis[N],ans;
struct Node{
	int ed,before,cost;
}s[N*N]; 

void add(int x,int y,int w)
{
	  s[++k1].ed=y; s[k1].before=fox[x]; fox[x]=k1; s[k1].cost=w;
}

class TravellingPurchasingMan{
	 public:
	 	int maxStores(int nc,vector<string> AA,vector<string> BB)
	 	{
	 		      n=nc; m=AA.size();
	 		      for (i=0;i<m;++i)
	 		      {
	 		      	   AA[i]+=' ';
	 		      	   int L=0,s=0;
	 		      	   while (AA[i][L]!=' ') s=s*10+AA[i][L]-'0',++L;
					   open[i]=s;
					   s=0; ++L;
					   while (AA[i][L]!=' ') s=s*10+AA[i][L]-'0',++L;
					   End[i]=s; 
					   s=0; ++L;
					   while (AA[i][L]!=' ') s=s*10+AA[i][L]-'0',++L;
					   T[i]=s; 
	 		      }
	 		      for (i=0;i<(int)BB.size();++i)
	 		      {
	 		      	      BB[i]+=' ';
	 		      	      int L=0,s=0,t=0,w=0;
	 		      	      while (BB[i][L]!=' ') s=s*10+BB[i][L]-'0',++L;
	 		      	      ++L;
	 		      	      while (BB[i][L]!=' ') t=t*10+BB[i][L]-'0',++L;
	 		      	      ++L;
	 		      	      while (BB[i][L]!=' ') w=w*10+BB[i][L]-'0',++L;
	 		      	      add(s,t,w); add(t,s,w);
	 		      }
	 		      memset(f,60,sizeof(f));
	 		      f[n-1][0]=0;
	 		      for(bit=0;bit<(1<<m);++bit) //设f_{i,S}为已经逛了{S}这些点,现在停在i的方案.然后枚举下一个点转移即可. 
	 		      { 
	 		      	   memset(vis,0,sizeof(vis));
	 		      	   for (i=0;i<n;++i) //对于每层中的点,先做一次dij来同层转移. 
	 		      	   {
	 		      	   	    for (j=0,k=-1;j<n;++j) if (!vis[j]&&(k==-1||f[j][bit]<f[k][bit])) k=j;
	 		      	   	    vis[k]=1;
	 		      	   	    for (j=fox[k];j;j=s[j].before)
	 		      	   	     f[s[j].ed][bit]=min(f[s[j].ed][bit],f[k][bit]+s[j].cost);
	 		      	   }
	 		      	   for (i=0;i<m;++i)
	 		      	     if (f[i][bit]<=End[i])
							  f[i][bit|(1<<i)]=min(f[i][bit|(1<<i)],max(f[i][bit],open[i])+T[i]);
	 		      }
	 		      for (i=0;i<(1<<m);++i)
	 		      {
	 		      	   int cnt=0;
	 		      	   for (j=0;j<m;++j) if (i&(1<<j)) ++cnt;
	 		      	   for (j=0;j<n;++j) if (f[j][i]<inf) ans=max(ans,cnt);
				  }
				  return ans;
	 	}
}E;
int main()
{
	  vector<string> A,B;
	  A.push_back("1 10 10"),A.push_back("1 55 30"),A.push_back("10 50 100");
      B.push_back("1 2 10");
      printf("%d\n",E.maxStores(3,A,B));
}

