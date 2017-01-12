#include <bits/stdc++.h>

using namespace std;

const int mo=1000000007;
int c[1300][1300],f[55][55];
typedef long long LL;

class KingdomAndCities {
public:
	int howMany(int N, int M, int K) {
		int n=1225;
		c[0][0]=1;
		for(int i=1;i<=n;++i){
			c[i][0]=1;
			for(int j=1;j<=i;++j)
				if((c[i][j]=c[i-1][j-1]+c[i-1][j])>=mo)c[i][j]-=mo;
		}//预处理组合数 
		f[0][0]=1;
		for(int i=1;i<=N;++i)
			for(int j=0;j<=c[i][2]&&j<=K;++j){
				f[i][j]=c[c[i][2]][j];
				for(int k=1;k<i;++k)
					for(int l=0;l<=j;++l)
						if((f[i][j]-=LL(f[k][l])*c[c[i-k][2]][j-l]%mo*c[i-1][k-1]%mo)<0)f[i][j]+=mo;
			}//计算f[i][j] i个点j条边的连通图个数 用全部个数扣掉不连通的 
		if(M==0)return f[N][K];//M=0
		if(M==1){//M=1
			if(K<2)return 0;
			if(N<=2)return 0;
			if(N==3){
				if(K==2)return 1;
				if(K==3)return 1;
				return 0;
			}
			int ans=LL(c[N-1][2])*f[N-1][K-2]%mo;// 一个联通块 
			for(int i=1;i<N-1;++i){
				LL res=0;
				for(int j=0;j<=K-2;++j)
					res=(res+LL(f[i][j])*f[N-1-i][K-2-j])%mo;
				ans=(ans+res*c[N-2][i-1]%mo*i*(N-1-i))%mo;
				//两个联通块 
			}
			return ans;
		}
		//M=2
		if(K<3)return 0;
		if(N<2)return 0;
		int ans=LL(f[N-2][K-3])*(N-2)*(N-2)%mo;//两个点有边，一个联通块 
		if(N<=3)return ans;
		for(int i=1;i<N-2;++i)
			for(int j=0;j<=K-3;++j)
			ans=(ans+LL(c[N-3][i-1])*f[i][j]%mo*f[N-2-i][K-3-j]%mo*i%mo*(N-2-i)*2)%mo;
		//两个点有边，两个联通块 
		if(K>=4){
			ans=(ans+LL(f[N-2][K-4])*c[N-2][2]*c[N-2][2])%mo;
			//两个点没边，一个联通块 
			for(int i=1;i<N-2;++i){
				LL res=0;
				for(int j=0;j<=K-4;++j)
				res=(res+LL(f[i][j])*f[N-2-i][K-4-j])%mo;
				ans=(ans+LL(res)*c[N-3][i-1]%mo*i*(N-2-i)%mo*(i*(N-2-i)+(c[i][2]+c[N-2-i][2])*2))%mo;
			}
			//两个点没边，两个联通块
			for(int a=1;a<=N-4;++a)
				for(int b=1;a+b<=N-3;++b){
					int c=N-2-a-b;
					for(int i=0;i<=K-4;++i)
						for(int j=0;i+j<=K-4;++j){
							int k=K-4-i-j;
							ans=(ans+LL(f[a][i])*f[b][j]%mo*f[c][k]%mo*::c[N-3][a-1]%mo*::c[N-3-a][b-1]%mo*a*b*c%mo*(a+b+c)*2)%mo;
						}
				}//三个联通块 
		}
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
