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
typedef long long ll;
const int moveNum = 8;


class HyperKnight {
    public:
    
    int numRows, numColumns, k, a, b;
    bool judge(int x, int y)
    {
        int res = 0;
        int dx[] = {a, a, -a, -a, b, b, -b, -b};
        int dy[] = {b, -b, b, -b, a, -a, a, -a};
        for(int i=0;i<moveNum;i++)
        {
            int xx = x + dx[i];
            int yy = y + dy[i];
            res += (xx > 0 && xx <= numRows && yy > 0 && yy <= numColumns);
        }
        return res == k;
    }
    
    long long countCells(int a, int b, int numRows, int numColumns, int k) {
        HyperKnight::numColumns = numColumns;
        HyperKnight::numRows = numRows;
        HyperKnight::k = k;
        HyperKnight::a = a;
        HyperKnight::b = b;
        
        vector<int> x, y;
//        for(int i=1;i<=numRows;i++) x.push_back(i);
        x.push_back(1); x.push_back(a); x.push_back(b); x.push_back(a+1); x.push_back(b+1); 
        x.push_back(numRows - a + 1); x.push_back(numRows - b + 1); x.push_back(numRows+1);
        sort(x.begin(), x.end()); x.erase(unique(x.begin(), x.end()), x.end());
        
//        for(int j=1;j<=numColumns;j++) y.push_back(j);
        y.push_back(1); y.push_back(a); y.push_back(b); y.push_back(a+1); y.push_back(b+1); 
        y.push_back(numColumns - a + 1); y.push_back(numColumns - b + 1); y.push_back(numColumns+1);
        sort(y.begin(), y.end()); y.erase(unique(y.begin(), y.end()), y.end());
        
        ll res = 0;
        for(int i=0;i<x.size()-1;i++)
            for(int j=0;j<y.size()-1;j++)
            {
                int mx = (x[i] + x[i+1]) / 2, my = (y[j] + y[j+1]) / 2;
                int lenx = x[i+1] - x[i], leny = y[j+1] - y[j];
                if(judge(mx, my))
                {
                    if(!judge(mx, y[j])) leny --;
                    if(!judge(x[i], my)) lenx --;
                    res += 1LL*lenx*leny;
                }
            }
        
        return res;
    }
};

// CUT begin
ifstream data("HyperKnight.sample");

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

bool do_test(int a, int b, int numRows, int numColumns, int k, long long __expected) {
    time_t startClock = clock();
    HyperKnight *instance = new HyperKnight();
    long long __result = instance->countCells(a, b, numRows, numColumns, k);
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
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        int numRows;
        from_stream(numRows);
        int numColumns;
        from_stream(numColumns);
        int k;
        from_stream(k);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, numRows, numColumns, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1480247705;
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
        cout << "HyperKnight (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
