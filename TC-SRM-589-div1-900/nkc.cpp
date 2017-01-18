#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 310
using namespace std;
struct FlippingBitsDiv1
{
	int A[N],B[N];
	int f[N][2],num[1<<17];
	int tot0[N],tot1[N];
	int getmin(vector <string> S, int M)
	{
		string s="";
		int i,j,k,n;
		for(i=0;i<S.size();i++)
		s+=S[i];
		n=s.size();
		int T=n/M,tmp,ans=1e9,now;
		if(M<T)//块比较小，枚举块的状态 
		{
			for(i=0;i<n;i+=M)
			{
				for(j=0;j<M&&i+j<n;j++)
				A[i/M+1]+=(s[i+j]-48)*(1<<(M-j-1));
			}
			for(i=0;i<(1<<M);i++)
			for(j=0;j<M;j++)
			if(i&(1<<j)) num[i]++;//预处理每个数有多少个1 
			for(k=0;k<(1<<M);k++)
			{
				now=0;
				if(n%M!=0)//最后一块特殊处理 
				{
					tmp=A[T+1]^k;
					for(i=1;i<=n%M;i++)
					if(tmp&(1<<(M-i))) now++;
				}
				f[T+1][0]=0;
				f[T+1][1]=1e9;
				for(i=T;i>=1;i--)//DP 
				{
					B[i]=A[i]^k;
					f[i][0]=min(f[i+1][0]+num[B[i]],f[i+1][1]+1+num[B[i]]);
					f[i][1]=min(f[i+1][0]+1+M-num[B[i]],f[i+1][1]+M-num[B[i]]);
				}
				ans=min(ans,now+min(f[1][0],f[1][1]));
			}
			return ans;
		}
		else//块的个数较少，枚举每块进不进行2操作 
		{
			for(k=0;k<(1<<T);k++)
			{
				now=0; 
				int sit=0;//用这个变量表示这块取不取反 
				memset(tot0,0,sizeof(tot0));
				memset(tot1,0,sizeof(tot1));
				for(i=T;i>=1;i--)
				{
					if(k&(1<<(i-1)))
					{
						now++;
						sit^=1;
					}
					if(sit)
					{
						for(j=0;j<M;j++)
						{
							if(s[(i-1)*M+j]^49) tot1[j]++;
							else tot0[j]++;
						}
					}
					else
					{
						for(j=0;j<M;j++)
						{
							if(s[(i-1)*M+j]^48) tot1[j]++;
							else tot0[j]++;
						}
					}
				}
				//统计出每位0和1的个数，贪心决定这位应该是0还是1 
				for(i=0;i<n%M;i++)
				{
					if(s[T*M+i]^48) tot1[i]++;
					else tot0[i]++;
				}
				for(i=0;i<M;i++)
				now+=min(tot0[i],tot1[i]);
				ans=min(ans,now);
			}
			return ans;
		}
	}
};