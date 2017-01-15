#include<bits/stdc++.h>
using namespace std;
char s[1<<21];int lw[1<<21],lo[1<<21],ro[1<<21],i,j,k,g,f[1<<21],S[1<<21],P=1e9+7;
class WolfDelaymasterHard
{
	public:
		int countWords(int n,int wl,int w0,int wm,int wa,int ol,int o0,int om,int oa)
		{
			for(;i<wl;i++)s[w0+1]='w',w0=(1ll*w0*wm+wa)%n;
			for(i=0;i<ol;i++)s[o0+1]='o',o0=(1ll*o0*om+oa)%n;
			for(i=1;i<=n;i++)lw[i]=s[i]=='w'?i:lw[i-1],lo[i]=s[i]=='o'?i:lo[i-1];
			for(ro[n+1]=n+1,i=n;i;i--)ro[i]=s[i]=='o'?i:ro[i+1];
			for(f[0]=S[0]=1,i=2;i<=n;S[i]=(S[i-2]+f[i])%P,i+=2)for(g=min(i-lw[i],i-lo[lw[i]]>>1),j=1;j<=g;)if(k=min(g,i-lo[i-j]>>1),j>k)j=i-ro[i-j-j]+1;else
			{
				if(f[i]=(f[i]+S[i-j-j])%P,i-k-k)f[i]=(f[i]+P-S[i-k-k-2])%P;
				j=i-lo[i-j]+1;
			}
			return f[n];
		}
};
