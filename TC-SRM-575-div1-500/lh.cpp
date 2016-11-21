#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=50;

double _fz[50][50];

struct mat{//倍增求出k次后，一个位置到另一个位置或自己的概率。 
	double oth,sel;
	
	mat(){
		oth=sel=0;
		return;
	}
	
	void mul(const mat &b,int n){
		double x=0,y=0;
		
		x=(n-2)*oth*b.oth+sel*b.oth+oth*b.sel;
		y=1.0-x*(n-1);
		
		oth=x;
		sel=y;
		return;
	}
};

class TheSwapsDivOne{
	mat rec,A;
	
	public:
		double find(vector<string> sequence, int k){
			string tmp;
			for (auto &i:sequence) tmp+=i;
			int n=tmp.length();
			A.oth=2.0/n/(n-1);
			A.sel=1.0-A.oth*(n-1);
			rec.sel=1.0;
			while(k){
				if (k&1) rec.mul(A,n);
				A.mul(A,n);
				k>>=1;
			}
			int num=n*(n-1)/2+n;
			double ans=0;
			for (int i=0;i<n;++i){
				for (int j=0;j<n;++j){//枚举每个位置最终在哪个位置，统计答案。 
					double p=((i==j)?rec.sel:rec.oth);
					p*=(double)(j+1)*(n-j)/(double)num;
					ans+=p*(tmp[i]-'0');
				}
			}
			return ans;
		}
};
