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
#include <map>

using namespace std;

template <typename T> inline void tension(T &a,const T &b){if (a>b) a=b;}
template <typename T> inline void relax(T &a,const T &b){if (a<b) a=b;}

inline double sqr(double x){return x*x;}

class CandyOnDisk {
    public:
        int mat[105][105];
        map<pair<int,int>,int> R;
        double minr[1005],maxr[1005];
        double dist[105][105];
        string ableToAchieve(vector<int> x, vector<int> y, vector<int> r, int sx, int sy, int tx, int ty) {
            memset(mat,0,sizeof(mat));
            if (sx==tx&&sy==ty) return "YES";
            vector<pair<int,int> > a;
            for (int i=0;i<(int)x.size();i++) a.push_back(make_pair(x[i],y[i]));
            R.clear();for (int i=0;i<(int)x.size();i++) relax(R[make_pair(x[i],y[i])],r[i]);
            sort(a.begin(),a.end()),a.resize(unique(a.begin(),a.end())-a.begin());
            int n=a.size();
            for (int i=0;i<n;i++) minr[i]=1e10,maxr[i]=-1e10,r[i]=R[make_pair(a[i].first,a[i].second)];
            for (int i=0;i<n;i++) for (int j=0;j<n;j++) dist[i][j]=sqrt(sqr(a[i].first-a[j].first)+sqr(a[i].second-a[j].second));
            for (int i=0;i<n;i++){
                double t=sqrt(sqr(a[i].first-sx)+sqr(a[i].second-sy));
                if (t<=r[i]) minr[i]=maxr[i]=t;
            }
            for (;;){
                int tag=0;
                for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (i!=j&&!mat[i][j]){
                    if (maxr[i]<dist[i][j]-r[j]||minr[i]>dist[i][j]+r[j]) continue;
                    mat[i][j]=1;
                    tag=1;
                    tension(minr[i],max(0.,dist[i][j]-r[j]));
                    relax(maxr[i],min(1.0*r[i],dist[i][j]+r[j]));
                    tension(minr[j],max(0.,dist[i][j]-r[i]));
                    relax(maxr[j],min(1.0*r[j],dist[i][j]+r[i]));
                }
                if (!tag) break;
            }
            for (int i=0;i<n;i++){
                double t=sqrt(sqr(a[i].first-tx)+sqr(a[i].second-ty));
                if (minr[i]<t&&t<maxr[i]) return "YES";
            }
            return "NO";
        }
};

// CUT begin
ifstream data("CandyOnDisk.sample");

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
        ts.push_back(t);
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

bool do_test(vector<int> x, vector<int> y, vector<int> r, int sx, int sy, int tx, int ty, string __expected) {
    time_t startClock = clock();
    CandyOnDisk *instance = new CandyOnDisk();
    string __result = instance->ableToAchieve(x, y, r, sx, sy, tx, ty);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        vector<int> r;
        from_stream(r);
        int sx;
        from_stream(sx);
        int sy;
        from_stream(sy);
        int tx;
        from_stream(tx);
        int ty;
        from_stream(ty);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, r, sx, sy, tx, ty, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483287730;
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
        cout << "CandyOnDisk (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
