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

class TreeUnion {
    public:
        int dist1[305][305],dist2[305][305];
        int c1[10],c2[10];
        double expectedCycles(vector<string> tree1, vector<string> tree2, int K) {
            int n=0;
            memset(dist1,0x3f,sizeof(dist1));
            {
                int nn=tree1.size();
                string stree("");
                for (int i=0;i<nn;i++) stree+=tree1[i];
                //puts(stree.c_str());
                stringstream strin(stree);
                for (int x;strin>>x;){
                    ++n;
                    dist1[x][n]=dist1[n][x]=1;
                    //printf("%d %d\n",n,x);
                }
                n++;
                for (int i=0;i<n;i++) dist1[i][i]=0;
            }
            for (int k=0;k<n;k++) for (int i=0;i<n;i++) for (int j=0;j<n;j++) dist1[i][j]=min(dist1[i][j],dist1[i][k]+dist1[k][j]);
            //printf("%d\n",n);
            memset(dist2,0x3f,sizeof(dist2));
            {
                int nn=tree2.size();
                string stree("");
                for (int i=0;i<nn;i++) stree+=tree2[i];
                stringstream strin(stree);
                for (int i=0,x;strin>>x;){
                    i++;
                    dist2[x][i]=dist2[i][x]=1;
                }
                for (int i=0;i<n;i++) dist2[i][i]=0;
            }
            for (int k=0;k<n;k++) for (int i=0;i<n;i++) for (int j=0;j<n;j++) dist2[i][j]=min(dist2[i][j],dist2[i][k]+dist2[k][j]);
            memset(c1,0,sizeof(c1)),memset(c2,0,sizeof(c2));
            double ans=0;
            for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if (dist1[i][j]<=4) c1[dist1[i][j]]++;
            for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if (dist2[i][j]<=4) c2[dist2[i][j]]++;
            //for (int i=1;i<=4;i++) printf("%d%c",c1[i]," \n"[i==4]);
            //for (int i=1;i<=4;i++) printf("%d%c",c2[i]," \n"[i==4]);
            for (int i=1;i<K-2;i++) for (int j=1;j<K-2;j++) if (i+j==K-2) ans+=c1[i]*c2[j];
            return ans*2/n/(n-1);
        }
};

// CUT begin
ifstream data("TreeUnion.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<string> tree1, vector<string> tree2, int K, double __expected) {
    time_t startClock = clock();
    TreeUnion *instance = new TreeUnion();
    double __result = instance->expectedCycles(tree1, tree2, K);
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
        vector<string> tree1;
        from_stream(tree1);
        vector<string> tree2;
        from_stream(tree2);
        int K;
        from_stream(K);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(tree1, tree2, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483456558;
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
        cout << "TreeUnion (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
