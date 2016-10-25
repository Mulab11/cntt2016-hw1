#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<iostream>

#define n 2305
#define N 3505

using namespace std;
const int inf=(int)1e9;
int C[N][N],i,j;
int f(int m,int n) //计算n个相同的小球放入m个不同篮子的方案数
{
	  return C[n+m-1][m-1];
}
const int Mo=555555555;
int ans;
class XorBoard{
public:
int count(int H,int W,int R,int C1,int S)
{
	     for (i=0;i<n;++i) //预处理组合数
	    {
		    C[i][0]=1;
			for (j=1;j<=i;++j) C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mo;
		}
		 for (i=0;i<=min(H,R);++i) //枚举行数
	     {
	     	    if ((R-i)&1) continue;
	     	    for (j=0;j<=min(W,C1);++j) //枚举列数
				 {
				        if ((C1-j)&1) continue; 
						if (i*W+j*H-2*i*j!=S) continue; //验证是否符合条件
						ans=(ans+1ll*C[H][i]*C[W][j]%Mo*f(H,(R-i)/2)%Mo*f(W,(C1-j)/2)%Mo)%Mo;
				 }
	    }
	    return ans;
}
};