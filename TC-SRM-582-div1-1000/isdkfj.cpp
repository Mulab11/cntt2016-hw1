#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
bool flag[1000005];
int mu[1000005],pr[1000005],tot;
vector<int>cnt[20005],zys[20005];
void predeal(){
	mu[1]=1;
	for(int i=2;i<=1000000;++i){//线性筛 
		if(!flag[i]){
			pr[++tot]=i;
			mu[i]=-1;
		}
		for(int j=1,k;j<=tot&&(k=i*pr[j])<=1000000;++j){
			flag[k]=1;
			if(i%pr[j]==0)break;
			mu[k]=-mu[i];
		}
	}
	for(int i=1;i<=tot;++i){//求出每个数的质因数 
		if(pr[i]>20000)break;
		for(int j=pr[i];j<=20000;j+=pr[i])zys[j].push_back(pr[i]);
	}
	for(int d=1;d<=20000;++d){//1 to d*i中有几个数是非完全平方数 
		int sum=0;
		cnt[d].push_back(0);
		for(int i=1;d*i<=500000;++i){
			if(mu[d*i])++sum;
			cnt[d].push_back(sum);
		}
	}
}
int gen2(LL x){//开平方根 
	int t=sqrt(x);
	if(LL(t+1)*(t+1)<=x)++t;
	if(LL(t)*t>x)--t;
	return t;
}
int gen3(LL x){//开立方根 
	int t=pow(x,1./3);
	if(LL(t+1)*(t+1)*(t+1)<=x)++t;
	if(LL(t)*t*t>x)--t;
	return t;
}
LL calc(LL n){
	LL ret=0;
	for(int a=1;LL(a)*a*a<n;++a)
		if(mu[a])ret+=gen2(n/a)-a;//a*x^2
	for(int b=1;LL(b)*b*b*b<n;++b){
		bool p3=1;
		for(int i=2;i*i*i<=b;++i)if(b%(i*i*i)==0){p3=0;break;}//是否有立方因子 
		if(!p3)continue;
		for(int k=1;k*k*k<=b;++k){
			int kk=k*k/__gcd(k*k,b);
			int bb=b/__gcd(k*k,b);
			int l=b/kk,r=gen3(n/b)/kk;
			if(mu[bb]){
				int N=zys[bb].size();
				for(int s=0;s<1<<N;++s){//枚举因数 
					int d=1;
					for(int i=0;i<N;++i)if(s&(1<<i))d=d*zys[bb][i];
					if(mu[d]==1)ret+=cnt[d][r/d]-cnt[d][l/d];
					else ret-=cnt[d][r/d]-cnt[d][l/d];
				}
			}
		}
	}
	return ret;
}

class SemiPerfectPower {
public:
	long long count(long long L, long long R) {
		predeal();
		return calc(R)-calc(L-1);
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
