// BEGIN CUT HERE

// END CUT HERE
#line 5 "ConvexPolygonGame.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const double eps=1e-9;
const int inf=1e9;

struct point 
{int x,y;
};
struct point a[110],b[200010];

int n,tot;
map<pair<int,int>,int> h;

long long mul(point p0,point p1,point p2)
{return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

class ConvexPolygonGame
{	public:
	string winner(vector <int> X, vector <int> Y)
	{	int i,j,k,flag,L,R;
		double s;
		
		n=X.size();
		for(i=1;i<=n;i++) a[i].x=X[i-1],a[i].y=Y[i-1];
		h.clear();
		for(i=1;i<=n;i++) h[make_pair(a[i].x,a[i].y)]=1;
		a[n+1]=a[1];
		tot=0;
		for(i=-100000;i<=100000;i++) //枚举每一个横坐标上在凸多边形内部的点个数 
		{	L=inf;
			R=-inf;
			for(j=1;j<=n;j++)
			{	if(a[j].x==i && a[j+1].x==i) //一条竖直的先的情况 
				{	L=min(a[j].y,a[j+1].y)+1;
					R=max(a[j].y,a[j+1].y)-1;
					break;
				}
				if((ll)(a[j].x-i)*(a[j+1].x-i)<=0) //与x=i相交 
				{	s=a[j].y+(double)(a[j+1].y-a[j].y)/(a[j+1].x-a[j].x)*(i-a[j].x);
					if(a[j+1].x>a[j].x)
					{	if(floor(s)+eps>s)
							L=floor(s);
						else
							L=ceil(s);
					}
					else
					{	if(ceil(s)-eps<s)
							R=ceil(s);
						else
							R=floor(s);
					}
				}
			}
			k=L;
			while(k<=R) //只要前200001个点就够了 
			{	if(h.find(make_pair(i,k))==h.end())
				{	b[++tot]=(point){i,k};
					if(tot>200001) return "Masha";
				}
				k++;
			}
		}
		for(i=3;i<=tot;i++) //判断是否全部共线 
			if(mul(b[1],b[2],b[i])!=0)
				return "Masha";
		return "Petya";
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 1, 3, 6, 10, 15, 21, 28, 36, 45, 46, 46, 45, 43, 40, 36, 31, 25, 18, 10, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Masha"; verify_case(0, Arg2, winner(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0, 4, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Masha"; verify_case(1, Arg2, winner(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0, 100, 100, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 100, 100}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Masha"; verify_case(2, Arg2, winner(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {0, 50, 100, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, -1, 0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Petya"; verify_case(3, Arg2, winner(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {-100000, 100000, 100000, -100000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1, -1, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Masha"; verify_case(4, Arg2, winner(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	ConvexPolygonGame ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
