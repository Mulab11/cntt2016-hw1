#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
inline bool cmp(int a,int b)
{
		return a>b;
}
int i,j,m,n,p,k,ans,A[N];
class TomekPhone{
	public:
		int minKeystrokes(vector <int> f, vector <int> keySizes)
		{
				n=f.size(); m=keySizes.size();
				for (i=0;i<m;++i)
				  for (j=1;j<=keySizes[i];++j) A[++A[0]]=j; //把每个位置都塞进set里 
				sort(A+1,A+A[0]+1);
				if (n>A[0]) return -1;
				sort(f.begin(),f.end(),cmp);
				for (i=0;i<n;++i) //把大的尽量往小的地方塞 
				  ans+=f[i]*A[i+1];
				return ans;
		}
};
