#define ll long long
#define MOD 1000000009ll
class MegaFactorial{
public:
	ll N,K,P,Q; // P^Q:B的最小质因子幂次
	ll fac[20],ifac[20]; // fac[i]=i! ifac[i]=1/i!
	ll inv(ll a,ll p){return a==1?1:(1+p*(a-inv(p%a,a)))/a%p;}
	ll C(ll n,ll m){ // 计算C(n,m) mod 10^9+9
		ll x=ifac[m];
		for(ll i=0;i<m;i++)(x*=n-i)%=MOD;
		return x;
	}
	ll C2(ll n,ll m){return!n&&!m?1:C(n%Q,m%Q)*C2(n/Q,m/Q)%Q;} // 计算C(n,m) mod Q
	ll f[20],pos[20];
	ll calc(ll x){ // 对多项式f，已知f(0),f(1),...,f(K)，求f(x)
		ll y=0,pre=pos[K]=1;
		for(ll i=K;i;i--)pos[i-1]=pos[i]*(x-i+MOD)%MOD;
		for(ll i=0;i<=K;i++){
			(y+=pre*pos[i]%MOD*f[i]%MOD*ifac[i]%MOD*((K-i)%2?MOD-ifac[K-i]:ifac[K-i]))%=MOD;
			(pre*=x-i+MOD)%=MOD;
		}
		return y;
	}
	ll sum(ll d){ // 求(N,K)到(d,1)(2d,1)...(d*[N/d],1)的路径条数之和 mod 10^9+9
		ll t=N/d,s=*f=0;
		if(t<=K){
			for(ll i=1;i<=t;i++)(s+=C(N-d*i+K-1,K-1))%=MOD;
			return s;
		}
		for(ll i=1;i<=K;i++)f[i]=(f[i-1]+C(N-d*i+K-1,K-1))%MOD;
		return calc(t);
	}
	ll sum2(ll d){ // 求路径条数之和 mod Q
		if(Q==1)return 0;
		ll t=N/d,r=Q==2?16:27,s=0;
		for(ll i=0;i<t&&i<r;i++)(s+=C2(N-d*i-d+K-1,K-1)*(t/r+(i<t%r)))%=Q;
		return s;
	}
	int countTrailingZeros(int N, int K, int B){
		ll ps[11]={0,0,2,3,2,5,3,7,2,3,5},
		   qs[11]={0,0,1,1,2,1,1,1,3,2,1};
		this->N=N;this->K=K;P=ps[B];Q=qs[B];
		// 预处理阶乘及逆元
		for(ll i=*fac=1;i<=K;i++)fac[i]=fac[i-1]*i%MOD;
		ifac[K]=inv(fac[K],MOD);
		for(ll i=K;i;i--)ifac[i-1]=ifac[i]*i%MOD;
		// 计算答案
		ll ans=0,ans2=0;
		for(ll d=P;d<=N;d*=P)(ans+=sum(d))%=MOD,(ans2+=sum2(d))%=Q;
		return(ans+MOD-ans2)*inv(Q,MOD)%MOD;
	}
};
