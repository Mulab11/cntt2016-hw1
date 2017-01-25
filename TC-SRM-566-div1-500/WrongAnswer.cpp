#define MOD 1000000007
class PenguinEmperor{
public:
	// 循环卷积
	int c[360];
	void mul(int*a,int*b,int n){
		for(int i=0;i<n;i++)c[i]=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)c[(i+j)%n]=(c[(i+j)%n]+1ll*a[i]*b[j])%MOD;
		for(int i=0;i<n;i++)a[i]=c[i];
	}
	// f[i][j]:前i天位移为j的方案数 g[j]:daysPassed/numCities天位移为j的方案数
	int f[360][360],g[360];
	int countJourneys(int numCities, long long daysPassed){
		// 递推计算f[i][j]
		f[0][0]=1;
		for(int i=1;i<=numCities;i++){
			for(int j=0;j<numCities;j++){
				f[i][j]=f[i-1][(j+i)%numCities];
				if(i*2%numCities)(f[i][j]+=f[i-1][(j+numCities-i)%numCities])%=MOD;
			}
		}
		// 倍增计算g[j]
		g[0]=1;
		long long n=daysPassed/numCities;
		for(int i=60;i>=0;i--){
			mul(g,g,numCities);
			if(n>>i&1)mul(g,f[numCities],numCities);
		}
		// 计算答案
		int ans=0;
		for(int i=0;i<numCities;i++)ans=(ans+1ll*f[daysPassed%numCities][i]*g[(numCities-i)%numCities])%MOD;
		return ans;
	}
};
