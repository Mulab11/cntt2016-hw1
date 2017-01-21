// BEGIN CUT HERE

// END CUT HERE
#line 5 "SplittingFoxes2.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
typedef complex<double> Complex;
const int maxn=27;
const double pi=acos(-1.0);


class SplittingFoxes2{
	int n,_amount[maxn];
	Complex w[maxn];
	void DFT(Complex *a,int n){
		Complex _a[maxn];
		for (int i=0;i<n;++i) _a[i]=a[i];
		for (int i=0;i<n;++i){
			a[i]=0;
			for (int j=0;j<n;++j) a[i]+=_a[j]*w[i*j%n];
		}
	}
	Complex Sqrt(Complex a){
		double alpha=atan2(a.imag(),a.real())/2.0;
		Complex ret(cos(alpha),sin(alpha));
		return ret*sqrt(sqrt(a.real()*a.real()+a.imag()*a.imag()));
	}
	vector<int> to_int(Complex *a,int n){
		vector<int> ret;
		for (int i=0;i<n;++i) ret.push_back((int)max(a[i].real()+0.5,0.0));
		return ret;
	}
	bool check(vector<int> a){
		for (int i=0;i<n;++i){
			int now=0;
			for (int j=0;j<n;++j) now+=a[j]*a[(j+i)%n];
			if (now!=_amount[i]) return 0;
		}
		return 1;
	}
	
	Complex a[maxn],_a[maxn];
	public:
	vector <int> getPattern(vector <int> amount){
		vector<int> ret;
		n=amount.size();
		for (int i=0;i<n;++i) w[i]=Complex(cos(2.0*pi/n*i),sin(2.0*pi/n*i));
		for (int i=0;i<n;++i) a[i]=1.0*(_amount[i]=amount[i])/(n*n);
		DFT(a,n);
		for (int i=0;i<n;++i) _a[i]=Sqrt(a[i]);
		for (int i=0;i<n;++i) w[i]=Complex(w[i].real(),-w[i].imag());
		for (int k=0;k<(1<<(n/2+1));++k){
			for (int i=0;i<n;++i) a[i]=_a[i];
			for (int i=0;i<(n/2+1);++i)if ((k>>i)&1){
				a[i]=-a[i];
				if ((n-i)%n!=i) a[(n-i)%n]=-a[(n-i)%n];
			}
//			for (int i=0;i<n;++i) printf("%.3f %.3f\n",a[i].real(),a[i].imag());
//			puts("=========");
			DFT(a,n);
			vector<int> now=to_int(a,n);
			if (check(now)&&(ret.size()==0||now<ret)) ret=now;
		}
		if (ret.size()==0) ret.push_back(-1);
		return ret;
	}
};

//this is for test
/*
int main(){
	SplittingFoxes2 test;
	vector<int> a;
	a.push_back(1);
	a.push_back(0);
	a.push_back(0);
	vector<int> res=test.getPattern(a);
//	test.run_test(-1);
	return 0;
}
*/
//test end
