#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define x first
#define y second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

const int mod=1000000007;

int fac[1000010],inv[1000010];

int power(int x,int y) //x^y 
{
	int t=1;
	while (y)
	{
		if (y&1) t=ll(t)*x%mod;
		y>>=1;x=ll(x)*x%mod;
	}
	return t;
}

int C(int n,int m) //组合数
{
	return ll(fac[n])*inv[n-m]%mod*inv[m]%mod;
}

int calc(int R,int G,int B,int M)
{
	int ans=0,t=1;
	for (int i=0;i<=R;i++)
	{
		int g=G-i,b=B-i;
		if (g<0||b<0) break;
		if ((R-i+g-b)%2==0)
		{
			int x=(R-i+g-b)/2;
			int y=R-i-x;
			int z=M-x-y-2*i;
			if (x>=0&&y>=0&&x<=g&&y<=b&&z>=0&&z%2==0) ans=(ll(t)*C(R,i)%mod*C(R-i,x)%mod*C(z/2+R-1,R-1)+ans)%mod;
		}
		t=t*2%mod;
	}
	return ans;
}

struct LittleElephantAndBoard 
{
    int getNumber(int M, int R, int G, int B)
    {
    	R=M-R;G=M-G;B=M-B;
    	if (R<0||G<0||B<0) return 0;//无解
    	fac[0]=1;for (int i=1;i<=M;i++) fac[i]=ll(fac[i-1])*i%mod;
    	inv[M]=power(fac[M],mod-2);for (int i=M;i;i--) inv[i-1]=ll(inv[i])*i%mod;//预处理阶乘的逆元
    	int ans=(calc(R+1,G,B,M-R)+calc(R-1,G,B,M-R))%mod;
    	ans=(calc(R,G,B,M-R)*2%mod+ans)%mod;
    	return ans*2%mod;
    }
};
