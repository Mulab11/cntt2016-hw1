#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class BigFatInteger{
	static const int maxn=100;
	int num[maxn],tot;
	
	public:
		int minOperations(int A, int B){
			tot=0;
			for (int i=2;i*i<=A;++i) if (A%i==0){
				num[tot]=1;
				A/=i;
				while(A%i==0){
					num[tot]++;
					A/=i;
				}
				++tot;
			}
			if (A>1) num[tot++]=1;
			int ret=0;
			for (int i=0;i<tot;++i){
				num[i]*=B;
				int now=1,tmp=0;
				while(now<num[i]){
					now<<=1;
					++tmp;
				}
				if (tmp>ret) ret=tmp;
			}
			return ret+tot;
		}
};
