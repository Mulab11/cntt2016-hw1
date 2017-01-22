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

class EqualSums {
    public:
    int n, book[110], cur[110], g[110][110];
    bool isOkay(int x, int v)
    {
        book[x] = 1;
        if(cur[x] != -1) return cur[x] == v;
        cur[x] = v;
        if(v < 0) return false;
        for(int i=1;i<=n;i++) if(g[x][i] != -1) 
            if(isOkay(i, g[x][i] - v) == false) return false;
        return true;
    }
    
    bool isOkay1(int x, int v)
    {
        book[x] = 1;
        if(cur[x] != -1) return cur[x] == v;
         
        cur[x] = v;
        if(v < 0 || (x <= n/2 && v == 0)) return false;
        for(int i=1;i<=n;i++) if(g[x][i] != -1) 
            if(isOkay1(i, g[x][i] - v) == false) return false;
        return true;
    }
    
    int count(vector<string> board) {
        n = board.size();
        memset(g, -1, sizeof(g));
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(isdigit(board[i][j]))
        {
            int s = i+1, t = j + 1 + n;
            g[s][t] = g[t][s] = board[i][j] - '0';
        }
        
        n *= 2;
        int modu = 1e9+7;
        
        long long res = 1;
        memset(book, 0, sizeof(book));
        for(int i=1;i<=n;i++) if(!book[i]) 
        {
            int now = 0;
           
            for(int j=0;j<=9;j++) 
            {
                memset(cur, -1, sizeof(cur));
                now += isOkay(i, j);
            }
            (res *= now) %= modu;
            cout<<i<<" "<<now<<endl;
        }
        
        long long del = 1;
        memset(book, 0, sizeof(book));
        for(int i=1;i<=n;i++) if(!book[i]) 
        {
            int now = 0;
            for(int j=0;j<=9;j++) 
            {
                memset(cur, -1, sizeof(cur));
                now += isOkay1(i, j);
            }            
            (del *= now) %= modu;
        }
        return (res+modu-del)%modu;
    }
};

// CUT begin
ifstream data("EqualSums.sample");

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
    EqualSums *instance = new EqualSums();
    int __result = instance->count(board);
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
        int T = time(NULL) - 1479028748;
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
        cout << "EqualSums (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
