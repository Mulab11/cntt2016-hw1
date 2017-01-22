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

class RotatingBot {
    public:
    int minArea(vector <int> moves)
    {
        bool book[200][200];
        int x = 100, y = 100;
        memset(book,0, sizeof(book));
        book[x][y] = true;
        
        int minX = x, maxX = x, minY = y, maxY = y;
        int d = 0;
        int dx[4] = {1,0,-1,0};
        int dy[4] = {0,-1,0,1};

        int allSteps = 0;
        for (int i=0; i<moves.size(); i++) {
            for (int j=0; j<moves[i]; j++) {
                allSteps++;
                int nx = x + dx[d];
                int ny = y + dy[d];
                if ( book[nx][ny] ) {
                    return -1;
                }
                x = nx;
                y = ny;
                minX = std::min(minX, x);
                minY = std::min(minY, y);
                maxX = std::max(maxX, x);
                maxY = std::max(maxY, y);
                book[x][y] = true;
            }
            d = (d+1) % 4;
        }
        d = 0, x = 100, y = 100;
        memset(book, 0, sizeof(book));
        book[x][y] = true;
        vector<int> moves2;
        
        int m = 0, cnt = 0;
        while (cnt < allSteps) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if ( book[nx][ny] || nx < minX || nx > maxX || ny < minY || ny > maxY ) {
                moves2.push_back(m);
                m = 0;
                d = (d + 1) % 4;
                nx = x + dx[d];
                ny = y + dy[d];
                if ( book[nx][ny] || nx < minX || nx > maxX || ny < minY || ny > maxY ) {
                    break;
                }
            } else {
                x = nx;
                y = ny;
                book[nx][ny] = true;
                m ++;
                cnt++; 
            }
        }
        if (m != 0) {
            moves2.push_back(m);
        }

        if (moves2 != moves) {
            return -1;
        }        
        return (maxX - minX + 1) * (maxY - minY + 1);
    }
};

// CUT begin
ifstream data("RotatingBot.sample");

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

bool do_test(vector<int> moves, int __expected) {
    time_t startClock = clock();
    RotatingBot *instance = new RotatingBot();
    int __result = instance->minArea(moves);
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
        vector<int> moves;
        from_stream(moves);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(moves, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1479041426;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "RotatingBot (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
