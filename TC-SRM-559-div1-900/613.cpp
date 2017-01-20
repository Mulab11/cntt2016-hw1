// BEGIN CUT HERE

// END CUT HERE
//#line 5 "CircusTents.cpp"
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
#include <cassert>
using namespace std;
struct point
{
	double x,y;
	friend point operator +(point a,point b){return (point){a.x+b.x,a.y+b.y};}
	friend point operator -(point a,point b){return (point){a.x-b.x,a.y-b.y};}
	friend point operator *(point a,double b){return (point){a.x*b,a.y*b};}
	
};
double getdis(point p1,point p2){return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));}
vector <point> po;
vector <int> r;
int n;
pair<double,double> st[210];
const double pi=acos(-1);
const double eps=1e-9;
bool check(double lim)
{
	//printf("%.3lf\n",lim);
	int top=0;
	for (int i=1;i<n;i++)
	{
		double d=sqrt(po[i].x*po[i].x+po[i].y*po[i].y);
		//if (d-r[0]-r[i]>=lim) return false;
		double dlt=atan2(po[i].y,po[i].x);
		double p=acos(r[0]/d);
		double L=0,R=pi;
		for (int t=1;t<=100;t++)
		{
			double mid=(L+R)/2,dis;
			if (mid<=p) dis=getdis((point){cos(mid)*r[0],sin(mid)*r[0]},(point){d,0.0})-r[i];
			else dis=getdis((point){cos(p)*r[0],sin(p)*r[0]},(point){d,0.0})-r[i]+r[0]*(mid-p);
			if (dis<=lim) L=mid;else R=mid;
		}
		if (L<=eps) continue;
		if (L+eps>pi) return true;
		double dl=dlt-L,dr=dlt+L;
		//swap(dl,dr);
		while (dl<0) dl+=2*pi;
		while (dl>=2*pi) dl-=2*pi;
		while (dr<0) dr+=2*pi;
		while (dr>=2*pi) dr-=2*pi;
			//printf("%.2lf %.2lf\n",dl,dr);
		if (dl<=dr) st[++top]=make_pair(dl,dr);
		else {st[++top]=make_pair(dl,2*pi);st[++top]=make_pair(0,dr);}
	}
	sort(st+1,st+top+1);
	if ((!top)||(st[1].first>eps)) return false;
	double lst=st[1].second;
	for (int i=2;i<=top;i++)
	{
		if (st[i].first>lst) return false;
		else lst=max(lst,st[i].second);
	}
	if (lst+eps<2*pi) return false;
	return true;
}
class CircusTents
{
        public:
        double findMaximumDistance(vector <int> x_, vector <int> y_, vector <int> r_)
        {
        	po.clear();r.clear();
			r=r_;
			n=x_.size();
			for (int i=0;i<n;i++) po.push_back((point){(double)x_[i]-x_[0],(double)y_[i]-y_[0]});
			cout<<check(24.5)<<endl;//return 0;
			
			double L=0,R=1;
			while (!check(R)) R*=2;
			//cout<<R<<endl;
			for (int t=1;t<=100;t++)
			{
				double mid=(L+R)/2;
				if (check(mid)) R=mid;else L=mid;
			}
			return R;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 3.7390603609952078; verify_case(0, Arg3, findMaximumDistance(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0,3,-3,3,-3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,3,3,-3,-3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,1,1,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 2.6055512754639887; verify_case(1, Arg3, findMaximumDistance(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {3,7,7,7,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4,6,1,-3,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,2,2,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 4.3264459099620725; verify_case(2, Arg3, findMaximumDistance(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {10,-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {8,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 24.63092458664212; verify_case(3, Arg3, findMaximumDistance(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {0,4,-4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,4,-4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 4.745474963675133; verify_case(4, Arg3, findMaximumDistance(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        CircusTents ___test;
        ___test.run_test(3);
        return 0;
}
// END CUT HERE
