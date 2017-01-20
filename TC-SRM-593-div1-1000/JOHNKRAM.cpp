#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000007
#define MAXN 1<<21
int i,j,k,m,l1[MAXN],r1[MAXN],l2[MAXN],r2[MAXN],f[MAXN],g[MAXN];
char a[MAXN];
class WolfDelaymasterHard
{
    public:
        int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)
        {
            for(i=0;i<wlen;i++)
            {
                a[w0+1]=1;
                w0=((ll)w0*wmul+wadd)%N;
            }
            for(i=0;i<olen;i++)
            {
                a[o0+1]=2;
                o0=((ll)o0*omul+oadd)%N;
            }
            for(i=1;i<=N;i++)
            {
                if(a[i]==1)l1[i]=i;
                else l1[i]=l1[i-1];
                if(a[i]==2)l2[i]=i;
                else l2[i]=l2[i-1];
            }
            for(r1[N+1]=r2[N+1]=N+1,i=N;i;i--)
            {
                if(a[i]==1)r1[i]=i;
                else r1[i]=r1[i+1];
                if(a[i]==2)r2[i]=i;
                else r2[i]=r2[i+1];
            }
            for(f[0]=g[0]=1,i=2;i<=N;i+=2)
            {
                m=min(i-l1[i],i-l2[l1[i]]>>1);
                for(j=1;j<=m;)
                {
                    k=min(m,i-l2[i-j]>>1);
                    if(j>k)j=i+1-r2[i-(j<<1)];
                    else
                    {
                        f[i]+=g[i-(j<<1)];
                        if(f[i]>=P)f[i]-=P;
                        if(i>k<<1)
                        {
                            f[i]-=g[i-(k+1<<1)];
                            if(f[i]<0)f[i]+=P;
                        }
                        j=i+1-l2[i-j];
                    }
                }
                g[i]=g[i-2]+f[i];
                if(g[i]>=P)g[i]-=P;
            }
            return f[N];
        }
};
