#include<cstdio>
#include<algorithm>
#include<cmath>
int tot=0,cnt[111]={};
void fact(int a)
{
	for(int i=2;i<=a;i++)
		if(a%i==0)
		{
			tot++;
			while(a%i==0)
				a/=i,cnt[tot]++;
		}
}
int getnum(int codeforces)
{
	int temp=0,ttt=1;
	while(codeforces>ttt)
		ttt*=2,temp++;
	return temp;
}
class BigFatInteger
{
public:
	int minOperations(int A, int B)
	{
		int codeforces=0;
		fact(A);
		codeforces+=tot;
		int maxx=1;
		for(int i=1;i<=tot;i++)
			if(maxx<cnt[i])
				maxx=cnt[i];
		codeforces+=(int)(log2(1.0*maxx)+log2(1.0*B)-0.00000001+1);
		return codeforces;
	}
};
