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
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,f[N][N][3][3],ans[N],Ans[N],num[N],low[N];
bool check(int x) //计算某个前缀是否合法 
{
		int nex=n-x-1,i,j,k,l;
		memset(f,0,sizeof(f));
		f[0][0][0][0]=1;  
		for (i=0;i<n-1;++i)  
		{
			    for (j=max(0,i-nex);j<=min(i,x);++j)
			  {
			  		if (j<x&&(ans[x-j-1]==-1||num[i+1]==ans[x-j-1]))
			  	   {
			  	   	     for (k=0;k<3;++k)
			  	   	     {
			  	   	     	  if (num[i+1]<low[x-j-1])
							  {
							  	   for (l=0;l<3;++l) 
							  	   	   f[i+1][j+1][1][k]|=f[i][j][l][k];
							  }
							  else if (num[i+1]==low[x-j-1])
							  {
							  		for (l=0;l<3;++l)
							  		   f[i+1][j+1][l][k]|=f[i][j][l][k];
							  }
							  else 
							  {
							  	    for (l=0;l<3;++l)
							  		   f[i+1][j+1][2][k]|=f[i][j][l][k];
							  }
			  	   		 }
			  	   }
			  	    if (i-j<nex&&(ans[x+i-j+1]==-1||ans[x+i-j+1]==num[i+1]))
			  	    {
			  	    	      for (k=0;k<3;++k)
			  	    	      {
			  	    	      		for (l=1;l<3;++l) f[i+1][j][k][l]|=f[i][j][k][l];
			  	    	      		if (num[i+1]<low[x+(i-j)+1])
										  f[i+1][j][k][1]|=f[i][j][k][0];
									else if (num[i+1]==low[x+(i-j)+1])
										  f[i+1][j][k][0]|=f[i][j][k][0];
									else 
										  f[i+1][j][k][2]|=f[i][j][k][0];
			  	    	      }
			  	    }
			  }
		}
		if (f[n-1][x][2][0]||f[n-1][x][2][1]||f[n-1][x][2][2]) return 1;
		if (num[0]<low[x])
		{
				return 0;
		}
		if (num[0]==low[x])
		{
				if (f[n-1][x][0][2]||f[n-1][x][0][0]) return 1;
				return 0;
		}
		if (f[n-1][x][0][0]||f[n-1][x][0][1]||f[n-1][x][0][2]) return 1;
		return 0;
}
class LeftRightDigitsGame2{
	public:
		string minNumber(string digits, string lowerBound)
		{
				n=digits.size();
				for (i=0;i<n;++i) num[i]=digits[i]-'0';
				for (i=0;i<n;++i) low[i]=lowerBound[i]-'0';
				if (n==1)
				{
					    string s;
						if (num[0]>=low[0]) s+=num[0]+'0';
						return s;
				}
				for (i=0;i<n;++i) Ans[i]=10; 
				for (i=0;i<n;++i) //枚举第一个数放的位置 
				{
					   memset(ans,-1,sizeof(ans));
					   ans[i]=digits[0]-'0';
					   for (j=0;j<n;++j) //开始逐位确定 
					   	if (i!=j)
					   {
					   		for (k=0;k<10;++k)
					   		{
					   				ans[j]=k;
					   				if (check(i)) break;
					   		}
					   		if (k==10) break;
					   }
					   if (j<n) continue;
					   for (k=0;k<n;++k) if (ans[k]!=Ans[k]) break;
					   if (ans[k]<Ans[k])
					   for (k=0;k<n;++k) Ans[k]=ans[k];
				}
				string s="";
				if (Ans[0]>9) return s;
				for (i=0;i<n;++i) s+=Ans[i]+'0';
				return s; 
		}
}FFT;

int main()
{
	 cout<<FFT.minNumber("09","77");
}
