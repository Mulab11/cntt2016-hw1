#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
typedef int Matrix[80][80];
const int M=1000000007;

Matrix tb,temp;

int N;

inline void up(int &x,const int &y)
{x+=y;if(x>=M)x-=M;}

void mult(Matrix &a,Matrix &b,Matrix &c)
{
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			tb[i][j]=b[j][i];
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
		{
			temp[i][j]=0;
			for(int k=0;k<N;k++)
				up(temp[i][j],(LL)a[i][k]*tb[j][k]%M);
		}
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			c[i][j]=temp[i][j];
}

class ConversionMachine
{
	public:
	int n,suc,s1,s2;
	int I[15][15];
	Matrix A,X;
	int countAll(string word1,string word2,vector<int> costs,int maxCost)
	{
		//After we turn word1 to word2, we can and only can do some 3-cycles for each position.
		//So we can determine moves which the number of times to operate can not exceed.
		LL moves=0,left=maxCost;
		n=word1.size();
		for(int i=0;i<n;i++)
		{
			if((word2[i]-word1[i]+3)%3==1)s1++;
			else if((word2[i]-word1[i]+3)%3==2)s2++;
			while(word1[i]!=word2[i])
				left-=costs[word1[i]-'a'],word1[i]=word1[i]=='c'?'a':word1[i]+1;
		}
		if(left<0)return 0;
		moves+=s1+s2*2;
		moves+=3LL*(left/((LL)costs[0]+costs[1]+costs[2]));
		//Then we use f[k][i][j] to represent that state
		//where are i positions needing one operation and j positions needing two operations.
		N=0;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n;j++)
				if(i+j<=n)
					I[i][j]=N++;
		suc=N++;
		//Build the transform.
		for(int d1=0;d1<=n;d1++)
			for(int d2=0;d2<=n;d2++)
				if(d1+d2<=n)
				{
					//We can pick which kind of positions to operate.
					int d0=n-d1-d2;
					if(d0)up(X[I[d1][d2]][I[d1][d2+1]],d0);
					if(d1)up(X[I[d1][d2]][I[d1-1][d2]],d1);
					if(d2)up(X[I[d1][d2]][I[d1+1][d2-1]],d2);
				}
		//We add a new element into the vector to represent stopping.
		up(X[I[0][0]][suc],1);
		up(X[suc][suc],1);
		//Simply use matrix multiplication to accelerate it.
		for(int i=0;i<N;i++)
			A[i][i]=1;
		for(;moves;moves>>=1,mult(X,X,X))
			if(moves&1)mult(A,X,A);
		int ans=((LL)A[I[s1][s2]][I[0][0]]+A[I[s1][s2]][suc])%M;
		return ans;
	}
};

