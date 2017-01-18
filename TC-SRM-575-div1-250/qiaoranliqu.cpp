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
int i,j,m,n,p;
long long k;
class TheNumberGameDivOne{
	public:
		string find(long long n)
		{
				if (n&1) return "Brus"; //通过打表可以得到,若k不是2^{奇数次},则"John"胜,否则另一个人胜 
				for (k=2;k<=n;k*=4)
				if (n==k) return "Brus";
				return "John";
		}
};

