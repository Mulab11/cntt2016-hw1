#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
const int M=1234567891;
typedef LL MT[123][123];
class TheBrickTowerHardDivOne
{
	public:
	
	int C,K,N;
	LL H;
	
	int col[8];
	int id[1<<8],tot;
	int way4[1<<8],cs4[1<<8];
	int fc[5555],fi[5555];
	
	MT A,B,X;
	
	int pow(int a,int b)
	{
		int s=1;
		for(;b;b>>=1,a=(LL)a*a%M)
			if(b&1)s=(LL)s*a%M;
		return s;
	}
	
	int pick(int n,int k)
	{
		if(k<0||k>n)return 0;
		return (LL)fc[n]*fi[n-k]%M;
	}
	
	int gets(int *x)//get the label of the state.
	{
		int c[4],t=0;
		for(int i=0;i<4;i++)
		{
			c[i]=-1;
			for(int j=0;j<i;j++)
				if(x[j]==x[i]){c[i]=c[j];break;}
			if(c[i]==-1)c[i]=t++;
		}
		t=0;
		for(int i=0;i<4;i++)
			t=t<<2|c[i];
		return t;
	}
	
	void dfs4(int x,int cnt)//cnt means the number of occured colors.
	{
		if(x==4)
		{
			id[gets(col)]=tot;
			way4[tot]=pick(C,cnt);//the number of ways to choose the used cnt colors.
			//cs4 is the number of adjacent cells pairs that share the same color.
			for(int i=0;i<4;i++)
				cs4[tot]+=col[i]==col[i+1&3];
			tot++;
			return;
		}
		for(int i=0;i<=cnt;i++)
		{
			col[x]=i;
			dfs4(x+1,cnt+(i==cnt));
		}
	}
	
	void dfs8(int x,int cnt)
	{
		if(x==8)
		{
			int nc=0,w,cs;
			for(int i=4;i<8;i++)
			{
				int k=0;
				for(int j=0;j<i;j++)
					if(col[j]==col[i]){k=1;break;}
				if(!k)nc++;
			}
			w=pick(C-cnt+nc,nc);
			cs=0;//Count the number of NEW adjacent concolorous cells pairs.
			for(int i=0;i<4;i++)
			{
				cs+=col[i+4]==col[(i+1&3)+4];
				cs+=col[i]==col[i+4];
			}
			int fr=id[gets(col)],to=id[gets(col+4)];//Find the labels of first state and second state.
			//Update the transform matrix.
			for(int i=0;i+cs<=K;i++)	
				(X[i*tot+fr][(i+cs)*tot+to]+=w)%=M;
			return;
		}
		for(int i=0;i<=cnt;i++)
		{
			col[x]=i;
			dfs8(x+1,cnt+(i==cnt));
		}
	}
	
	LL temp[123][123];
	
	void mult(MT &a,MT &b,MT &c)
	{
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
			{
				temp[i][j]=0;
				for(int k=0;k<N;k++)
					temp[i][j]=(temp[i][j]+(LL)a[i][k]*b[k][j])%M;
			}
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				c[i][j]=temp[i][j];
	}
	
	MT t1;
	
	void MTpow(LL p)
	{
		if(p==1)
		{
			for(int i=0;i<N;i++)
				for(int j=0;j<N;j++)
				{
					A[i][j]=i==j;
					B[i][j]=X[i][j]; 
				}
			return;
		}
		MTpow(p>>1);
		mult(A,B,t1);
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				(A[i][j]+=t1[i][j])%=M;
		mult(B,B,B);
		if(p&1)
		{
			mult(B,X,B);
			mult(A,X,A);
			for(int i=0;i<N;i++)
				(A[i][i]+=1)%=M;
		}
	}
	
	int V[123];
	
	int find(int C, int K, long long H)
	{
		this->C=C;this->K=K;this->H=H;
		//Calculate factorial and inverse factorial.
		for(int i=fc[0]=1;i<=5000;i++)fc[i]=(LL)fc[i-1]*i%M;
		fi[5000]=pow(fc[5000],M-2);
		for(int i=5000;i;i--)fi[i-1]=(LL)fi[i]*i%M;
		dfs4(0,0);//get all essentially different states.
		dfs8(0,0);//get the transform.
		N=(K+1)*tot;
		MTpow(H);//use matrix fast exponentiation to optimize it.
		int ans=0;
		for(int i=0;i<tot;i++)
			V[tot*cs4[i]+i]=way4[i];
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				ans=(ans+(LL)V[i]*A[i][j])%M;
		return ans;
	}
};

