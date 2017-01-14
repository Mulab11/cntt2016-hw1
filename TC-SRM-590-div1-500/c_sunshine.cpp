#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;

class XorCards
{
	public:
	int n,fv,P[55];
	LL X[55];
	
	LL firstBit(LL x)
	{return x==1?0:firstBit(x>>1)+1;}
	
	void Gauss()
	{
		for(int k=49,i=0,j;k>=0&&i<n;k--)
		{
			for(j=i;j<n;j++)
				if(X[j]>>k&1)
				{
					swap(X[i],X[j]);
					break;
				}
			if(X[i]>>k&1)
			{
				for(j=i+1;j<n;j++)
					if(X[j]>>k&1)
						X[j]^=X[i];
				i++;
			}
		}
		fv=0;
		while(n&&X[n-1]==0)
			n--,fv++;
		for(int i=0;i<n;i++)//P[i]: X[i] is a base vector at P[i]-th bit
			P[i]=firstBit(X[i]);
	}
	
	LL numberOfWays(vector<LL> number,LL limit)
	{
		n=number.size();
		for(int i=0;i<n;i++)X[i]=number[i];
		//(a,b) and (a xor b,b) have the same vector space, so we can use Gauss elimination to deal with the numbers
		Gauss();
		LL ans=0,now=0;
		int flag=0;
		//we determine all bits from 50th bit to 0th bit 
		for(int i=0,k=50;i<n;i++)
		{
			flag=0;
			for(;k>P[i];k--)
				if((now>>k&1)!=(limit>>k&1))
				{
					if(now>>k&1)flag=-1;
					else flag=1;
					break;
				}
			if(flag)//if the limit and the current number do not match at some bit without a base vector
			{
				//if the current number is the less one we can arrange the unused numbers freely
				if(flag==1)ans+=1LL<<n-i;
				//Otherwise there is no way to arrange the unused numbers satisfying the limit
				break;
			}
			if(limit>>P[i]&1)//limit is 1 at this bit
			{
				//if we do pick or not pick this number to make this bit 0,
				//we can arrange the unused numbers freely
				ans+=1LL<<n-i-1;
				//Otherwise the limit and the current number match perfectly at P[i]-th higher bits.
				if((now>>P[i]&1)==0)
					now^=X[i];
			}
			else//The limit is 0 at this bit so we have only one way to deal with this number
			{
				if(now>>P[i]&1)
					now^=X[i];
			}
		}
		//In some condition, we only count the numbers that are strictly less than limit over P[n-1]-th bit
		//Do not forget to check the final number 
		if(!flag&&now<=limit)ans++;
		ans<<=fv;//Ans should times 2^fv, while fv is the number of free element
		return ans;
	}
};

