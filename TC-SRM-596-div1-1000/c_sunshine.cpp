#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
class SparseFactorial
{
	public:
	vector<LL> A,B,temp;
	int cnt[1000005];
	
	void mult(vector<LL> &a,vector<LL> &b,vector<LL> &c)//We use the chinese remainder theorem to merge two divisors.
	{
		temp.clear();
		int x=a.size(),y=b.size();//x and y are coprime.
		for(int i=0;i<x*y;i++)
			//A_xy[i]=max(A_x[i%x],A_y[i%y])
			temp.push_back(max(a[i%x],b[i%y]));
		c=temp;
	}
	
	void getA(int m,int p,int r)
	{
		//Get A_m[], and m=p^r
		A.clear();
		for(int i=0;i<m;i++)
			A.push_back((1LL<<60)-1);
		memset(cnt,0,m<<2);
		//We can prove that p*r different k is enough.
		for(int k=0;k<p*r;k++)
		{
			LL k2=(LL)k*k;
			LL dm=k2%m;
			LL dp=dm%p;
			for(int i=dp;i<m;i+=p)//update all t satisfying p|(t-k^2) in residue system.
				if(cnt[i]<r)
				{
					LL s=(i-dm+m)%m;
					//Update the occurence number of p.
					if(s)
						while(s%p==0)
							s/=p,cnt[i]++;
					else
						cnt[i]+=r;
					//The power of p is enough to satisfy m|f(n).
					if(cnt[i]>=r)
						A[i]=k2+1;
				}
		}
	}
	
	LL getCount(LL lo,LL hi,LL divisor)
	{
		LL m=divisor;
		A.clear();B.clear();
		B.push_back(0);
		//We are going to determine the array A[0..m-1] that m|F(n) if and only if n>=A[n mod m].
		//m must be the product of some (p^r)s, we can do each m=p^r first and merge them.
		for(int i=2;i<=m;i++)
			if(m%i==0)
			{
				LL p=i,r=0,t=1;
				while(m%p==0)
					t*=p,m/=p,r++;
				getA(t,p,r);
				mult(A,B,B);
			}
		A=B;
		m=divisor;
		LL ans=0;
		LL l,r;
		for(int i=0;i<m;i++)//Enumerate all remainders divided by m and count the numbers.
		{
			if(A[i]>hi)continue;
			l=max(A[i]-1,lo-1);
			r=hi;
			ans+=(r-i+m)/m-(l-i+m)/m;
		}
		return ans;
	}
};

