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

class HexagonalBoard {
    public:
        int vis[10005];
        struct Edge{int t,next;} G[10005];int head[10005],e;
        inline void add_edge(int x,int y){
            G[++e].t=y,G[e].next=head[x],head[x]=e;
            G[++e].t=x,G[e].next=head[y],head[y]=e;
        }
        bool color(int x){
            for (int i=head[x];i;i=G[i].next) if (vis[G[i].t]<0){
                if (vis[G[i].t]=!vis[x],!color(G[i].t)) return false;
            } else if (vis[G[i].t]==vis[x]) return false;
            return true;
        }
        int id[105][105];
        int minColors(vector<string> board) {
            int n=board.size();
            bool empty=true;
            for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (board[i][j]=='X') empty=false;
            if (empty) return 0;
            bool is1=true;
            for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (board[i][j]=='X'){
                if (j+1<n&&board[i][j+1]=='X') is1=false;
                if (i+1<n&&j-1>=0&&board[i+1][j-1]=='X') is1=false;
                if (i+1<n&&board[i+1][j]=='X') is1=false;
            }
            if (is1) return 1;
            memset(id,0,sizeof(id));
            for (int i=0,k=0;i<n;i++) for (int j=0;j<n;j++) id[i][j]=++k;
            memset(vis,-1,sizeof(vis));
            memset(head,0,sizeof(head)),e=1;
            bool is2=true;
            for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (board[i][j]=='X'){
                if (j+1<n&&board[i][j+1]=='X') add_edge(id[i][j],id[i][j+1]);
                if (i+1<n&&j-1>=0&&board[i+1][j-1]=='X') add_edge(id[i][j],id[i+1][j-1]);
                if (i+1<n&&board[i+1][j]=='X') add_edge(id[i][j],id[i+1][j]);
            }
            for (int i=1;i<=n*n;i++) if (vis[i]<0&&(vis[i]=0,!color(i))) is2=false;
            if (is2) return 2;
            return 3;
        }
};

// CUT begin
ifstream data("HexagonalBoard.sample");

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
    HexagonalBoard *instance = new HexagonalBoard();
    int __result = instance->minColors(board);
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
        int T = time(NULL) - 1475388055;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "HexagonalBoard (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
