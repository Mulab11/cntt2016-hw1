#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define M 2000010
using namespace std;
struct WolfDelaymasterHard
{
	char s[M];
	int add[M],pre[M];
	int befo[M],befw[M],nxto[M],nxtw[M];
	static const int mod=1e9+7;
	int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)
	{
		long long x=w0;
		int i,j,y;
		for(i=0;i<N;i++)
		s[i+1]='?';
		for(i=0;i<wlen;i++)
		{
			s[x+1]='w';
			x=(x*wmul+wadd)%N;
		}
		x=o0;
		for(i=0;i<olen;i++)
		{
			s[x+1]='o';
			x=(x*omul+oadd)%N;
		}
		befo[1]=-1;befw[1]=-1;
		for(i=2;i<=N;i++)
		{
			befo[i]=befo[i-1];
			befw[i]=befw[i-1];
			if(s[i-1]=='o') befo[i]=i-1;
			else if(s[i-1]=='w') befw[i]=i-1;
		}
		nxto[N]=-1;nxtw[N]=-1;
		for(i=N-1;i>=0;i--)
		{
			nxto[i]=nxto[i+1];
			nxtw[i]=nxtw[i+1];
			if(s[i+1]=='o') nxto[i]=i+1;
			if(s[i+1]=='w') nxtw[i]=i+1;
		}
		int L,R,F;
		for(i=0;i<=N;i++)
		{
			//if(s[i]=='w') cout<<i<<' ';
			F=0;
			if(i!=0) (add[i]+=add[i-1])%=mod;
			if(i!=0&&!(i&1)&&s[i]!='w')
			{
				F=add[i];
				y=befw[i];
				if(y!=-1)
				{
					if(befo[y]==-1)
					{
					//	cout<<'*';
						if(y&1) R=y-1;
						else R=y-2;
						if(nxto[y]!=-1) R=min(R,2*nxto[y]-2-i);
						if(2*y-i<=0&&R>=0) (F+=pre[R])%=mod;
						else
						{
							L=2*y-i;
							if(L<=R&&L>=0)
							(F+=(pre[R]-pre[L-1])%mod)%=mod;
							(F+=mod)%=mod; 
						}
					}
					else
					{
						if(befo[y]&1) L=befo[y]+1;
						else L=befo[y];
						L=max(L,2*y-i);
						if(y&1) R=y-1;
						else R=y-2;
						if(nxto[y]!=-1) R=min(R,2*nxto[y]-2-i);
						//cout<<L<<' '<<R<<nxto[y]<<'@';
						if(L<=R&&L>=0) (F+=(pre[R]-pre[L-1])%mod)%=mod;
						(F+=mod)%=mod; 
					}
				}
			}
			if(i==0) F=1,pre[0]=1;
			else (pre[i]=pre[i-1]+F)%=mod;
			if(nxtw[i]==-1) R=N;
			else if(nxtw[i]&1) R=nxtw[i]-1;
			else R=nxtw[i]-2;
			if(nxto[i]!=-1) R=min(R,2*nxto[i]-2-i);
			if(i%2==0&&i==1200000)cout<<i<<' '<<F<<' '<<R<<endl;
			if(R>i)
			{
			//	cout<<'!';
				(add[i+1]+=F)%=mod;
				(add[R+1]-=F)%=mod;
				(add[R+1]+=mod)%=mod;
			}
		}
		return (F+mod)%mod;
	}
};
/*WolfDelaymasterHard P;
int main()
{
	int T=100;
	//cout<<P.countWords(T,4,T-4,1,2,1,T/2,0,0);
	cout<<P.countWords(1834500, 447, 1834390, 1, 2, 1750536, 39324, 1, 0);
}*/