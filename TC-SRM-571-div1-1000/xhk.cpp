// BEGIN CUT HERE

// END CUT HERE
#line 5 "CandyOnDisk.cpp"
#include<bits/stdc++.h>
using namespace std;

const double eps=1e-7,inf=1e9;

struct unit
{int x,y,r,flag=0;
 double L,R;
};
struct unit a[110];

int n,t,w;
int q[100010],used[110];

double dis(int x1,int y1,int x2,int y2)
{return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void spfa()
{int i,j;
 double s,x,y;
 
 while(t<=w)
 {	i=q[t];
 	used[i]=0;
	for(j=1;j<=n;j++)
 	{	s=dis(a[i].x,a[i].y,a[j].x,a[j].y);	
 		if(i==j || s>a[i].r+a[j].r+eps) continue;
 		//cout<<t<<" "<<w<<" "<<s<<endl;
 		if(a[i].r>s-eps)
 		{	if(min(a[i].R,s+a[j].r)>max(a[i].L,s-a[j].r)-eps && (!a[j].flag || a[j].L>eps || a[j].R<a[j].r-eps))
 			{	a[j].L=0;
 				a[j].R=a[j].r;
 				a[j].flag=1;
 				//cout<<t<<" "<<w<<" "<<i<<" "<<j<<endl;
 				if(!used[j])
 				{	used[j]=1;
 					q[++w]=j;
 				}
 			}
 		}
 		else if(a[j].r>s-eps)
 		{	x=max((double)0,s-a[i].r);
 			y=min((double)a[j].r,s+a[i].r);
 			if(!a[j].flag || x<a[j].L-eps || y>a[j].r+eps)
 			{	a[j].L=min(a[j].L,x);
 				a[j].R=max(a[j].R,y);
 				a[j].flag=1;
 				if(!used[j])
 				{	used[j]=1;
 					q[++w]=j;
 				}
 			}
 		}
 		else if(a[i].R>s-a[j].r)
 		{	if(!a[j].flag || a[j].R<a[j].r-eps || a[j].L>s-a[i].R+eps)
 			{	a[j].L=s-a[i].R;
 				a[j].R=a[j].r;
 				a[j].flag=1;
 				if(!used[j])
 				{	used[j]=1;
 					q[++w]=j;
 				}
 			}
 		}
 	}
 	t++;
 }
}
 		
class CandyOnDisk
{	public:
	string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty)
	{	int i,j;
		double s;
		
		n=x.size();
		for(i=1;i<=n;i++)
		{	a[i].x=x[i-1];
			a[i].y=y[i-1];
			a[i].r=r[i-1];
			a[i].L=0;
			a[i].R=0;
			//cout<<a[i].x<<" "<<a[i].y<<endl;
			a[i].flag=0;
		}
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			{	if(i==j) continue;
				if(a[j].x==a[i].x && a[j].y==a[i].y && a[j].r<=a[i].r)
				{	a[j].x=inf;
					a[j].y=inf;
				}
			}
		if(sx==tx && sy==ty) return "YES";
		t=1;
		w=0;
		for(i=1;i<=n;i++)
		{	s=dis(a[i].x,a[i].y,sx,sy);
			if(s<a[i].r+eps)
			{	a[i].L=a[i].R=s;
				a[i].flag=1;
				q[++w]=i;
			}
		}
		//cout<<t<<" "<<w<<" "<<a[1].L<<" "<<a[1].R<<endl;
		spfa();
		
		//cout<<a[1].L<<" "<<a[1].R<<endl;
		//cout<<a[2].L<<" "<<a[2].R<<endl;
		
		for(i=1;i<=n;i++)
		{	s=dis(a[i].x,a[i].y,tx,ty);
			if(a[i].flag && s>a[i].L-eps && s<a[i].R+eps) return "YES";
		}
		return "NO";
	}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -1; int Arg4 = -2; int Arg5 = 6; int Arg6 = 1; string Arg7 = "YES"; verify_case(0, Arg7, ableToAchieve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_1() { int Arr0[] = {0, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {5, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -4; int Arg4 = 0; int Arg5 = -2; int Arg6 = 0; string Arg7 = "YES"; verify_case(1, Arg7, ableToAchieve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_2() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; int Arg4 = 0; int Arg5 = 571; int Arg6 = 571; string Arg7 = "NO"; verify_case(2, Arg7, ableToAchieve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_3() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 571; int Arg4 = 571; int Arg5 = 571; int Arg6 = 571; string Arg7 = "YES"; verify_case(3, Arg7, ableToAchieve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_4() { int Arr0[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; int Arg4 = 2; int Arg5 = 19; int Arg6 = 19; string Arg7 = "YES"; verify_case(4, Arg7, ableToAchieve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_5() { int Arr0[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; int Arg4 = 2; int Arg5 = 19; int Arg6 = 19; string Arg7 = "NO"; verify_case(5, Arg7, ableToAchieve(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	CandyOnDisk ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
