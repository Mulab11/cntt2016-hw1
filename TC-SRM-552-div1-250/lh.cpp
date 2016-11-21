#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class FoxPaintingBalls{
	public:
		long long theMax(long long R, long long G, long long B, int N){
			if (N==1) return R+G+B;
			long long sum=1ll*N*(N+1)/2;
			if (N%3==1){
				long long tmp=sum/3;
				return min({R/tmp,G/tmp,B/tmp,(R+G+B)/(3*(sum/3)+1)});
			}
			else{
				long long tmp=sum/3;
				return min({R/tmp,G/tmp,B/tmp});
			}
		}
};

