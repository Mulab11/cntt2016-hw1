#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

const double eps=1e-7;
inline int sgn(double x){return x<-eps?-1:x>eps;}

template <typename T> inline T sqr(const T &x){return x*x;}

class FindPolygons {
    public:
        struct rec{int x,y,d;} a[1000005];
        inline double dist(const rec &a,const rec &b){return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));};
        double minimumPolygon(int L) {
            if (L&1) return -1;
            if (L==2) return -1;
            int n=0;
            for (int i=0;i<=L;i++) for (int j=0;j<=L;j++){
                double d=sqrt(i*i+j*j);
                if (!sgn(d-round(d))&&round(d)>0) n++,a[n].x=i,a[n].y=j,a[n].d=int(round(d));
            }
            int ans=0x3f3f3f3f;
            for (int i=1;i<n;i++) for (int j=i+1;j<n;j++){
                int d=L-a[i].d-a[j].d;
                if (d>0&&!sgn(d-dist(a[i],a[j]))){
                    int maxd=max(d,max(a[i].d,a[j].d)),mind=min(d,min(a[i].d,a[j].d));
                    if (maxd*2<L) ans=min(ans,maxd-mind);
                    //if (L<=5) printf("%d %d %d %d %d %d %d\n",a[i].x,a[i].y,a[j].x,a[j].y,L,mind,maxd);
                }
            }
            if (ans!=0x3f3f3f3f) return ans;
            return L%4!=0?1:0;
        }
};

// CUT begin
ifstream data("FindPolygons.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(int L, double __expected) {
    time_t startClock = clock();
    FindPolygons *instance = new FindPolygons();
    double __result = instance->minimumPolygon(L);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        int L;
        from_stream(L);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(L, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483150848;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "FindPolygons (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
