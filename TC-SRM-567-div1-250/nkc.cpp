#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
bool spc[80010];
struct TheSquareRootDilemma
{
	int countPairs(int N, int M)
	{
		int i,j;
		if(N>M) swap(N,M);
		for(i=2;i*i<=N;i++)
		for(j=1;j*i*i<=N;j++)
		spc[j*i*i]=true;//枚举可以当做根号下的数 
		int ans=0;
		for(i=1;i<=N;i++)
		if(!spc[i])
		ans+=(int)sqrt(N/i)*(int)sqrt(M/i);//计算答案 
		return ans;
	}
};