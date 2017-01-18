#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
struct JumpFurther
{
	int furthest(int N, int badStep)
	{
		int t=sqrt(badStep*2);
		if(t<=N&&t*(t+1)/2==badStep) return N*(N+1)/2-1;
		else return N*(N+1)/2;
	}
};