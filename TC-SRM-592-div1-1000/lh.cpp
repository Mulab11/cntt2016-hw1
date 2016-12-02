#include<cmath>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const double pi=acos(-1),eps=1e-5;

struct complex{
	double rel,emp;
	complex(double a=0,double b=0):rel(a),emp(b){};
	void operator = (double a){rel=a;emp=0;}
	complex operator + (const complex &a)const{
		return complex(rel+a.rel,emp+a.emp);
	}
	complex operator - (const complex &a)const{
		return complex(rel-a.rel,emp-a.emp);
	}
	complex operator * (const complex &a)const{
		return complex(rel*a.rel-emp*a.emp,rel*a.emp+emp*a.rel);
	}
	complex operator / (const double &a)const{
		return complex(rel/a,emp/a);
	}
	complex operator * (const double &a)const{
		return complex(rel*a,emp*a);
	}
	friend complex sqrt(const complex &a){
		double t=atan2(a.emp,a.rel)/2;
		return complex(cos(t),sin(t))*sqrt(sqrt(a.rel*a.rel+a.emp*a.emp));
	}
};

class SplittingFoxes2{
	static const int maxn=55;
	bool ex;
	vector<int> ans;
	
	void update(vector<int>a){
		if (!ex){
			ex=true;
			ans=a;
		}
		else{
			if (ans>a) ans=a;
		}
		return;
	}
	
	int n;
	complex A[maxn],B[maxn],use[maxn];
	complex w[maxn];
	int p[maxn],num[maxn],ss[maxn];
	
	void dft(complex *a){
		for (int i=0;i<n;++i){
			use[i]=complex(0,0);
			for (int j=0;j<n;++j){
				use[i]=use[i]+a[j]*w[i*j%n];
//				printf("j=%d,use[%d]=%lf,%lf\n",j,i,use[i].rel,use[i].emp);
			}
		}
		memcpy(a,use,sizeof(use));
		return;
	}
	
	bool de;
	
	void check(){
		for (int i=0;i<n;++i){
			if (B[i].rel<-eps) return;
			if (B[i].emp>eps||B[i].emp<-eps) return;
			p[i]=B[i].rel+eps;
		}
		memset(num,0,sizeof(num));
		for (int i=0;i<n;++i)
		for (int j=0;j<n;++j) num[(i+j)%n]+=p[i]*p[j];
		for (int i=0;i<n;++i) if (num[i]!=ss[i]) return;
		update(vector<int>(begin(p),begin(p)+n));
		return;
	}
	
	public:
		vector<int> getPattern(vector<int> amount){
			ans={-1};
			n=amount.size();
			for (int i=0;i<n;++i) ss[i]=amount[i];
			w[0]=complex(1,0);
			w[1]=complex(cos(2*pi/n),sin(2*pi/n));
			for (int i=2;i<n;++i) w[i]=w[i-1]*w[1];
			for (int i=0;i<n;++i) A[i]=amount[i];
			dft(A);
			for (int i=0;i<n;++i) w[i].emp=-w[i].emp;
			for (int i=0;i<n;++i) A[i]=sqrt(A[i]);
			complex zero;
			int lim=1<<(n/2+1);
			for (int i=0;i<lim;++i){
				for (int j=0;j<n;++j) if (i&(1<<min(j,n-j))) B[j]=zero-A[j];
				else B[j]=A[j];
				dft(B);
				for (int j=0;j<n;++j) B[j]=B[j]/n;
				if (i==4) de=true;
				else de=false;
				check();
//				printf("%d B:\n",i);
//				for (int j=0;j<n;++j) printf("%lf,%lf\n",B[j].rel,B[j].emp);
			}
			return ans;
		}
};
