#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class JumpFurther{
	public:
	int furthest(int n, int m){
		int sum=0;
		for (int i=1;i<=n;++i){
			sum+=i;
			if (sum==m) return n*(n+1)/2-1;
		}
		return n*(n+1)/2;
	}
};