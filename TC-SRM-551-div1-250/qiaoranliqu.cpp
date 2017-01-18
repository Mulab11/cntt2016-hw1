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
#define pb push_back

#define N 55
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,ans,maxSwaps;
vector<int>v;
int check()
{
	  int i,j;
	  for (i=0;i+(int)v.size()<=n;++i) //枚举不动点 
	  {
	  		int sum=0;
	  		for (j=0;j<(int)v.size();++j) sum+=abs(i+j-v[j]); //其他点都交换过去 
			if (sum<=maxSwaps) return 1; 
	  }
	  return 0;
}
class ColorfulChocolates{
	public:
		int maximumSpread(string chocolates, int maxSwaps)
		{
				::maxSwaps=maxSwaps;
				ans=1; 
				n=chocolates.size();
				for (i=0;i<n;++i) //枚举成为答案的两个端点 
					for (j=i+1;j<n;++j)
						if (chocolates[i]==chocolates[j]) 
						{
								v.clear();
								for (k=i;k<=j;++k) if (chocolates[k]==chocolates[i])
								v.pb(k);
								if (check()) ans=max(ans,(int)v.size());
						}
				return ans;
		}
}FFT;
int main()
{
	 FFT.maximumSpread("ABCDCBC",1);
}
