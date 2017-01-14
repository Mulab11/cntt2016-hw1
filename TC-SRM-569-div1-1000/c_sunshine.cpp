#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int pr[]={0,0,2,3,2,5,3,7,2,3,5};
const int dv[]={0,0,1,1,2,1,1,1,3,2,1};
typedef long long LL;
typedef int mtx[20][20];
LL temp[20][20];
int M;

int pow(int a,int b)
{
	int s=1;
	for(;b;b>>=1,a=(LL)a*a%M)
		if(b&1)s=(LL)s*a%M;
	return s;
}

class MegaFactorial
{
	public:
	int N,K,P;
	int n;
	
	void init(mtx &a)//Identity matrix
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				a[i][j]=(i==j);
	}
	
	void cpy(mtx &a,mtx &b)//copy matrix
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				a[i][j]=b[i][j];
	}
	
	void mult(mtx &a,mtx &b,mtx &c)//matrix multiplication
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
			{
				temp[i][j]=0;
				for(int k=0;k<n;k++)
					temp[i][j]=(temp[i][j]+(LL)a[i][k]*b[k][j])%M;
			}
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				c[i][j]=temp[i][j];
	}
	
	mtx A[50],B[50],C[50],ans;
	int pp[50];
	
	int calc()//find the greastest k that P^k | N!K
	{
		int D=0,t=N;
		while(t)
		{
			t/=P;
			if(t)D++;
		}
		n=K+2;
		//Use matrix multiplication to accelerate the calculation.
		for(int i=0;i<=D;i++)
		{
			memset(A[i],0,sizeof(A[i]));
			for(int j=1;j<=K;j++)
				for(int k=j;k<=K;k++)
					A[i][j][k]++;
				A[i][K+1][K+1]++;
				for(int j=0;j<=K;j++)
					A[i][K+1][j]+=i;
		}
		//Determine B[i], and the numebr of different matrix "B"s is no more than O(log N).
		init(B[0]);
		for(int i=1;i<=D;i++)
		{
			cpy(B[i],B[i-1]);
			for(int j=1;j<P;j++)
			{
				mult(B[i],A[i-1],B[i]);
				mult(B[i],B[i-1],B[i]);
			}
		}
		for(int i=0;i<=D;i++)
			mult(B[i],A[i],C[i]);
		pp[0]=1;
		for(int i=1;i<=D;i++)
			pp[i]=pp[i-1]*P;
		init(ans);
		int tn=N;
		while(tn)
		{
			int i;
			for(i=D;;i--)
				if(pp[i]<=tn)break;
			tn-=pp[i];
			mult(ans,C[i],ans);
		}
		return ans[K+1][K];
	}
	
	int countTrailingZeros(int N,int K,int B)
	{
		//P is the least prime factor of B, and let k be the greatest number that P^k | N!K
		//The answer is floor(k/dv[B]) = (k - (k mod dv[B]) ) / dv[B]
		M=dv[B];P=pr[B];
		this->N=N,this->K=K;
		int t=calc();
		M=1000000009;
		int ans=(calc()-t+M)%M;
		ans=(LL)ans*pow(dv[B],M-2)%M;
		return ans;
	}
};

