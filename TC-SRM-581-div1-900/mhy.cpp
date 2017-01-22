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

class YetAnotherBoardGame {
    public:
        int ans,now;
        int n,m;
        int a[15][15],must[2][15];
        void dfs(int x,int y){
            if (x>=n){
                //puts("");for (int i=0;i<n;i++) for (int j=0;j<m;j++) printf("%d%c",a[i][j]," \n"[j==m-1]);
                int tag=1;
                for (int i=0;i<m;i++) if (a[n-1][i]) tag=0;
                if (tag) ans=min(ans,now);
                return;
            }
            if (y>=m) return dfs(x+1,0);
            if (!x||a[x-1][y]){
                now++;
                if (must[0][x]!=1&&must[1][y]!=1){
                    if (x-1>=0) a[x-1][y]^=1;
                    if (y-1>=0) a[x][y-1]^=1;
                    if (y+1<m) a[x][y+1]^=1;
                    if (x+1<n) a[x+1][y]^=1;
                    int x0=must[0][x],y0=must[1][y];
                    must[0][x]=must[1][y]=0;
                    dfs(x,y+1);
                    must[0][x]=x0,must[1][y]=y0;
                    if (x-1>=0) a[x-1][y]^=1;
                    if (y-1>=0) a[x][y-1]^=1;
                    if (y+1<m) a[x][y+1]^=1;
                    if (x+1<n) a[x+1][y]^=1;
                }
                if (must[0][x]!=0&&must[1][y]!=0){
                    if (x-1>=0) a[x-1][y]^=1;
                    if (y-1>=0) a[x][y-1]^=1;
                    if (y+1<m) a[x][y+1]^=1;
                    if (x+1<n) a[x+1][y]^=1;
                    a[x][y]^=1;
                    int x0=must[0][x],y0=must[1][y];
                    must[0][x]=must[1][y]=1;
                    dfs(x,y+1);
                    must[0][x]=x0,must[1][y]=y0;
                    a[x][y]^=1;
                    if (x-1>=0) a[x-1][y]^=1;
                    if (y-1>=0) a[x][y-1]^=1;
                    if (y+1<m) a[x][y+1]^=1;
                    if (x+1<n) a[x+1][y]^=1;
                }
                now--;
            }
            if (!x||!a[x-1][y]) dfs(x,y+1);
        }
        int minimumMoves(vector<string> board) {
            memset(must,-1,sizeof(must));
            ans=0x3f3f3f3f;
            n=board.size(),m=board[0].size();
            for (int i=0;i<n;i++) for (int j=0;j<m;j++) a[i][j]=board[i][j]=='W';
            dfs(0,0);
            return ans!=0x3f3f3f3f?ans:-1;
        }
};

// CUT begin
ifstream data("YetAnotherBoardGame.sample");

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

bool do_test(vector<string> board, int __expected) {
    time_t startClock = clock();
    YetAnotherBoardGame *instance = new YetAnotherBoardGame();
    int __result = instance->minimumMoves(board);
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
        vector<string> board;
        from_stream(board);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483456564;
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
        cout << "YetAnotherBoardGame (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
