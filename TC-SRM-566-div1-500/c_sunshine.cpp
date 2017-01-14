#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
const int M=1000000007;
const int N=355;

inline void up(int &x,const int &y){x+=y;if(x>=M)x-=M;}

class PenguinEmperor
{
	public:
	int n;
	int temp[N];
	int A[N],B[N],X[N],Q[N];
	
	void mult(int *a,int *b,int *c)
	{
		for(int i=0;i<n;i++)temp[i]=0;
		for(int i=0;i<n;i++)
			if(a[i])for(int j=0;j<n;j++)
				up(temp[(i+j)%n],(LL)a[i]*b[j]%M);
		for(int i=0;i<n;i++)c[i]=temp[i];
	}
	
	int countJourneys(int numCities,LL daysPassed)
	{
		//f[i][j] : The number of ways that the Percy will be at j-th city on i-th day.
		//f[i][j]->f[i+1][j +/- i mod n]
		//let g[i][j]=(j=i mod n)+(j=-i mod n)
		//f[i]=g[1]*g[2]*...*g[n]  '*' means convolution.
		//Notice that g[i]=g[i%n]
		//We can use fast exponentiation to optimize it.
		n=numCities;
		X[0]=A[0]=B[0]=1;
		for(int i=1;i<=n;i++)//Get g[1]*g[2]*...*g[n] and g[1]*g[2]*...*g[T mod n]
		{
			Q[i%n]=Q[n-i]=1;
			mult(Q,X,X);
			if(i==daysPassed%n)memcpy(B,X,sizeof(B));
			Q[i%n]=Q[n-i]=0;
		}
		for(LL b=daysPassed/n;b;b>>=1,mult(X,X,X))//fast exponentiation
			if(b&1)mult(A,X,A);
		mult(A,B,A);
		return A[0];//After T days he should be in city 0.
	}
};

