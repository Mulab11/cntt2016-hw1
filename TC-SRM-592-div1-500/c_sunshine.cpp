#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int M=1000000007;
typedef long long LL;

inline void up(int &x,const int &y)
{x=(x+y)%M;}

class LittleElephantAndPermutationDiv1
{
	public:
	int f[55][55][2505];
	int getNumber(int N,int K)
	{
		int n=N;
		int sum=n*n,t,ans;
		f[0][0][0]=1;
		//f[i][j][k]: We have filled numbers 1~i in, and there are j positions filled both in A and B, the current sum of max(A_i,B_i) is k.
		for(int i=0;i<n;i++)
			for(int j=0;j<=i;j++)
				for(int k=0;k<=sum;k++)
					if((t=f[i][j][k])!=0)
					{
						//Two "i"s are filled in the same position.
						up(f[i+1][j+1][k+i+1],(LL)t*(n-i-i+j)%M);
						//One of two is filled in a half-filled position, and another in a empty postion.
						if(j<i)up(f[i+1][j+1][k+i+1],(LL)t*(i-j)*(n-i-i+j)*2%M);
						//Two "i"s are filled in positions half-filled.
						if(j<i)up(f[i+1][j+2][k+i+i+2],(LL)t*(i-j)*(i-j)%M);
						//Two "i"s are filled in empty positions.
						if(n-i-i+j>=2)up(f[i+1][j][k],(LL)t*(n-i-i+j)*(n-i-i+j-1)%M);
						//Notice that we count the value in a position if and only if it is totally filled,
						//because we fill in numbers in increasing order.
					}
		ans=0;
		for(int k=K;k<=sum;k++)//Count the answer.
			up(ans,f[n][n][k]);
		return ans;
	}
};

