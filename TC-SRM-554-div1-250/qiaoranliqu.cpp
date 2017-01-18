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

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k;
class TheBrickTowerEasyDivOne
{
	public:
	int find(int redCount, int redHeight, int blueCount, int blueHeight)
	{
			int A=redCount,B=blueCount;
			if (A>B) swap(A,B); B=min(B,A+1);
			if (redHeight!=blueHeight) 
			{
				int ans=3*(A+1);
				ans-=2; 
				if (A==B) --ans; //判断(A,A+1)这个二元组是否存在 
				return ans;
			}
			else return A+B;
	}
};


