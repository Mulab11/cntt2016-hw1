#include <bits/stdc++.h>
#include <tr1/unordered_set>

using namespace std;

typedef unsigned u32;
const double pai=acos(-1);//π 
struct fs{//复数 
	double a,b;
	fs(){}
	fs(double a,double b):a(a),b(b){}
	fs operator+(const fs&rhs){return fs(a+rhs.a,b+rhs.b);}
	fs operator-(const fs&rhs){return fs(a-rhs.a,b-rhs.b);}
	fs operator*(const fs&rhs){return fs(a*rhs.a-b*rhs.b,a*rhs.b+b*rhs.a);}
	fs kg(){//把复数开平方 
		fs ret;
		if(b==0){
			if(a>0)ret=fs(sqrt(a),0);
			else ret=fs(0,sqrt(-a));
		} else {
			ret.a=sqrt((a+sqrt(a*a+b*b))/2);
			ret.b=b/(2*ret.a);
		}
		return ret;
	}
};
int n,A[33],as[33],p[33];
double a[33];
fs f[33],w[33];
bool zf[33];
tr1::unordered_set<u32>s;
void dfs(int x){
	if(x+x>n){
		for(int i=0;i<n;++i){
			fs t(0,0),tmp(1,0),wn=w[n-i];
			for(int j=0;j<n;++j)
			if(zf[j+j<=n?j:n-j])t=t+f[j]*tmp,tmp=tmp*wn;
			else t=t-f[j]*tmp,tmp=tmp*wn;
			t.a/=n;
			p[i]=int(t.a+0.5);//IDF回去 
			if(p[i]<0)return;//不是非负整数 
			if(i+i>n&&p[i]!=p[n-i])return;//不对称 
		}
		bool flag=1;
		for(int i=0;i<n;++i){
			int u=p[i]*p[0];
			for(int j=i+1,k=n-1;k>0;--k,++j){
				if(j==n)j=0;
				u+=p[j]*p[k];
			}
			if(u!=A[i])return;//得到的不是给定的数组 
		}
		if(flag){
			u32 ha=0;
			for(int i=0;i<n;++i)ha=ha*233+p[i];
			s.insert(ha);
			if(s.size()==1)flag=1;
			else {
				flag=0;
				for(int i=0;i<n;++i)
				if(p[i]<as[i]){flag=1;break;}
				else if(p[i]>as[i]){flag=0;break;}//是否字典序最小 
			}
			if(flag)for(int i=0;i<n;++i)as[i]=p[i];//保存答案 
		}
		return;
	}
	zf[x]=1;dfs(x+1);//取正根 
	zf[x]=0;dfs(x+1);//取负根 
}


class SplittingFoxes2 {
public:
	vector <int> getPattern(vector <int> amount) {
		n=amount.size();
		for(int i=0;i<n;++i)A[i]=amount[i],a[i]=A[i];
		fs wn=fs(cos(2*pai/n),sin(2*pai/n));w[0]=fs(1,0);
		for(int i=0;i<n;++i){
			fs tmp(1,0);f[i]=fs(0,0);
			for(int j=0;j<n;++j)f[i]=f[i]+fs(a[j],0)*tmp,tmp=tmp*w[i];
			f[i]=f[i].kg();//先DFT之后开平方 
			w[i+1]=w[i]*wn;
		}
		dfs(0);
		vector<int>ret;
		if(s.size())
			for(int i=0;i<n;++i)ret.push_back(as[i]);
		else ret.push_back(-1);
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
