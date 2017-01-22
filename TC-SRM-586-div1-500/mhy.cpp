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

class History {
    public:
        int dist[55][55];
        string verifyClaims(vector<string> dynasties, vector<string> battles, vector<string> queries) {
            vector<vector<int> > a;
            int n=dynasties.size(),m=battles.size(),q=queries.size();
            for (int i=0;i<n;i++){
                vector<int> v;
                stringstream strin(dynasties[i]);
                for (int t;strin>>t;) v.push_back(t);
                a.push_back(v);
            }
            for (int i=0;i<n;i++) for (int j=0;j<n;j++) dist[i][j]=i!=j?-0x3f3f3f3f:0;
            string str;
            for (int i=0;i<m;i++) str+=battles[i];
            stringstream strin(str);
            for (string ss;strin>>ss;){
                //puts(ss.c_str());
                int x=ss[0]-'A',y,xv,yv;
                for (int i=1;i<(int)ss.size();i++) if ('A'<=ss[i]&&ss[i]<='Z') y=ss[i]-'A';
                for (int i=0;i<(int)ss.size();i++) if (ss[i]<'0'||'9'<ss[i]) ss[i]=' ';
                stringstream ssin(ss);
                ssin>>xv>>yv;
                //printf("%d %d %d %d\n",x,y,xv,yv);
                //x_baseline+x_r>=y_baseline+y_l
                dist[x][y]=max(dist[x][y],a[y][yv]+1-a[x][xv+1]);
                dist[y][x]=max(dist[y][x],a[x][xv]+1-a[y][yv+1]);
            }
            for (int k=0;k<n;k++) for (int i=0;i<n;i++) for (int j=0;j<n;j++) dist[i][j]=max(dist[i][j],dist[i][k]+dist[k][j]);
            //for (int i=0;i<n;i++) for (int j=0;j<n;j++) printf("%d %d %d\n",i,j,dist[i][j]);
            string ans;
            for (int tqdm=0;tqdm<q;tqdm++){
                string ss=queries[tqdm];
                int x=ss[0]-'A',y,xv,yv;
                for (int i=1;i<(int)ss.size();i++) if ('A'<=ss[i]&&ss[i]<='Z') y=ss[i]-'A';
                for (int i=0;i<(int)ss.size();i++) if (ss[i]<'0'||'9'<ss[i]) ss[i]=' ';
                stringstream ssin(ss);
                ssin>>xv>>yv;
                if (dist[y][x]>a[x][xv+1]-1-a[y][yv]||dist[x][y]>a[y][yv+1]-1-a[x][xv]) ans+="N"; else ans+="Y";
            }
            return ans;
        }
};

// CUT begin
ifstream data("History.sample");

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

bool do_test(vector<string> dynasties, vector<string> battles, vector<string> queries, string __expected) {
    time_t startClock = clock();
    History *instance = new History();
    string __result = instance->verifyClaims(dynasties, battles, queries);
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
        vector<string> dynasties;
        from_stream(dynasties);
        vector<string> battles;
        from_stream(battles);
        vector<string> queries;
        from_stream(queries);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(dynasties, battles, queries, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484325875;
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
        cout << "History (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
