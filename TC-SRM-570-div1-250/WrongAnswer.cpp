#include <vector>
using namespace std;
class RobotHerb{
public:
	long long getdist(int T, vector <int> a){
		int vx[4]={1,0,-1,0},vy[4]={0,1,0,-1},d=0;
		long long x=0,y=0;
		for(int t=0;t<4;t++)
			for(int i=0;i<a.size();i++)x+=a[i]*vx[d]*(T/4ll+(t<T%4)),y+=a[i]*vy[d]*(T/4ll+(t<T%4)),d=(d+a[i])%4;
		return (x<0?-x:x)+(y<0?-y:y);
	}
};
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
[i])||!i&&c)continue;
			if(!t)select[id[i]]=1,stype[id[i]]=c^type[i];
			if(link(ex[i],ex[i]+1,c)&&link(ey[i],ey[i]+1,c)
				&&link(ex[i]+1,ey[i],c?0:(ex[i]^ey[i]^1)%2)&&dfs2(i+1))return 1; // 每条边内同类点必须偶数个 
			if(!t)select[id[i]]=0;undo(old);
		}
		return 0;
	}
	string getPossibility(vector <int> labels){
		for(int i=ecnt=top=opcnt=0;i<labels.size();i++) // 预处理边集
			if(labels[i]==-1)list[top++]=i;
			else for(int j=i+1;j<labels.size();j++)if(labels[i]==labels[j])ex[ecnt]=i,ey[ecnt++]=j;
		init(labels.size());
		for(int i=0;i<ecnt;i++)
			for(int j=i+1;j<ecnt;j++)if(cross(i,j)&&!link(i,j,1))return"IMPOSSIBLE"; // 输入的不合法则退出
		if(top<=12)return dfs1(0)?"POSSIBLE":"IMPOSSIBLE"; // 搜索1
		for(int j=0;j<ecnt;j++)id[j]=find_fa(j),type[j]=find_val(j),select[j]=0;
		init(labels.size());link(0,labels.size(),0);
		return dfs2(0)?"POSSIBLE":"IMPOSSIBLE"; // 搜索2
	}
};
1ll*P*(p-l)%MOD;
				}
			}
			ans=(ans+P)%MOD;
		}
		return ans; 
	}
};

			for(edge*e=first[i];e;e=e->next){
				if(siz[e->to]==n-k)dfs2(e->to,i,dep+1,ff*fv[e->to]%MOD);
			}
		}
		else for(edge*e=first[i];e;e=e->next)
			if(e->to!=fa)dfs2(e->to,i,dep+1,ff);
	}
	int getCount(vector <int> edge1, vector <int> edge2, int k){
		this->n=edge1.size()+1;this->k=k;ne=E;ans=0;
		for(int i=0;i<edge1.size();i++)link(edge1[i],edge2[i]),link(edge2[i],edge1[i]);
		init();
		if(k==1)return fac[n];
		if(2*k>n){
			init(0,-1);
			dfs1(0,-1,1);
			return ans*fac[2*k-n]%MOD*fac[n-k]%MOD*fac[n-k]%MOD;
		}
		for(int i=0;i<n;i++){
			init(i,-1);
			dfs2(i,-1,0,inv[k]);
		}
		return ans*fac[k]%MOD*fac[k]%MOD;
	}
};
