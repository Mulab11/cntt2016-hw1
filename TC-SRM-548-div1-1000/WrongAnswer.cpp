// FST:组合数预处理到 N^2*K 导致 K<2 时访问 C[i][2] 时挂了 
#define ll long long
#define MOD 1000000007
class KingdomAndCities{
public:
	ll C[2501][51],f[51][3][2][51];
	// n个1-连通块，n2个2-连通块，n3个3-连通块，m个2-度限制点用k条边连通的方案数
	ll F(int n,int n2,int n3,int m,int k){
		if(m){ // 有2-度限制点
			ll s=0;
			if(n>=2&&k>=2){ // 连接两个1-连通块
				(s+=C[n][2]*F(n-2,n2+1,0,m-1,k-2))%=MOD; // 新的2-连通块内不连
				if(k>=3)(s+=C[n][2]*F(n-2,n2+1,0,m-1,k-3))%=MOD; // 新的2-连通块内连
			}
			if(n&&n2&&k>=2){ // 连接1-连通块和2-连通块
				(s+=n*2*F(n-1,0,1,m-1,k-2))%=MOD; // 新的3-连通块内不连
				if(k>=3)(s+=n*2*F(n-1,0,1,m-1,k-3)*2)%=MOD; // 新的3-连通块内连1条
				if(k>=4)(s+=n*2*F(n-1,0,1,m-1,k-4))%=MOD; // 新的3-连通块内连2条
			}
			if(n2&&k>=2)(s+=F(n,1,0,m-1,k-2))%=MOD; // 连接同一个2-连通块
			if(m>=2&&k>=3){ // 连接一个2-度限制点和一个1-连通块
				(s+=n*F(n,0,0,0,k-3))%=MOD; // 另一个2-度限制点连同一个1-连通块
				if(n>=2){ // 另一个2-度限制点连另一个1-连通块
					(s+=n*(n-1)*F(n-2,1,0,0,k-3))%=MOD; // 新的2-连通块内不连
					if(k>=4)(s+=n*(n-1)*F(n-2,1,0,0,k-4))%=MOD; // 新的2-连通块内连
				}
			}
			return s;
		}
		ll&s=f[n][n2][n3][k];
		if(s)return s-1;
		if(n3){ // 有3-连通块
			s=C[C[n][2]+n*3][k]; // 图的总个数
			for(int x=0;x<n;x++) // 减去不连通图个数
				for(int y=0;y<=k;y++)
					(s-=C[n][x]*F(x,0,1,0,y)%MOD*C[C[n-x][2]][k-y])%=MOD; // (x,1,y)\(n-x,0,k-y) 的图个数
		}
		else if(n2){ // 没有3-连通块但有2-连通块
			s=C[C[n][2]+n*n2*2+4*C[n2][2]][k]; // 图的总个数
			for(int x=0;x<=n;x++) // 减去不连通图个数
				for(int x2=0;x2<n2&&x+x2+1<n+n2;x2++)
					for(int y=0;y<=k;y++)
						(s-=C[n][x]*C[n2-1][x2]%MOD*F(x,x2+1,0,0,y)%MOD*C[C[n-x][2]+(n-x)*(n2-x2-1)*2][k-y])%=MOD; // (x,x2+1,y)\(n-x,n2-x2-1,k-y) 的图个数
		}
		else{ // 只有1-连通块
			s=C[C[n][2]][k]; // 图的总个数
			for(int x=0;x<n-1;x++) // 减去不连通图个数
				for(int y=0;y<=k;y++)
					(s-=C[n-1][x]*F(x+1,0,0,0,y)%MOD*C[C[n-x-1][2]][k-y])%=MOD; // (x+1,y)\(n-x-1,k-y) 的图个数
		}
		if(s<0)s+=MOD;
		return s++;
	}
	int howMany(int N, int M, int K){
		for(int i=0;i<=N*N;i++)
			for(int j=*C[i]=1;j<=i&&(j<=2||j<=K);j++)
				C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
		return F(N-M,0,0,M,K);
	}
};
