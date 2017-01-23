// BEGIN CUT HERE

// END CUT HERE
#line 5 "EnclosingTriangle.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const long long inf=1e18;

struct point 
{int x,y;
};
struct point a[300010],b[110];

int n,m;
int f[300010],g[300010];
long long ans;
long long sum[300010];

long long mul(point p0,point p1,point p2)
{//cout<<"## "<<p1.x<<" "<<p1.y<<" "<<p2.x<<" "<<p2.y<<endl;
 return (ll)(p1.x-p0.x)*(p2.y-p0.y)-(ll)(p2.x-p0.x)*(p1.y-p0.y);
}

int check(int i,int j)
{int k,ret;
 long long s,mi,ma;
 
 mi=inf;
 ma=-inf;
 for(k=1;k<=m;k++)
 {	s=mul(a[i],a[j],b[k]);
 	//if(i==1 && j==11) cout<<k<<" "<<s<<endl;
 	mi=min(mi,s);
 	ma=max(ma,s);
 }
 ret=0;
 if(mi>=0) ret|=1;
 if(ma<=0) ret|=2;
 return ret;
}

class EnclosingTriangle
{	public:
	long long getNumber(int L, vector <int> x, vector <int> y)
	{	int i,j,k,p,l,r,mid;
		
		n=L*4;
		for(i=1;i<=L;i++) a[i]=(point){0,L-i};
		for(i=L+1;i<=2*L;i++) a[i]=(point){i-L,0};
		for(i=2*L+1;i<=3*L;i++) a[i]=(point){L,i-L*2};
		for(i=3*L+1;i<=4*L;i++) a[i]=(point){4*L-i,L};
		m=x.size();
		for(i=1;i<=m;i++) b[i]=(point){x[i-1],y[i-1]};
		for(i=1;i<=n;i++)
		{	p=i+1;
			l=i+1;
			r=n;
			while(l<=r)
			{	mid=(l+r)/2;
				if(check(i,mid)&1)
				{	p=max(p,mid);
					l=mid+1;
				}
				else
					r=mid-1;
			}
			f[i]=p;
			l=i+1;
			r=n;
			p=n+1;
			while(l<=r)
			{	mid=(l+r)/2;
				if(check(i,mid)&2)
				{	p=min(p,mid);
					r=mid-1;
				}
				else
					l=mid+1;
			}
			g[i]=p;
		}
		//cout<<check(1,11)<<endl;
		//for(i=1;i<=n;i++)
		//	cout<<i<<" "<<f[i]<<" "<<g[i]<<endl;
		
		for(i=1;i<=n;i++) sum[i]=sum[i-1]+f[i];
		ans=0;
		k=2;
		for(i=1;i<=n;i++)
		{	while(k<=n && (f[k]<g[i] || k<=i)) k++;
			//cout<<"^^ "<<i<<" "<<k<<endl;
			if(k<=f[i])
			{	if(k<f[i])
					ans+=sum[f[i]-1]-sum[k-1]-(ll)(f[i]-1-k+1)*(g[i]-1);
				l=g[i];
				r=n;
				l=max(l,f[i]+1);
				r=min(r,f[f[i]]);
				//cout<<i<<" "<<l<<" "<<r<<endl;
				if(l<=r) ans+=r-l+1;
			}
			//cout<<i<<" "<<ans<<endl;
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arr1[] = { 1, 2, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 1, 3, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 19LL; verify_case(0, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 7; int Arr1[] = { 1, 1, 6, 6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 1, 6, 1, 6 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 0LL; verify_case(1, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 4; int Arr1[] = { 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 224LL; verify_case(2, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 10; int Arr1[] = { 2, 6, 7, 6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 7, 7, 9, 3 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 81LL; verify_case(3, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 15; int Arr1[] = { 7, 6, 5, 4, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 1, 4, 7, 10, 13 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 283LL; verify_case(4, Arg3, getNumber(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	EnclosingTriangle ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
