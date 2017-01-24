// BEGIN CUT HERE

// END CUT HERE
#line 5 "Ear.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long

struct point 
{int x,y;
};
struct point a[310],b[310];

int n,m;
long long ans;
vector<int> rx,bx,by;

long long mul(point p0,point p1,point p2) //叉积 
{return (ll)(p1.x-p0.x)*(p2.y-p0.y)-(ll)(p2.x-p0.x)*(p1.y-p0.y);
}

bool operator <(point p1,point p2)
{return p1.x<p2.x || (p1.x==p2.x && p1.y<p2.y);
}

vector<int> trans(vector<string> A) //转换格式 
{string w;
 int i,s;
 vector<int> ret;
 
 w="";
 for(i=0;i<A.size();i++) w+=A[i];
 ret.clear();
 s=0;
 for(i=0;i<w.length();i++)
 	if(w[i]==' ')
 	{	ret.push_back(s);
 		s=0;
 	}
 	else
 		s=s*10+w[i]-48;
 ret.push_back(s);
 return ret;
}

class Ear
{	public:
	long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY)
	{	int i,j,k,s,s1,s2;
		
		rx=trans(redX);
		bx=trans(blueX);
		by=trans(blueY);
		
		n=rx.size();
		m=bx.size();
		for(i=1;i<=n;i++) a[i]=(point){rx[i-1],0};
		for(i=1;i<=m;i++) b[i]=(point){bx[i-1],by[i-1]};
		sort(a+1,a+n+1);
		ans=0;	
		for(i=1;i<=m;i++) //枚举p,q点 
			for(j=1;j<=m;j++)
			{	if(b[j].y>=b[i].y) continue;
				if(b[i].x<=b[j].x) //按照b[p].x和b[q].x关系分类讨论 
				{	s1=0;
					s=0;
					for(k=n;k>=1;k--) //算出A,B选法 
					{	if(a[k].x>=b[j].x) continue;
						if(a[k].x<b[i].x) s1+=s;
						s++;
					}
					s2=0;
					s=0;
					for(k=1;k<=n;k++) //算出C,D选法 
					{	if(a[k].x<=b[j].x) continue;
						if(mul(b[i],b[j],a[k])>0) s2+=s;
						s++;
					}
				}
				else //同理 
				{	s1=0;
					s=0;
					for(k=n;k>=1;k--)
					{	if(a[k].x>=b[j].x) continue;
						if(mul(b[i],b[j],a[k])<0) s1+=s;
						s++;
					}
					s2=0;
					s=0;
					for(k=1;k<=n;k++)
					{	if(a[k].x<=b[j].x) continue;
						if(a[k].x>b[i].x) s2+=s;
						s++;
					}
				}
				ans+=s1*s2;
			}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"3 2 8 7"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"5 4"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"2 4"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 1LL; verify_case(0, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"3 2 8 7"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"2 8"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"3 4"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 0LL; verify_case(1, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"1 2 6 9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"3 6 8 5"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 5 4 3"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 4LL; verify_case(2, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"10000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"10000 9999"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"10000 9999"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 0LL; verify_case(3, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"100 2", "00", " 39", "9", " 800 900 9", "99"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"15", "0 250 ", "349"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"2 3 1"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 12LL; verify_case(4, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"1", " ", "2", " ", "3", " ", "4 5 6", " 7 8 9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"4", " ", "5", " ", "6", " 7 ", "8"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1", " 2 ", "3 4", " 5"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 204LL; verify_case(5, Arg3, getCount(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	Ear ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
