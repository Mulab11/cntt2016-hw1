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
const int M=2000010;

int dp[M],sum[M],delta[M],next1[M],next2[M];
char s[M];

struct WolfDelaymasterHard 
{
    int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)
    {
		if (N&1) return 0;
		
		for (int i=0;i<N;i++) s[i]='?';				// Concatenation of N '?'s
		long long x = w0;
		for(int i=0;i<wlen;i++){
			s[x] = 'w';				// Rewrite the x-th (0-based) character of s
			x = (x * wmul + wadd) % N;
		}
		x = o0;
		for(int i=0;i<olen;i++){
			s[x] = 'o';				// Rewrite the x-th (0-based) character of s
			x = (x * omul + oadd) % N;
		}
		int k1=N+1,k2=N+1;
		for (int i=N;i>=1;i--)
		{
			if (s[i-1]=='w') k1=i; else if (s[i-1]=='o') k2=i;
			next1[i]=k1;next2[i]=k2;
		}
		sum[0]=1;dp[0]=1;
		int q1=0,q2=0;
		int t=0;
		for (int i=1;i<=N/2;i++)
		{
			int k1=next1[2*i-1],k2=next2[2*i-1];
			int d=min(k2-2*i+1,(k1-2*i+1)/2);
			t=(t+dp[2*i-2])%mod;delta[2*i+2*d]=(delta[2*i+2*d]-dp[2*i-2]+mod)%mod;
			t=(t+delta[2*i])%mod;
			if (s[2*i-2]=='w') 
			{
				int k=2*i-1;
				while (k>=q1) 
				{
					if (s[k-1]=='o') {q2=k;break;}
					k--;
				}
				q1=2*i-1;
			}
			if (s[2*i-1]=='w') 
			{
				int k=2*i;
				while (k>=q1) 
				{
					if (s[k-1]=='o') {q2=k;break;}
					k--;
				}
				q1=2*i;
			}
			k1=q1;k2=q2;int k3=next2[q1];
			int L=max(2*i-k3+1,(2*i-k1)/2+1),R=min(2*i-k1,(2*i-k2)/2);
			if (L<=R)
			{
				if (R==i)
					dp[2*i]=(t+sum[2*i-2*L])%mod;
				else
					dp[2*i]=((t+sum[2*i-2*L]-sum[2*i-2*R-2])%mod+mod)%mod;
			}
			else
				dp[2*i]=t;
			sum[2*i]=(sum[2*i-2]+dp[2*i])%mod;
		}
		return dp[N];
    }
};
