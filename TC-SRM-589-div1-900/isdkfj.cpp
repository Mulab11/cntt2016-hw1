#include <bits/stdc++.h>

using namespace std;

const int inf=0x3f3f3f3f;
int n,m,a[305],b[305],f[305][2];

int work1(){
	int ret=inf;
	for(int s=0;s<1<<m;++s){//枚举前m个的状态 
		int w=1,t=0;
		while(w+m-1<=n){
			b[++t]=0;
			for(int i=0;i<m;++i)
				b[t]+=((s>>i)&1)^a[w+i];//每个块里面的1的个数 
			w+=m;
		}
		int tmp=0;
		for(int i=0;w+i<=n;++i)
			tmp+=((s>>i)&1)^a[w+i];//最后多出来的 
		memset(f,0x3f,sizeof f);
		f[t+1][0]=0;
		for(int i=t;i>=1;--i){
			f[i][0]=min(f[i+1][0]+b[i],f[i+1][1]+b[i]+1);
			f[i][1]=min(f[i+1][1]+m-b[i],f[i+1][0]+m-b[i]+1);//dp求最小次数 
		}
		tmp+=min(f[1][0],f[1][1]);
		ret=min(ret,tmp);
	}
	return ret;
}

int work2(){
	int k=n/m,ret=inf;
	for(int s=0;s<1<<k;++s){//枚举每个前缀是否改变 
		int w=k*m,p=0,tmp=0;
		memset(f,0,sizeof f);
		for(int i=k-1;i>=0;--i){
			tmp+=(s>>i)&1;
			p^=(s>>i)&1;
			w-=m;
			for(int j=1;j<=m;++j)
				++f[(w+j)%m][a[w+j]^p];//统计mod m下的0跟1的个数 
		}
		for(int i=k*m+1;i<=n;++i)++f[i%m][a[i]];
		for(int i=0;i<m;++i)tmp+=min(f[i][0],f[i][1]);//取较小的 
		ret=min(ret,tmp);
	}
	return ret;
}

class FlippingBitsDiv1 {
public:
	int getmin(vector <string> S, int M) {
		string s;
		for(int i=0;i<S.size();++i)s+=S[i];
		n=s.size();m=M;
		for(int i=1;i<=n;++i)a[i]=s[i-1]-'0';
		if(m<=17)return work1();
		else return work2();
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
