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

const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
class RotatingBot {
    public:
        int tag[3005][3005];
        int minArea(vector<int> moves) {
            memset(tag,0,sizeof(tag));
            int n=moves.size(),x0=1502,y0=1502,x=x0,y=y0,minx=x0,maxx=x0,miny=y0,maxy=y0;
            tag[x0][y0]=1;
            for (int i=0,f=0;i<n;i++){
                for (int j=0;j<moves[i];j++){
                    x+=dx[f],y+=dy[f];
                    if (tag[x][y]) return -1;
                    tag[x][y]=1;
                }
                if (x>maxx){
                    if (maxx==x0) maxx=x; else return -1;
                } else{
                    if (i<n-1&&f==0&&x<maxx&&!tag[x+1][y]) return -1;
                }
                if (x<minx){
                    if (minx==x0) minx=x; else return -1;
                } else{
                    if (i<n-1&&f==2&&x>minx&&!tag[x-1][y]) return -1;
                }
                if (y>maxy){
                    if (maxy==y0) maxy=y; else return -1;
                } else{
                    if (i<n-1&&f==1&&y<maxy&&!tag[x][y+1]) return -1;
                }
                if (y<miny){
                    if (miny==y0) miny=y; else return -1;
                } else{
                    if (i<n-1&&f==3&&y>miny&&!tag[x][y-1]) return -1;
                }
                f=(f+1)%4;
            }
            return (maxx-minx+1)*(maxy-miny+1);
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
        int T = time(NULL) - 1484325734;
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
