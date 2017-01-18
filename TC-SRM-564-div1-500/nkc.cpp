#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
ll ans;
void get(int n,int k)
{
	if(k%2==1&&n>=k+1) ans+=(n-k)*2;
	ans+=(k-1)/2*2+1;
}
struct AlternateColors2
{
ll countWays(int n,int k)
{
	if(k%3==1&&n>=k+2) ans+=(ll)(n-k)*(n-k-1)/2;
	for(int i=0;i*3<k;i++) get(n-i*3,k-i*3);
	return ans;
}
};