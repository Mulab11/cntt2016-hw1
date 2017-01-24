#include<bits/stdc++.h>
using namespace std;

int n,m;
double ans;
vector<int> a,b,f,g;

const int maxn=310,inf=1e9;
int dis[maxn][maxn];

vector<int> countPaths(vector<int> tree,int K)
{int i,j,k,N;
 vector<int> ret;

 for(i=0;i<maxn;i++)
	for(j=0;j<maxn;j++)
		dis[i][j]=inf;
 N=tree.size()+1;
 for(i=0;i<N-1;i++)
 {	dis[tree[i]][i+1]=1;
	dis[i+1][tree[i]]=1;
 }
 for(k=0;k<N;k++) //求出两点距离 
 	for(i=0;i<N;i++)
 		for(j=0;j<N;j++)
	 		dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
 ret.clear();
 for(i=0;i<K;i++) ret.push_back(0);
 for(i=N-1;i>=0;i--)
 	for(j=0;j<i;j++)
 		if(dis[i][j]<=(K-3)) //统计 
	 		ret[dis[i][j]+1]++;
 return ret;
}

vector<int> stringvec2intvec(vector<string> sv)
{int i,j,k,slen;
 string s="";
 vector<int> ret;
 ret.clear();
 
 for(i=0;i<sv.size();i++) s+=sv[i];
 slen=s.length();
 for(j=0;j<slen;j++) //把字符串格式转换成数字格式，放在vector里面 
 	if(s[j]>=48 && s[j]<=57)
 	{	for(k=j+1;k<=slen;k++)
	 		if(s[k]<48 || s[k]>57 || k==slen)
		 	{	ret.push_back(atoi(s.substr(j,k-j).c_str()));
				j=k;
				break;
			}
	}
 return ret;
}

class TreeUnion
{	public:
	double expectedCycles(vector <string> tree1, vector <string> tree2, int K)
	{	int i,x,y;
		double p;
			
		a=stringvec2intvec(tree1);
		b=stringvec2intvec(tree2);
		f=countPaths(a,K);
		g=countPaths(b,K);
		n=a.size()+1;
		m=K;
		ans=0;
		for(x=2;x<=m-2;x++) //枚举两边的距离，统计答案 
		{	y=m-x;
			p=1.0/(n*(n-1));
			ans+=2.0*f[x]*g[y]*p;
		}
		return ans;
	}
	
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; double Arg3 = 1.0; verify_case(0, Arg3, expectedCycles(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"0 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; double Arg3 = 1.3333333333333333; verify_case(1, Arg3, expectedCycles(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"0 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; double Arg3 = 0.3333333333333333; verify_case(2, Arg3, expectedCycles(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"0 ", "1 1 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0 1 0 ", "1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; double Arg3 = 4.0; verify_case(3, Arg3, expectedCycles(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"0 1 2 0 1 2 0 1 2 5 6 1", "0 11", " 4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0 1 1 0 2 3 4 3 4 6 6", " 10 12 12"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; double Arg3 = 13.314285714285713; verify_case(4, Arg3, expectedCycles(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TreeUnion ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
