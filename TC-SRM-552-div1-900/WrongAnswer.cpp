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
		// 预处理前缀和
		for(int i=0;i<=n;i++){
			for(int j=0;j<=m;j++){
				if(!i||!j)D[i][j]=S[i][j]=0;
				else{
					D[i][j]=D[i-1][j]+D[i][j-1]-D[i-1][j-1];
					S[i][j]=S[i-1][j]+S[i][j-1]-S[i-1][j-1];
					if(flowers[i-1][j-1]=='L')D[i][j]++,S[i][j]++;
					if(flowers[i-1][j-1]=='P')D[i][j]--,S[i][j]++;
				}
			}
		}
		if((tmp=solve())>ans)ans=tmp;
		// 交换矩形行列
		tmp=n;n=m;m=tmp;
		for(int i=0;i<=n||i<=m;i++){
			for(int j=i+1;j<=n||j<=m;j++){
				tmp=D[i][j];D[i][j]=D[j][i];D[j][i]=tmp;
				tmp=S[i][j];S[i][j]=S[j][i];S[j][i]=tmp;
			}
		}
		return (tmp=solve())>ans?tmp:ans;
	}
};
		x[i]=calc(N-i);
			for(int j=i;j;j--)(C[j]+=C[j-1])%=MOD;
			for(int j=0;j<i;j++)x[i]=(x[i]+(MOD-C[j])*1ll*x[j])%MOD;
			ans=(ans+x[i]*1ll*s[i])%MOD;
		}
		return ans;
	}
};
��足条件就退出
		if(!rest){ // 枚举完所有点，判断是否可行
			init_ways();
			int w=ways((1<<N)-1);
			return w>=Min&&w<=Max;
		}
		int cnt=0;
		// i放新的一层
		if(cur!=-1)for(int i=0;i<N;i++)if(rest>>i&1){
			L[++top]=1<<i;
			for(G[i]=L[top-1];G[i];G[i]=(G[i]-1)&L[top-1]) // 枚举上一层向i连的边
				cnt+=count_graph(i,rest-(1<<i));
			top--;
		}
		// i放同一层
		for(int i=cur+1;i<N;i++)if(rest>>i&1){
			L[top]|=1<<i;
			if(top)for(G[i]=L[top-1];G[i];G[i]=(G[i]-1)&L[top-1]) // 枚举上一层向i连的边
				cnt+=count_graph(i,rest-(1<<i));
			else G[i]=0,cnt+=count_graph(i,rest-(1<<i));
			L[top]-=1<<i;
		}
		return cnt;
	}
	int getNumOrders(vector <int> blockTypes, int minWays, int maxWays){
		N=blockTypes.size();Min=minWays;Max=maxWays;
		for(int i=0;i<N;i++)cnt[i]=blockTypes[i],G[i]=0;
		*L=top=0;
		return count_graph(-1,(1<<N)-1);
	}
};
