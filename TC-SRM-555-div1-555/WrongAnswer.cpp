#define ll long long
#define MOD 555555555
class XorBoard{
public:
	int C[3113][3113];
	ll f(int n,int m,int k){ // x[1]+x[2]+...+x[n]=m，x[i]>=0，且恰有k个x[i]为奇数的方案数
		return k>m||(m-k)%2?0:1ll*C[n][k]*C[(m-k)/2+n-1][n-1]%MOD;
	}
	int count(int H, int W, int Rcount, int Ccount, int S){
		for(int i=0;i<3113;i++)
			for(int j=*C[i]=1;j<=i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
		ll ans=0;
		for(int x=0,y;x<=H;x++){ // 枚举有多少行被取反
			if(x*2==H)x*W==S?ans=(ans+f(H,Rcount,x)*C[Ccount+W-1][W-1])%MOD:1; // x=H/2时列可以任意取反
			else if((S-W*x)%(H-2*x)==0)(y=(S-W*x)/(H-2*x))>=0?ans=(ans+f(H,Rcount,x)*f(W,Ccount,y))%MOD:1; // 否则列取反的数量y确定
		}
		return ans;
	}
};
