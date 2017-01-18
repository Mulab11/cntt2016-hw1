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
int i,j,m,n,p,k,A[2],ans;
class TheDevice{
	public:
		int minimumAdditional(vector <string> plates)
		{
				n=plates.size();
				m=plates[0].length();
				for (i=0;i<m;++i) //枚举每一位,从所有位置的情况中取需要最大的那种 
				{
						memset(A,0,sizeof(A));
						for (j=0;j<n;++j) A[plates[j][i]-'0']++;
						//通过01可以判断是不是and,通过11判断是不是or,所以需要2个1和1个0 
						ans=max(ans,max(0,1-A[0])+max(0,2-A[1])); 
				}
				return ans;
		}
};

