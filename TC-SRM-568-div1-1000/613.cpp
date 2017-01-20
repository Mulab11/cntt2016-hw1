// BEGIN CUT HERE

// END CUT HERE
//#line 5 "DisjointSemicircles.cpp"
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
using namespace std;
int part[255],n,pp[255],fa[255];
bool sum[255][2];
vector <pair<int,int> >pt;
int getf(int s){if (fa[s]==s) return s;return fa[s]=getf(fa[s]);}
bool work1()
{
	int ths=-1;
	for (int i=0;i<n;i++) if (part[i]==-1) {ths=i;break;}
	if (ths==-1)
	{
		for (int i=0;i<n;i++) fa[i]=i;
		for (int i=0;i<(n>>1);i++)
		for (int j=i+1;j<(n>>1);j++)
		if (((pt[j].first>pt[i].first)&&(pt[j].first<pt[i].second)&&(pt[j].second>pt[i].second))||
			((pt[j].first<pt[i].first)&&(pt[j].second>pt[i].first)&&(pt[j].second<pt[i].second)))
		{
			fa[getf(i)]=getf(j+(n>>1));
			fa[getf(j)]=getf(i+(n>>1));
		}
		for (int i=0;i<(n>>1);i++) if (getf(i)==getf(i+(n>>1))) return false;
		return true;
	}
	for (int j=ths+1;j<n;j++) if (part[j]==-1)
	{
		part[ths]=j;part[j]=ths;pt.push_back(make_pair(ths,j));
		if (work1()) return true;
		part[ths]=part[j]=-1;pt.pop_back();
	}
	return false;
}
bool work2()
{
	sort(pt.begin(),pt.end());
	int ths=0;
	for (int i=0;i<n;i++)
	{
		if (part[i]==-1) ths++;
		pp[i]=ths;
	}
	cout<<pt.size()<<endl;
	for (int s=0;s<(1<<pt.size());s++)
	{
		for (int i=0;i<pt.size();i++)
		for (int j=i+1;j<pt.size();j++) if ((bool)(s&(1<<i))==(bool)(s&(1<<j)))
			if ((pt[j].first<pt[i].second)&&(pt[j].second>pt[i].second)) goto bomb;
	
		for (int i=0;i<=ths*2+1;i++) fa[i]=i;
		for (int i=0;i<n;i++) sum[i][0]=sum[i][1]=0;
		for (int i=0;i<pt.size();i++) {sum[pt[i].first][(bool)(s&(1<<i))]^=1;sum[pt[i].second][(bool)(s&(1<<i))]^=1;}
		for (int i=1;i<n;i++) {sum[i][0]^=sum[i-1][0];sum[i][1]^=sum[i-1][1];}
		for (int i=0;i<pt.size();i++)
		{
			//pp[pt[i].second] pp[pt[i].first-1]
			bool w=s&(1<<i);
			int fst=(pt[i].first)?pp[pt[i].first-1]:0,lst=pp[pt[i].second];
			bool ds=sum[pt[i].second][w]^((pt[i].first)?sum[pt[i].first-1][w]:0);
			if ((!w)&&((lst-fst)&1)) ds^=1;
			if (!ds)
			{
				fa[getf(fst)]=getf(lst);
				fa[getf(fst+ths+1)]=getf(lst+ths+1);
			}
			else
			{
				fa[getf(fst)]=getf(lst+ths+1);
				fa[getf(lst)]=getf(fst+ths+1);
			}
		}
		fa[getf(ths)]=getf(0);
		fa[getf(ths+ths+1)]=getf(0+ths+1);
		for (int i=0;i<=ths;i++) if (getf(i)==getf(i+ths+1)) goto bomb;
		cout<<s<<endl;
		return true;
		bomb:;
	}
	return false;
}
class DisjointSemicircles
{
        public:
        string getPossibility(vector <int> vec)
        {
        	memset(part,255,sizeof(part));
        	memset(pp,255,sizeof(pp));
        	pt.clear();
			n=vec.size();
			int js=0;
			for (int i=0;i<n;i++)
			{
				if (vec[i]==-1) js++;
				else if (pp[vec[i]]!=-1)
				{
					part[pp[vec[i]]]=i;part[i]=pp[vec[i]];
					pt.push_back(make_pair(part[i],i));
				}
				else pp[vec[i]]=i;
			}
			//for (int i=0;i<pt.size();i++) cout<<pt[i].first<<' '<<pt[i].second<<endl;
			//bool bo=(js<=12)?work1():work2();
			bool bo=work2();
			return bo?"POSSIBLE":"IMPOSSIBLE";
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = { -1, 0, -1, -1, 0, -1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "POSSIBLE"; verify_case(0, Arg1, getPossibility(Arg0)); }
	void test_case_1() { int Arr0[] = { 1, -1, 2, 1, -1, 2 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "IMPOSSIBLE"; verify_case(1, Arg1, getPossibility(Arg0)); }
	void test_case_2() { int Arr0[] = { 2, -1, -1, 0, -1, -1, 2, 0 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "POSSIBLE"; verify_case(2, Arg1, getPossibility(Arg0)); }
	void test_case_3() { int Arr0[] = { -1, 1, 3, -1, 1, 3, -1, -1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "IMPOSSIBLE"; verify_case(3, Arg1, getPossibility(Arg0)); }
	void test_case_4() { int Arr0[] = { -1, 5, -1, -1, 3, 6, 8, -1, 10, 7, -1, 7, 8, 0, 11, -1, -1, 11, 0, 10, 4, -1, 6, 5, -1, -1, 9, 9, 4, 3 }
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "POSSIBLE"; verify_case(4, Arg1, getPossibility(Arg0)); }
	void test_case_5() { int Arr0[] = { 4, -1, 2, 4, -1, 3, 3, 12, 2, 5, -1, 0, 9, 9, 8, -1, 12, 8, -1, 6, 0, -1, -1, -1, 5, 6, 10, -1, -1, 10 }
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "IMPOSSIBLE"; verify_case(5, Arg1, getPossibility(Arg0)); }
	void test_case_6() { int Arr0[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "POSSIBLE"; verify_case(6, Arg1, getPossibility(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        DisjointSemicircles ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
