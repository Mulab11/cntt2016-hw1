// BEGIN CUT HERE

// END CUT HERE
#line 5 "Constellation.cpp"
#include<bits/stdc++.h>
using namespace std;

struct point 
{int x,y;
};
struct point a[110];

int n;
double ans;
double b[110];

int mul(point p0,point p1,point p2) //求叉积 
{return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

double calc(int i,int j)
{int k,s;
 double ret=1;
 
 for(k=1;k<=n;k++) //求出a[i],a[j]这个叉积出现的概率 
 {	if(k==i || k==j) continue;
 	s=mul(a[i],a[j],a[k]);
	if(s>0 || (s==0 && (a[k].x-a[i].x)*(a[k].x-a[j].x)>=0 && (a[k].y-a[i].y)*(a[k].y-a[j].y)>=0)) continue;
	//注意判断共线 
	ret=ret*(1-b[k]);
 }
 return ret;
}

class Constellation
{	public:
	double expectation(vector <int> x, vector <int> y, vector <int> prob)
	{	int i,j;
	 	double pr;
	 	
	 	n=x.size();
	 	for(i=1;i<=n;i++) a[i]=(point){x[i-1],y[i-1]};
	 	for(i=1;i<=n;i++) b[i]=prob[i-1]/1000.0;
	 	
	 	ans=0;
	 	for(i=1;i<=n;i++)
	 		for(j=1;j<=n;j++) //枚举两个点计算其叉积的贡献 
	 		{	if(i==j) continue;
	 			pr=calc(i,j);
	 			//cout<<i<<" "<<j<<" "<<pr<<endl;
	 			ans+=pr*b[i]*b[j]*mul((point){0,0},a[i],a[j]);
	 			//cout<<i<<" "<<j<<" "<<pr<<" "<<mul((point){0,0},a[i],a[j])<<endl;
	 		}
	 	ans/=2;
	 	return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {500,500,500}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 0.0625; verify_case(0, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0,1,0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1000,1000,400,800}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 0.6000000000000001; verify_case(1, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {-1,-1,-1,0,0,0,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,0,1,-1,0,1,-1,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {500,500,500,500,500,500,500,500,500}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 1.9375; verify_case(2, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {0,0,1,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,2,1,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1000,500,200,500,1000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 1.3; verify_case(3, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {1,5,5,8,2,6,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,6,4,2,5,7,9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100,400,200,1000,400,900,600}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 12.888936; verify_case(4, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {-100,100,-100,100,-42,57,-34,76,35,-75,-54,10,43}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-100,-100,100,100,52,-57,-84,63,-43,50,63,10,-44}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1000,1000,1000,1000,342,747,897,325,678,34,53,6,253}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 40000.0; verify_case(5, Arg3, expectation(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	Constellation ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
