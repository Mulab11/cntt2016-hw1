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

class EllysChessboard {
    public:
        static const int n=8;
        struct rec{int x,y;} a[10][10];
        int tag[10][10];
        int dp[20][20][20][20];
        int DP(int x1,int y1,int x2,int y2){
            if (x1>x2||y1>y2) return 0;
            int &ans=dp[x1][y1][x2][y2];
            if (~ans) return ans;
            ans=0x3f3f3f3f;
            if (x1==x2&&y1==y2) return ans=0;
            /*
            if (x1==x2){
                int miny=y2,maxy=y1;
                for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (x1<=a[i][j].x&&a[i][j].x<=x2&&y1<=a[i][j].y&&a[i][j].y<=y2)
                    miny=min(miny,a[i][j].y),maxy=max(maxy,a[i][j].y);
                if (miny<=maxy) ans=maxy-miny; else ans=0;
                return ans;
            }
            if (y1==y2){
                int minx=x2,maxx=x1;
                for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (x1<=a[i][j].x&&a[i][j].x<=x2&&y1<=a[i][j].y&&a[i][j].y<=y2)
                    minx=min(minx,a[i][j].x),maxx=max(maxx,a[i][j].x);
                if (minx<=maxx) ans=maxx-minx; else ans=0;
                return ans;
            }
            */
            int s0=DP(x1+1,y1,x2,y2),s1=DP(x1,y1+1,x2,y2),s2=DP(x1,y1,x2-1,y2),s3=DP(x1,y1,x2,y2-1);
            for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (tag[i][j]&&x1<=a[i][j].x&&a[i][j].x<=x2&&y1<=a[i][j].y&&a[i][j].y<=y2){
                //if (a[i][j].x==x1||a[i][j].x==x2||a[i][j].y==y1||a[i][j].y==y2) printf("%d %d %d %d %d %d %d %d\n",x1,y1,x2,y2,i,j,a[i][j].x,a[i][j].y);
                //if (x1==4&&y1==5&&x2==5&&y2==9) printf("%d %d %d %d\n",i,j,a[i][j].x,a[i][j].y);
                if (a[i][j].x==x1) s0+=max(x2-a[i][j].x,max(a[i][j].y-y1,y2-a[i][j].y));
                if (a[i][j].x==x2) s2+=max(a[i][j].x-x1,max(a[i][j].y-y1,y2-a[i][j].y));
                if (a[i][j].y==y1) s1+=max(y2-a[i][j].y,max(a[i][j].x-x1,x2-a[i][j].x));
                if (a[i][j].y==y2) s3+=max(a[i][j].y-y1,max(a[i][j].x-x1,x2-a[i][j].x));
            }
            /*
            11 4
            5 6
            4 9
            */
            ans=min(ans,s0);
            ans=min(ans,s1);
            ans=min(ans,s2);
            ans=min(ans,s3);
            //if (x1==4&&y1==5&&x2==5&&y2==9) printf("dp %d %d %d %d s:%d<-%d %d<-%d %d<-%d %d<-%d =%d\n",x1,y1,x2,y2,s0,DP(x1+1,y1,x2,y2),s1,DP(x1,y1+1,x2,y2),s2,DP(x1,y1,x2-1,y2),s3,DP(x1,y1,x2,y2-1),ans);
            //if (ans) printf("dp %d %d %d %d s:%d<-%d %d<-%d %d<-%d %d<-%d =%d\n",x1,y1,x2,y2,s0,DP(x1+1,y1,x2,y2),s1,DP(x1,y1+1,x2,y2),s2,DP(x1,y1,x2-1,y2),s3,DP(x1,y1,x2,y2-1),ans);
            return ans;
        }
        int minCost(vector<string> board) {
            memset(dp,-1,sizeof(dp));
            for (int i=0;i<n;i++) for (int j=0;j<n;j++) tag[i][j]=board[i][j]=='#',a[i][j].x=i+j,a[i][j].y=i-j+n-1;
            int ans=DP(0,0,2*n-2,2*n-2);
            return ans;
        }
};

// CUT begin
ifstream data("EllysChessboard.sample");

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
    EllysChessboard *instance = new EllysChessboard();
    int __result = instance->minCost(board);
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
        int T = time(NULL) - 1483456598;
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
        cout << "EllysChessboard (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
