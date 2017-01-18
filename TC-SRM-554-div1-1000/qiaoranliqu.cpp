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

#define N 5005
#define M 200005
#define seed 23333
#define Mo 1234567891

using namespace std;
int i,j,m,n,p,k,bl[N][8],sum[N],P[N][6],tot,Q[N],Ax[N],lim,Max[N],col;
void dfs(int x,int y,int z)
{
		if (x==4) 
		{
			 if (Ax[0]==Ax[1]) ++sum[z];
			 if (Ax[0]==Ax[2]) ++sum[z];
			 if (Ax[1]==Ax[3]) ++sum[z];
			 if (Ax[2]==Ax[3]) ++sum[z];
			 if (sum[z]>k||y>col) return;
			 int i;
			 for (i=0;i<=k;++i) bl[z][i]=++tot; //给状态标号 
			 Q[++Q[0]]=z;
			 Max[z]=y;
		}
		else 
		{
			  Ax[x]=y;
			  dfs(x+1,y+1,(z<<2)+y);
			  int i;
			  for (i=0;i<y;++i) Ax[x]=i,dfs(x+1,y,(z<<2)+i); 
		}
}
#define L 130
int A[L],B[L][L];
int work()
{
		int vis[15],w=0,s=0,i;
		for (i=0;i<15;++i) vis[i]=-1;
		for (i=0;i<4;++i) 
		{
			if (vis[Ax[i]]==-1) vis[Ax[i]]=w++;
			s=(s<<2)+vis[Ax[i]];
		}
		return s;
}
void jia(int &x,int y)
{
		long long z=1ll*x+1ll*y;
		if (z>=Mo) z-=Mo;
		x=z;
}
void getall(int x,int y,int z)
{
		if (x==4) 
		{
			 int now=0;
			 if (Ax[0]==Ax[1]) ++now;
			 if (Ax[0]==Ax[2]) ++now;
			 if (Ax[1]==Ax[3]) ++now;
			 if (Ax[2]==Ax[3]) ++now;
			 int j;
			 for (j=0;j<4;++j) if (Ax[j]==((Q[i]>>(6-2*j))&3)) ++now;
			 if (now>k) return; //判断是否合法 
			 int ID=work(); //把后一层的标号还原出来 
			 for (j=0;j<=k;++j) 
			 	if (j+now<=k&&col>=Max[Q[i]])
			 	   jia(B[bl[Q[i]][j]][bl[ID][j+now]],P[col-Max[Q[i]]][y-Max[Q[i]]]);
			 if (B[1][0])
			     B[1][0]=0;
		}
		else 
		{
			  Ax[x]=y; //这里从上一层的最大标号开始标 
			  getall(x+1,y+1,(z<<1)+y);
			  int i;
			  for (i=0;i<y;++i) Ax[x]=i,getall(x+1,y,(z<<1)+i); 
		}
}
void cheng()
{
		int C[L]={0},j,k;
		for (k=1;k<=lim;++k)
		  for (j=1;j<=lim;++j)
		     jia(C[j],1ll*A[k]*B[k][j]%Mo);
		memcpy(A,C,sizeof(C));
}
void Cheng()
{
		int C[L][L]={0},i,j,k;
		for (k=1;k<=lim;++k)
			for (i=1;i<=lim;++i)
				for (j=1;j<=lim;++j)
				    jia(C[i][j],1ll*B[i][k]*B[k][j]%Mo);
		memcpy(B,C,sizeof(C)); 
}
void Power(long long y)
{
		for (;y;y>>=1)
		{
				if (y&1) cheng();
				Cheng();
		}
}
class TheBrickTowerHardDivOne{
	public:
		int find(int CC, int K, long long H)
		{
			  k=K; col=CC;
			  dfs(0,0,0); //搜出4个点的最小表示法
			P[0][0]=1;
			for (i=1;i<N;++i)  
				for (j=0;j<=4;++j)
					if (i>=j)
				{
					 P[i][j]=1;
					 for (k=1;k<=j;++k) P[i][j]=1ll*P[i][j]*(i-k+1)%Mo;
				}
			k=K;
			for (i=1;i<=Q[0];++i) //如果一个状态本身相邻的数量就超过上限的话就不计算 
			if (sum[Q[i]]<=k) A[bl[Q[i]][sum[Q[i]]]]=P[col][Max[Q[i]]];
			lim=tot+1;	B[lim][lim]=1;  
			for (i=1;i<=Q[0];++i)//处理矩阵的转移 
			{
				   for (j=0;j<=k;++j) B[bl[Q[i]][j]][lim]=1; 
				   getall(0,Max[Q[i]],0);
			}
			Power(H);
			return A[lim];
	    }
}FFT;
int main()
{
	 cout<<FFT.find(4,7,47);
}
