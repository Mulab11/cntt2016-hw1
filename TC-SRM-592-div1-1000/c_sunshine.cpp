#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
const double pi=acos(-1.0);

class SplittingFoxes2
{
	public:
	
	int N;
	
	struct cp
	{
		double r,i;
		cp(){}
		cp(const double &_r,const double &_i):r(_r),i(_i){}
		cp operator+(const cp &o)const{return cp(r+o.r,i+o.i);}
		cp operator-(const cp &o)const{return cp(r-o.r,i-o.i);}
		cp operator*(const cp &o)const{return cp(r*o.r-i*o.i,r*o.i+i*o.r);}
	}w[30],temp[30];
	
	cp Sqrt(const cp &z)//Sqrt to complex number z.
	{
		double a=atan2(z.i,z.r),p=sqrt(z.r*z.r+z.i*z.i);
		a/=2.0;
		p=sqrt(p);
		return cp(p*cos(a),p*sin(a));
	}
	
	void DFT(vector<cp> &v)//Discrete Fourier Transform
	{
		for(int i=0;i<N;i++)
			temp[i]=v[i];
		for(int i=0;i<N;i++)
		{
			cp &s=v[i];
			s=cp(0,0);
			for(int j=0;j<N;j++)
				s=s+temp[j]*w[i*j%N];
		}
	}
	
	bool check(vector<int> &v,vector<int> &v2)
	{
		for(int i=0,j,t;i<N;i++)
		{
			t=0;
			for(j=0;j<N;j++)
				t+=v[j]*v[(i-j+N)%N];
			if(t!=v2[i])return 0;
		}
		return 1;
	}
	
	vector<int> getPattern(vector<int> amount)
	{
		//Because Discrete Fourier Transform is evaluation, and Inverse Discrete Fourier Transform is interpolation,
		//We can do DFT and extract a root to each value, then do IDFT and check if the numbers are all integers.
		int cnt=0;
		N=amount.size();
		double th=2*pi/N;
		for(int i=0;i<N;i++)
			w[i]=cp(cos(th*i),sin(th*i));
		vector<cp> v,v_;
		for(int i=0;i<N;i++)
			v.push_back(cp((double)amount[i]/(N*N),0));
		DFT(v);//Evaluation
		for(int i=0;i<N;i++)
			v[i]=Sqrt(v[i]);
		for(int i=0;i<N;i++)
			w[i].i=-w[i].i;
		int K=N+2>>1;
		vector<int> ans,tmp;
		//Because complex number has two roots, we must try all possible arrays, and it seem to be 2^n distinct arrays.
		//But we know P[i mod N] = P[(-i) mod N], so there are at most 2^ceil(n/2) distinct fesible values of sqrt(DFT(A))
		for(int s=0;s<1<<K;s++)
		{
			v_=v;
			for(int i=0;i<N;i++)
				if(s>>min(i,N-i)&1)
					v_[i]=cp(-v_[i].r,-v_[i].i);
			DFT(v_);
			tmp.clear();
			//Get possible P
			for(int i=0;i<N;i++)
				tmp.push_back((int)(max(v_[i].r,0.0)+0.45));
			if(check(tmp,amount))//Check with brute-force
			{
				cnt++;
				if(ans.empty()||tmp<ans)
					ans=tmp;
			}
		}
		if(ans.empty())ans.push_back(-1);
		cout<<cnt<<endl; 
		return ans;
	}
};

