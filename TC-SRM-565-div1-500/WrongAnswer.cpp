// FST:预处理质数应处理到sqrt(10^9+10^6)而只处理到sqrt(10^9)
class TheDivisionGame{
public:
	int p[31638],f[1000010],g[1000010];
	bool c[31638];
	long long countWinningIntervals(int L, int R){
		int m=0,cnt[32]={1};
		for(int i=L;i<=R;i++)f[i-L+1]=i;
		for(int i=2;i<=31638;i++){
			if(!c[i]){
				p[m++]=i;
				for(int j=(L+i-1)/i*i;j<=R;j+=i){
					for(int&x=f[j-L+1];x%i==0;x/=i)g[j-L+1]++;
				}
			}
			for(int j=0;j<m&&i*p[j]<=31638;j++){
				c[i*p[j]]=1;
				if(i%p[j]==0)break;
			}
		}
		for(int i=L;i<=R;i++){
			if(f[i-L+1]>1)g[i-L+1]++;
			cnt[g[i-L+1]^=g[i-L]]++;
		}
		long long ans=(R-L+1ll)*(R-L+2ll)/2;
		for(int i=0;i<32;i++)ans-=cnt[i]*(cnt[i]-1ll)/2;
		return ans;
	}
};
