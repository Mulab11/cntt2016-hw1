// BEGIN CUT HERE

// END CUT HERE
#line 5 "CircusTents.cpp"
#include<bits/stdc++.h>
using namespace std;

const double pi=acos(-1),eps=1e-9;

struct unit
{int x,y,r;
};
struct unit a[110];

int n,tot;
double ans;
pair<double,int> b[1010];

double dis(double x,double y,double x1,double y1) //求距离 
{return sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
}

void add(double L,double R) //加入一个不合法区间 
{if(L<0) L+=2*pi;
 if(R<0) R+=2*pi;
 if(L>R)
 {	b[++tot]=make_pair(R,1);
 	b[++tot]=make_pair(L,-1);
 }
 else
 {	b[++tot]=make_pair(0,1);
 	b[++tot]=make_pair(L,-1);
 	b[++tot]=make_pair(R,1);
 	b[++tot]=make_pair(2*pi,-1);
 }
}	

int check(double len)
{int i,j,s;
 double l,r,mid,p,d,td,ang,a1,L,R,x,y;
 
 tot=0;
 for(i=2;i<=n;i++) //对每个圆求出不合法的角度区间 
 {	d=dis(a[1].x,a[1].y,a[i].x,a[i].y);
 	td=sqrt(d*d-a[1].r*a[1].r);
 	ang=atan2(a[i].y-a[1].y,a[i].x-a[1].x);
 	L=ang+acos(a[1].r/d);
 	R=ang-acos(a[1].r/d);
 	if(a[i].r+len>td) //如果这个len包含了(a[i].x,a[i].y)到圆a[1]的切线范围,多余的会包含a1的角度 
 	{	a1=(a[i].r+len-td)/a[1].r;
 		if(a1+acos(a[1].r/d)>pi) return 0;
 		L+=a1;
 		R-=a1;
 		add(L,R);
 	}
 	else if(a[i].r+len>d-a[1].r) //如果这个len不足以包含(a[i].x,a[i].y)到圆a[1]的切线范围,则包含一个角度 
 	{	l=0;
 		r=acos(a[1].r/d);
 		p=0;
 		while(fabs(r-l)>eps)
 		{	mid=(l+r)/2;
 			a1=ang+mid;
 			x=a[1].x+a[1].r*cos(a1);
 			y=a[1].y+a[1].r*sin(a1);
 			if(dis(x,y,a[i].x,a[i].y)<a[i].r+len) //二分算出交点 
 			{	p=max(p,mid);
			 	l=mid;
			}
			else
				r=mid;
		}
		L=ang+p;
		R=ang-p;

		add(L,R);
	}
 }
 b[++tot]=make_pair(0,0);
 b[++tot]=make_pair(2*pi,0);
 sort(b+1,b+tot+1);
 s=0;
 for(i=1;i<tot;i++)
 {	s+=b[i].second;
 	if(s==0 && b[i+1].first-b[i].first>eps)
 		return 1;
 }
 return 0;
}

class CircusTents
{	public:
	double findMaximumDistance(vector <int> X, vector <int> Y, vector <int> R)
	{	int i,j;
		double l,r,mid;
		
		n=X.size();
		for(i=1;i<=n;i++)
		{	a[i].x=X[i-1];
			a[i].y=Y[i-1];
			a[i].r=R[i-1];
		}
		
		l=0;
		r=80000;
		ans=0;
		while(fabs(r-l)>eps) //二分答案 
		{	mid=(l+r)/2;
			if(check(mid))
			{	ans=max(ans,mid);
				l=mid;
			}
			else
				r=mid;
		}
		return ans;
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
{	CircusTents ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
