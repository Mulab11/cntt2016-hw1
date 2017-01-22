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

class FoxTheLinguist {
    public:
        int id[105][105];
        int mat[105][105],mat0[105][105];
        inline void add(int x,int y,int z){if (x!=y) mat[x][y]=min(mat[x][y],z);}
        int prev[105];
        int cir[105];
        int asn[105];
        int minimalHours(int nn, vector<string> courseInfo) {
            string str;
            for (int i=0;i<(int)courseInfo.size();i++) str+=courseInfo[i];
            int n=1;
            for (int i=0;i<nn;i++) for (int j=0;j<10;j++) id[i][j]=++n;
            for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) mat[i][j]=0x3f3f3f3f;
            for (int i=0;i<nn;i++) for (int j=1;j<10;j++) add(id[i][j],id[i][j-1],0);
            for (int i=0;i<nn;i++) add(1,id[i][0],0);
            for (int i=0;i<(int)str.size();i++) if (str[i]==':'){
                int x=str[i-6]-'A',xx=str[i-5]-'0';
                int y=str[i-2]-'A',yy=str[i-1]-'0';
                int v=1000*(str[i+1]-'0')+100*(str[i+2]-'0')+10*(str[i+3]-'0')+(str[i+4]-'0');
                add(id[x][xx],id[y][yy],v);
            }
            for (;;){
                //printf("%d\n",n);
                prev[1]=0;for (int i=2;i<=n;i++) prev[i]=i;
                for (int i=2;i<=n;i++) for (int j=1;j<=n;j++) if (mat[j][i]<mat[prev[i]][i]) prev[i]=j;
                for (int i=1;i<=n;i++) if (prev[i]==i) return -1;
                for (int i=1;i<=n;i++) cir[i]=0;
                int tag=1;
                for (int i=2;i<=n;i++) if (!cir[i]){
                    static int vis[105];
                    for (int j=1;j<=n;j++) vis[j]=0;
                    int j=i;
                    for (;j&&!vis[j];j=prev[j]) vis[j]=1;
                    if (i==j){
                        cir[j]=i,j=prev[j];
                        for (;j!=i;j=prev[j]) cir[j]=i;
                        tag=0;
                    }
                }
                if (tag){
                    int ans=0;
                    for (int i=2;i<=n;i++) ans+=mat[prev[i]][i];
                    return ans;
                }
                int n0=0;
                for (int i=1;i<=n;i++) if (!cir[i]) asn[i]=++n0; else if (cir[i]==i){
                    n0++;
                    int sum=0;
                    for (int j=1;j<=n;j++) if (cir[j]==i) asn[j]=n0,sum+=mat[prev[j]][j];
                    for (int j=1;j<=n;j++) if (cir[j]==i) for (int k=1;k<=n;k++) if (cir[j]!=cir[k]&&mat[k][j]!=0x3f3f3f3f) mat[k][j]+=sum-mat[prev[j]][j];
                }
                for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) mat0[i][j]=mat[i][j];
                for (int i=1;i<=n0;i++) for (int j=1;j<=n0;j++) mat[i][j]=0x3f3f3f3f;
                for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) if (asn[i]!=asn[j]&&mat0[i][j]!=0x3f3f3f3f) add(asn[i],asn[j],mat0[i][j]);
                n=n0;
            }
            return '?';
        }
};

// CUT begin
ifstream data("FoxTheLinguist.sample");

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

bool do_test(int n, vector<string> courseInfo, int __expected) {
    time_t startClock = clock();
    FoxTheLinguist *instance = new FoxTheLinguist();
    int __result = instance->minimalHours(n, courseInfo);
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
        int n;
        from_stream(n);
        vector<string> courseInfo;
        from_stream(courseInfo);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, courseInfo, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483287701;
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
        cout << "FoxTheLinguist (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
