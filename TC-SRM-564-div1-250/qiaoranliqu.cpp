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
int i,j,m,n,p,k;
class KnightCircuit2{
		public:
			int maxSize(int w, int h)
			{
					if (w==1||h==1) return 1;
					if (w==2) return (h-1)/2+1;
					if (h==2) return (w-1)/2+1;
					w-=2; h-=2;
					int down=3; int now=8;
					for (i=1;i<h;++i) //事实上是在计算w*h 
					{
						 if (i==1) now+=4; else now+=3;
						 ++down;
					}
					for (i=1;i<w;++i)
					{
						 if (i==1&&down==3) now+=4; else now+=down;
					}
					return now;
			}
};
	

