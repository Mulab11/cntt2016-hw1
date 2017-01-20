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
#define PER(i, a, b) for (int i = (a); i >= (b); --i)
#define RVC(i, c) fot (int i = 0; i < (c).size(); ++i)
#define RED(k, u) for (int k = head[(u)]; k; k = edge[k].next)
#define lowbit(x) ((x) & (-(x)))
#define CL(x, v) memset(x, v, sizeof x)
#define MP std::make_pair
#define PB push_back
#define FR first
#define SC second
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

const int mo = 1000000007;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
bool flag[1000005];
vector<int>v;  
class HolyNumbers{  
    public:   //预处理素数表  
    void Init(int n){  
        for(int i=2;i * i <= n;i++){  
            if(flag[i]) continue;  
            for(int j=2;j*i<=n;j++)  
                flag[i*j]=true;  
        }  
        for(int i=2;i<=n;i++)  
            if(!flag[i])  
               v.push_back(i);  
    }  
    //搜索到第idx个素数,这时候的范围是 1--up  
    LL solve(int idx,LL up){  
        //如果素数没了，而且当前及以后的素数都超过范围，则返回1  
        //这个1表示之前搜的素数组成的数刚好就是要求的数  
        //初始的话就是返回1就代表1是满足条件的  
        if(idx>=v.size()||v[idx]>up)  return 1;  
        if((LL)v[idx]*v[idx]>=up){  
            //这里说明这个素因子以及后面的素因子都不可能取3个  
            //那么求出有多少个素因子可以取，都是取1个  
            int k=upper_bound(v.begin()+idx,v.end(),up)-v.begin();  
            return k-idx+1;  
        }  
        LL p=v[idx];  
        //不取这个素因子  
        LL ans=solve(idx+1,up);  
        //取奇数个  
        for(LL num=p;num<=up&&num>0;num*=p*p)  
            ans+=solve(idx+1,up/num);  
        return ans;  
    }  
    LL count(LL upTo, int maximalPrime){  
        v.clear();  
        Init(maximalPrime);  
        return solve(0,upTo);  
    }  
};  
// CUT begin
ifstream data("HolyNumbers.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(long long upTo, int maximalPrime, long long __expected) {
    time_t startClock = clock();
    HolyNumbers *instance = new HolyNumbers();
    long long __result = instance->count(upTo, maximalPrime);
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
        long long upTo;
        from_stream(upTo);
        int maximalPrime;
        from_stream(maximalPrime);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(upTo, maximalPrime, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478506938;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "HolyNumbers (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
