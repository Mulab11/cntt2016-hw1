#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class PyramidSequences{
	int gcd(int a,int b){
		return (b==0)?a:gcd(b,a%b);
	}
	public:
		long long distinctPairs(int N, int M){
			N--,M--;
			int g=gcd(N,M);
//			cout<<g<<endl;
			long long ans=1ll*N/g*M/g*(g-1);
			return ans+((long long)(N/g+1)*(M/g+1)+1)/2;
		}
};
