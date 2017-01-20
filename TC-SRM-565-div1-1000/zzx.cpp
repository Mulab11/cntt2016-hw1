/* Copyright 2016 AcrossTheSky */
#include <iostream>
#include <cstdio>
#include <utility>
#include <cassert>
#include <map>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <bitset>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define REP2(i, a, b) for (int i = (a); i != (b); ++i)
#define PER(i, a, b) for (int i = (a); i >= (b); --i)
#define RVC(i, c) fot (int i = 0; i < (c).size(); ++i)
#define RED(k, u) for (int k = head[(u)]; k; k = edge[k].next)
#define lowbit(x) ((x) & (-(x)))
#define CL(x, v) memset(x, v, sizeof x)
#define MP std::make_pair
#define PB push_back
#define x first
#define y second
#define rank rankk
#define next nextt
#define link linkk
#define index indexx
#define abs(x) ((x) > 0 ? (x) : (-(x)))
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

template<class T> inline
bool getmin(T *a, const T &b) {
	if (b < *a) {
		*a = b;
		return true;
	}
	return false;
}

template<class T> inline
bool getmax(T *a, const T &b) {
	if (b > *a) {
		*a = b;
		return true;
	}
	return false;
}

const int mo = 1000000009;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/

struct UnknownTree {
	int work1(vector<int> ve) {
		LL ans=1;
		int i,j;
		sort(ve.begin(),ve.end());
		REP2(i,0,ve.size()) {
			int num=0;
			REP2(j,0,i)
				if(ve[j]<ve[i])
					++num;
			ans=ans*(num+1)%mo;
		}
		return ans;
	}

	int work2(vector<PII> ve) {
		int i;
		sort(ve.begin(),ve.end());
		if(ve.size()>1 && ve[0].x==ve[1].x)
			return 0;
		vector< pair<int,int>  > B;
		vector< int > A;
		int b=0;
		while(ve[b].y!=0)
			++b;
		if(b==0)
		{
			//the root is A
			REP2(i,1,ve.size())
			{
				if(ve[i].x!=ve[b].x+ve[i].y)
					return 0;
				A.PB(ve[i].y);
			}
			return work1(A);
		}
		//ve[0] is the root of the branch
		REP2(i,1,ve.size())
		{
			int da=ve[i].x-ve[0].x;
			int db=ve[i].y-ve[0].y;
			if(da==db)
				A.PB(da);
			else
			{
				if(ve[i].x-ve[0].x + ve[i].y < ve[0].y)
					return 0;
				B.PB(ve[i]);
			}
		}
		return (LL)work1(A)*work2(B)%mo;
	}

	int Center(int a,vector<int> da,vector<int> db,vector<int> dc)
	{
		vector< pair<int,int> > A,B,C;
		vector<int> ve;
		A.PB(MP(0,da[a]));
		A.PB(MP(da[a],0));
		B.PB(MP(0,db[a]));
		B.PB(MP(db[a],0));
		C.PB(MP(0,dc[a]));
		C.PB(MP(dc[a],0));
		int i;
		REP2(i,0,da.size())
			if(i!=a)
			{
				int pa=da[i]-da[a],PB=db[i]-db[a],pc=dc[i]-dc[a];
				if(pa == PB && PB == pc && pa>0)
					ve.PB( pa );
				else if(pa==PB && pa>0)
					C.PB( MP(pa,dc[i]) );
				else if(pc==pa && pc>0)
					B.PB( MP(pc,db[i]) );
				else if(PB==pc && PB>0)
					A.PB( MP(PB,da[i]) );
				else return 0;
			}
		LL ans=1;
		ans=ans*work1(ve)%mo;
		ans=ans*work2(C)%mo;
		ans=ans*work2(B)%mo;
		ans=ans*work2(A)%mo;
		return ans;
	}

	int calc(vector<int> da,vector<int> db,vector<int> dc,int ab,int ac) {
		if(ab<=0 || ac<=0)return 0;
		vector<int> A;
		vector< pair<int,int> > B,C;
		B.PB(MP(0,ab));
		B.PB(MP(ab,0));
		C.PB(MP(0,ac));
		C.PB(MP(ac,0));
		for (int i = 0; i < da.size(); ++i) {
			if(db[i]-ab==da[i] && dc[i]-ac==da[i])
				A.PB(da[i]);
			else if(da[i]+ac==dc[i])
				B.PB(MP(da[i],db[i]));
			else if(da[i]+ab==db[i])
				C.PB(MP(da[i],dc[i]));
			else
				return 0;
		}
		LL ans=1;
		ans=ans*work1(A)%mo;
		ans=ans*work2(B)%mo;
		ans=ans*work2(C)%mo;
		return ans;
	}

	int calc(vector<int> da, vector<int> db, vector<int> dc) {
		int m;
		LL ans=0;
		vector<PII> dd;
		REP2(m,0,da.size()) {
			dd.PB(MP(db[m] - da[m], dc[m] - da[m]));
			dd.PB(MP(da[m] + db[m], dc[m] - da[m]));
			dd.PB(MP(db[m] - da[m], dc[m] + da[m]));
			dd.PB(MP(da[m] - db[m], dc[m] - da[m]));
			dd.PB(MP(db[m] - da[m], da[m] - dc[m]));
		}
		sort(dd.begin(),dd.end());
		for (int m = 0; m < dd.size(); ++m) {
			if(m!=0 && dd[m].x==dd[m-1].x && dd[m].y==dd[m-1].y) continue;
			ans += calc(da,db,dc,dd[m].x,dd[m].y);
		}
		return ans % mo;
	}

	int getCount(vector <int> distanceA, vector <int> distanceB, vector <int> distanceC) {
		int ans = 0;
		for (int i = 0; i < distanceA.size(); ++i) ans = (ans + Center(i,distanceA,distanceB,distanceC)) % mo;
		ans = (ans + calc(distanceA,distanceB,distanceC)) % mo; // calc A B C
		ans = (ans + calc(distanceB,distanceA,distanceC)) % mo; // calc B A C
		ans = (ans + calc(distanceC,distanceA,distanceB)) % mo; // calc C A B
		return ans;
	}
};
// CUT begin
ifstream data("UnknownTree.sample");

string next_line() {
	string s;
	getline(data, s);
	return s;
}

template <typename T> void from_stream(T &t) {
	stringstream ss(next_line());
	ss >> t;
}

void from_stream(string &s) {
	s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
	int len;
	from_stream(len);
	ts.clear();
	for (int i = 0; i < len; ++i) {
		T t;
		from_stream(t);
		ts.PB(t);
	}
}

template <typename T>
string to_string(T t) {
	stringstream s;
	s << t;
	return s.str();
}

string to_string(string t) {
	return "\"" + t + "\"";
}

bool do_test(vector<int> distancesA, vector<int> distancesB, vector<int> distancesC, int __expected) {
	time_t startClock = clock();
	UnknownTree *instance = new UnknownTree();
	int __result = instance->getCount(distancesA, distancesB, distancesC);
	double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
	delete instance;

	if (__result == __expected) {
		cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
		return true;
	}
	else {
		cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
		cout << "           Expected: " << to_string(__expected) << endl;
		cout << "           Received: " << to_string(__result) << endl;
		return false;
	}
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
	int cases = 0, passed = 0;
	while (true) {
		if (next_line().find("--") != 0)
			break;
		vector<int> distancesA;
		from_stream(distancesA);
		vector<int> distancesB;
		from_stream(distancesB);
		vector<int> distancesC;
		from_stream(distancesC);
		next_line();
		int __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if ( do_test(distancesA, distancesB, distancesC, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1481719908;
		double PT = T / 60.0, TT = 75.0;
		cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
		cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
	set<int> cases;
	bool mainProcess = true;
	for (int i = 1; i < argc; ++i) {
		if ( string(argv[i]) == "-") {
			mainProcess = false;
		} else {
			cases.insert(atoi(argv[i]));
		}
	}
	if (mainProcess) {
		cout << "UnknownTree (1000 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
