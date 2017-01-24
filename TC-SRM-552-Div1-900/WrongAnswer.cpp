class HolyNumbers{
public:
	int P[100010],cnt,S[1000010],f[1000010],Q[330010],nxt[330010],fir[1000010],tot;
	bool com[1000010];
	long long ans;
	void dfs(int i,long long x){ // 搜索用前i个质数的奇数次幂能组成多少个x以内的数
		if(!i)ans++;
		else if(P[i]>x)ans+=S[x];
		else if(x<=1000000)Q[++tot]=i,nxt[tot]=fir[x],fir[x]=tot,ans++; // x<=10^6时不用搜索，记录询问之后解决
		else for(ans++;i;i--){ // x>10^6时，枚举最大质因子
			for(long long y=x/P[i-1];y;y/=P[i-1],y/=P[i-1])dfs(i-1,y); // 枚举最大质因子次数
		}
	}
	long long count(long long upTo, int maximalPrime){
		for(int i=2;i<=1000003;i++){ // 筛法预处理质数
			if(!com[i])P[cnt++]=i,S[i]=1,f[i]=cnt;
			for(int j=0;j<cnt&&P[j]<=1000003/i;j++){
				com[i*P[j]]=1;
				f[i*P[j]]=f[i]; // f[i]为i的最大质因子是第几个
				if(i%P[j]==0){
					S[i*P[j]]=i/P[j]%P[j]?0:S[i/P[j]];
					break;
				}
				S[i*P[j]]=S[i];
			}
		}
		for(int i=*S=S[1]=1;i<1000000;i++)S[i+1]+=S[i]; // 预处理10^6以内所有质因子幂次为奇数的数字个数
		int i=cnt-1;while(i&&P[i-1]>maximalPrime)--i;
		dfs(i,upTo);
		for(int i=0;i<=cnt;i++)P[i]=0;
		for(int i=1;i<=1000000;i++){ // y能被dfs(i,x)统计 <=> y<=x且f[y]<=i，二维偏序解决
			if(S[i]!=S[i-1])for(int j=f[i];j<=cnt;j+=j&-j)P[j]++;
			for(int k=fir[i];k;k=nxt[k])for(int j=Q[k];j;j-=j&-j)ans+=P[j];
		}
		return ans;
	}
};
