#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<string>
#include<vector>

#define N 15
#define M 105
#define Mo 1000000007

#define mk make_pair
#define fi first
#define se second

using namespace std;

long long cost1,cost2,cost0,m,maxmoves,cost[3][3],Cost[3][3];
int n,i,j,ID[N][N],tot;

char s[N],c[N];

int mA[N],mB[N],A[M],B[M][M];

pair<int,int> P[M];

void jia(int &x,int y) { x+=y; if (x>=Mo) x-=Mo; }

void cheng()
{
   int C[M]={0},k,j;
   for (k=1;k<=tot;++k)
     for (j=1;j<=tot;++j)
       jia(C[j],1ll*A[k]*B[k][j]%Mo);
   memcpy(A,C,sizeof(C));
}
void Cheng()
{
	int C[M][M]={0},i,k,j;
	for (k=1;k<=tot;++k)
	  for (i=1;i<=tot;++i)
	    for (j=1;j<=tot;++j)
	       jia(C[i][j],1ll*B[i][k]*B[k][j]%Mo);
	 memcpy(B,C,sizeof(C));
}
void Power(int y)
{
	for (;y;y>>=1,Cheng()) if (y&1) cheng();
}
class ConversionMachine{
   public:
	int countAll(string word1, string word2, vector <int> costs, int maxCost)
{
   n=word1.length();
   for (i=1;i<=n;++i) s[i]=word1[i-1],c[i]=word2[i-1];
   for (i=1;i<=n;++i) mA[i]=s[i]-'a',mB[i]=c[i]-'a';
   cost0=costs[0]; cost1=costs[1]; cost2=costs[2]; m=maxCost;
   long long str=0;   
   cost[0][1]=cost0; cost[0][2]=cost0+cost1; 
   cost[1][2]=cost1; cost[1][0]=cost1+cost2; 
   cost[2][0]=cost2; cost[2][1]=cost2+cost0;
   Cost[0][1]=1; Cost[0][2]=2;
   Cost[1][2]=1; Cost[1][0]=2;
   Cost[2][0]=1; Cost[2][1]=2;
   for (i=1;i<=n;++i)	//计算一开始到达终点的方案 
   {
			str+=cost[mA[i]][mB[i]];
			maxmoves+=Cost[mA[i]][mB[i]];
  }
   if (str>m) return 0;
   maxmoves+=(m-str)/(cost0+cost1+cost2)*3; //这里就是一共可以走的步数. 
   for (i=0;i<=n;++i) for (j=0;i+j<=n;++j) 	 ID[i][j]=++tot,P[tot]=mk(i,j);
   int C[3]={0};
   for (i=1;i<=n;++i) C[(mA[i]-mB[i]+3)%3]++;
   ++tot;
   A[ID[C[0]][C[1]]]=1; A[tot]=A[ID[n][0]];
   B[tot][tot]=1;
   for (i=1;i<tot;++i) //构建矩乘的图 
   {
   		int sx=P[i].fi,sy=P[i].se,sz=n-sx-sy;
   		if (sx>0) B[i][ID[sx-1][sy+1]]=sx;
   		if (sy>0) B[i][ID[sx][sy-1]]=sy;
   		if (sz>0)
   		{
   		      B[i][ID[sx+1][sy]]=sz;
   		      if (sx+1==n) B[i][tot]=sz;
		}
   }
   Power(maxmoves); //矩乘 
   return A[tot];
}
};
