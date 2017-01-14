#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;

class TheDivisionGame
{
	public:
	int sg[1000005],num[1000005];
	int cnt[32];
	LL countWinningIntervals(int L,int R)
	{
		//It is a simple Nim-game and sg(x) is the total power of its prime factors.
		LL ans=(LL)(R-L+2)*(R-L+1)/2;//We add all possible intervals at first.
		for(int i=L;i<=R;i++)
			num[i-L]=i;
		//For each prime that not exceed sqrt(R), we check all numbers in range[L,R] and count the power of d.
		for(int d=2;d<=32000;d++)
			for(int i=((L-1)/d+1)*d;i<=R;i+=d)
				while(num[i-L]%d==0)
					num[i-L]/=d,sg[i-L]++;
		for(int i=L;i<=R;i++)//Some numbers have prime factors greater than sqrt(R).
			if(num[i-L]>1)sg[i-L]++;
		int sum=0;
		cnt[0]=1;
		for(int i=L;i<=R;i++)
		{
			sum^=sg[i-L];
			//There are some intervals with xor-sum equal to zero, we can subtract them from the answer.
			ans-=cnt[sum];
			cnt[sum]++;
		}
		return ans;
	}
};

