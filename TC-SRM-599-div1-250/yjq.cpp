#include<bits/stdc++.h>
#define MOD 2000000009 
using namespace std;const int MAXN=1010;int c[MAXN],cnt;typedef long long LL;void dividint(int n){cnt=0;for(int i=2;i*i<=n;i++)if(n%i==0){c[++cnt]=0;while(n%i==0){++c[cnt];n/=i;}}if(n>1)c[++cnt]=1;}class BigFatInteger{public:int minOperations(int A,int B){int maxv=0;dividint(A);for(int i=1;i<=cnt;++i)maxv=max(maxv,(int)(ceil(log2(c[i]*B))));return cnt+maxv;}};
