#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 51
using namespace std;
struct XorCards
{
	int jd[N][N],b[N];
	bool hav[N];
	int a[N],A,n;
	int add()//线性基求方程的解数 
	{
		int i,j,k;
		for(i=n-1;i>=0;i--)
		if(a[i])
		{
			if(!hav[i])
			{
				hav[i]=true;
				for(j=i;j>=0;j--)
				jd[i][j]=a[j];
				b[i]=A;
				return i;
			}
			else
			{
				for(j=i;j>=0;j--)
				a[j]^=jd[i][j];
				A^=b[i];
			}
		}
		if(A==1) return -1;//矛盾返回-1 
		return 707;//没有成功加入，返回707 
	}
	void back(int x)//删除一个方程 
	{
		memset(jd[x],0,sizeof(jd[x]));
		b[x]=0;
		hav[x]=false;
	}
	long long numberOfWays(vector<long long> number, long long limit)
	{
		n=number.size();
		int i,j;
		long long ans=0,re=n;
		for(i=50;i>=0;i--)//按位数从高到低加入可以让时间复杂度变为n^2logINF 
		{
			memset(a,0,sizeof(a));
			for(j=n-1;j>=0;j--)
			if(number[j]&(1LL<<i)) a[j]=1;
			A=!!(limit&(1LL<<i));
			if(!A)
			{
				j=add();
				if(j==-1) return ans;
				if(j!=707) re--;
			}
			else
			{
				A=0;
				j=add();//先算答案在这位开始不同，小于m的 
				if(j!=-1)
				{
					if(j!=707)
					{
						re--;
						ans+=(1LL<<re);
						re++;
						back(j);
					}
					else ans+=(1LL<<re);
				}
				//然后正常加入线性基 
				memset(a,0,sizeof(a));
				for(j=n-1;j>=0;j--)
				if(number[j]&(1LL<<i)) a[j]=1;
				A=1;
				j=add();
				if(j==-1) return ans;
				if(j!=707) re--;
			}
		}
		ans+=(1LL<<re);
		return ans;
	}
};