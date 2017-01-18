#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair

#define N 55
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
class IncrementAndDoubling{
public:
int getMin(vector<int> v)
{
       int i,j; int Ans=0,B=0;
       for (i=0;i<(int)v.size();++i)
       {
       	      int S=0;
       	      for (j=v[i];j;j>>=1,++S) if (j&1) ++Ans;
       	      B=max(B,S-1);
       }
       return Ans+B;
	   return Ans;
}
};

