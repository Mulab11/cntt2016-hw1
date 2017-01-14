#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class FlippingBitsDiv1
{
	public:
	string S,w;
	int B[305][2],f[305][2],Bn;
	int n,m,ans;
	
	int work()
	{
		n=S.size();
		if(m<(n+m-1)/m)//It is better to enumerate the cyclic string
		{
			for(int s=0;s<1<<m;s++)
			{
				w="";
				for(int i=0;i<n;i++)
					w+=(S[i]!=(s>>i%m&1)+'0')+'0';
				Bn=-1;
				//We can divide S into many sections of length M
				for(int i=0,c0=0,c1=0;i<=n;i++)//count the bits that need (not) to flip in each section
				{
					if(i%m==0||i==n)
					{
						Bn++;
						B[Bn][0]=c0;
						B[Bn][1]=c1;
						c0=c1=0;
					}
					if(i<n)
					{
						if(w[i]=='1')c1++;
						else c0++;
					}
				}
				f[0][0]=0;
				f[0][1]=0;
				//f[i][j]: the minimum flips to make first i bits rotating when the i-th bit is (not) flipped by operation 2
				//It is the number of breakpoints times that we will do operation 2
				for(int i=1;i<=Bn;i++)
				{
					f[i][0]=min(f[i-1][0],f[i-1][1]+1)+B[i][1];
					f[i][1]=min(f[i-1][0]+1,f[i-1][1])+B[i][0];
				}
				ans=min(ans,min(f[Bn][0],f[Bn][1]+1));
			}
		}
		else//It is better to enumerate the ways of operation 2
		{
			Bn=(n+m-1)/m;
			for(int s=0;s<1<<Bn;s++)
			{
				int t=0;
				w=S;
				for(int i=0;i<n;i++)
				{
					if(i%m==0)
						if(s>>i/m&1)t^=1;
					if(t)
						w[i]=w[i]^'0'^'1';
				}
				int sum=0;
				for(int i=0;i<Bn;i++)//count the number of times we use operation 2
					sum+=s>>i&1;
				for(int i=0;i<m;i++)
				{
					int c0=0,c1=0;
					//There are some groups that must be equal at last,
					//ans we should flip the minority equal bits into the others.
					for(int j=i;j<n;j+=m)
						if(w[j]=='0')c0++;
						else c1++;
					sum+=min(c0,c1);
				}
				ans=min(ans,sum);
			}
		}
		return ans;
	}
	
	int getmin(vector<string> S,int M)
	{
		this->m=M;ans=1000005;
		for(int i=0;i<S.size();i++)
			this->S+=S[i];
		//Since the length of S is at most 300, the time complexity O(2^sqrt(|S|)) will be suitable
		return work();
	}
};

