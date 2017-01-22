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

class ThreeColorability {
    public:
        struct Edge{int t,next,v;} G[1000005];int head[105],e;
        inline void add_edge(int x,int y,int z){
            G[++e].t=y,G[e].next=head[x],head[x]=e;G[e].v=z;
            G[++e].t=x,G[e].next=head[y],head[y]=e;G[e].v=z;
        }
        int vis[105];
        bool color(int x){
            for (int i=head[x];i;i=G[i].next) if (vis[G[i].t]<0){
                vis[G[i].t]=vis[x]^G[i].v;
                if (!color(G[i].t)) return false;
            } else if (vis[G[i].t]!=(vis[x]^G[i].v)) return false;
            return true;
        }
        bool ok(int n,int m,const vector<string> &cells){
            memset(head,0,sizeof(head)),e=1;
            for (int k=0;k<m;k++) for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if (cells[i][k]!='?'&&cells[j][k]!='?'){
                add_edge(i,j,cells[i][k]!=cells[j][k]);
            }
            memset(vis,-1,sizeof(vis));
            for (int i=0;i<n;i++) if (vis[i]<0&&(vis[i]=0,!color(i))) return false;
            return true;
        }
        vector<string> lexSmallest(vector<string> cells){
            int n=cells.size(),m=cells[0].size();
            if (!ok(n,m,cells)) return vector<string>();
            for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (cells[i][j]=='?'){
                cells[i][j]='N';
                if (!ok(n,m,cells)) cells[i][j]='Z';
            }
            return cells;
        }
};

// CUT begin
ifstream data("ThreeColorability.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<string> cells, vector<string> __expected) {
    time_t startClock = clock();
    ThreeColorability *instance = new ThreeColorability();
    vector<string> __result = instance->lexSmallest(cells);
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
        vector<string> cells;
        from_stream(cells);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cells, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483150759;
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
        cout << "ThreeColorability (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
