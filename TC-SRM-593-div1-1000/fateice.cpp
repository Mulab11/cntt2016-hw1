#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define inf 1000000000
using namespace std;
class WolfDelaymasterHard
{
	int f,lw[2000010],rw[2000010],lo[2000010],ro[2000010],a[2000010],b[2000010],q=1000000007;
	char s[2000010];
public:
	int countWords(int n,int wlen,int w0,int wmul,int wadd,int olen,int o0,int omul,int oadd)
	{
		int i,j,k,l,r;
		for(i=1;i<=n;i++)
		  s[i]='?';
        long long x=w0;
        for(i=0;i<wlen;i++)
		  {
	       s[x+1]='w';
	       x=(x*wmul+wadd)%n;
          }
        x=o0;
        for(i=0;i<olen;i++)
		  {
	       s[x+1]='o';
	       x=(x*omul+oadd)%n;
          }
        for(i=1;i<=n;i++)
          {
		   lw[i]=(s[i]=='w'?i:lw[i-1]);
		   lo[i]=(s[i]=='o'?i:lo[i-1]);
		  }
		rw[n+1]=ro[n+1]=n+1;
		for(i=n;i>0;i--)
          {
		   rw[i]=(s[i]=='w'?i:rw[i+1]);
		   ro[i]=(s[i]=='o'?i:ro[i+1]);
		  }
		f=1;
		a[0]=1;
		for(i=2,k=0;i<=n;i+=2)
		  {
		   //w部分全为'?' 
		   j=min(ro[i-1]-(i-1),(rw[i-1]-(i-1))/2);
		   b[i]=(b[i]+f)%q;
		   b[i+j*2]=(b[i+j*2]-f)%q;
		   k=(k+b[i])%q;
		   f=k;
		   //w部分存在'w' 
		   j=lw[i];
		   l=max((i-j)/2+1,i-ro[j]+1);
		   r=min(i-j,(i-lo[j])/2);
		   if(l<=r)
		     f=((L)f+a[i-2*l]-((i-2*r==0)?0:a[i-2*r-2]))%q;
		   a[i]=(a[i-2]+f)%q;
		  }
		return (f+q)%q;
    }
};
