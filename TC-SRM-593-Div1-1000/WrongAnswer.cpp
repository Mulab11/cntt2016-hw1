#define MOD 1000000007
class WolfDelaymasterHard{
public:
	char s[2000010];
	int t[2000010],f[2000010];
	int min(int a,int b){return a<b?a:b;}
	int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd){
		for(int i=0;i<N;i++)s[i]='?';
		long long x=w0;
		for(int i=0;i<wlen;i++)s[x]='w',x=(x*wmul+wadd)%N;
		x=o0;
		for(int i=0;i<olen;i++)s[x]='o',x=(x*omul+oadd)%N;
		for(int i=t[N]=N;i--;)t[i]=s[i]=='o'?i:t[i+1];
		for(int i=N;i--;)if(t[i]>(i+N)/2)t[i]=(i+N)/2;
		f[N]=1;
		for(int l=N,r=N;r>=0;l=r=l-1){
			while(l&&s[l-1]!='w')--l;
			(f[r]+=f[r+2])%=MOD;
			for(int i=r-1;i>=l;i--)f[i]=(f[i]+f[i+2]*2ll-f[2*min(t[i],i+r>>1)-i+2]+MOD)%MOD;
			for(int i=l-1,rr;i>=0&&i>=2*l-r;i--)if((rr=min(t[i],i+r>>1))>=l)f[i]=(f[i]+f[2*l-i]*1ll-f[2*rr-i+2]+MOD)%MOD;
		}
		return (f[0]-f[2]+MOD)%MOD;
	}
};
