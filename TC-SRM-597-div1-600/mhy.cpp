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

const double eps=1e-6;
inline int sgn(const double &x){return x<-eps?-1:x>eps;}

class ConvexPolygonGame {
    public:
        struct rec{
            int x,y;
            friend inline bool operator <(const rec &a,const rec &b){return a.x!=b.x?a.x<b.x:a.y<b.y;}
        } a[105],b[200005];
        inline double slope(const rec &a,const rec &b){return a.x!=b.x?1.0*(b.y-a.y)/(b.x-a.x):0x3f3f3f3f;}
        int stack[105],now;
        int next[105];
        string winner(vector<int> X, vector<int> Y) {
            int n=X.size(),m=0;
            for (int i=0;i<n;i++) a[i].x=X[i],a[i].y=Y[i];
            sort(a,a+n);
            stack[now=0]=-1;
            for (int i=0;i<n;i++){
                for (;now>1&&slope(a[stack[now-1]],a[stack[now]])<slope(a[stack[now]],a[i]);now--);
                stack[++now]=i;
            }
            for (int i=1;i<now;i++) next[stack[i]]=stack[i+1];
            stack[now=0]=-1;
            for (int i=n-1;~i;i--){
                for (;now>1&&slope(a[stack[now-1]],a[stack[now]])<slope(a[stack[now]],a[i]);now--);
                stack[++now]=i;
            }
            for (int i=1;i<now;i++) next[stack[i]]=stack[i+1];
            bool ok=false;
            int okcnt=0,ok1cnt=0;
            for (int i=a[0].x;i<=a[n-1].x;i++){
                double L=0x3f3f3f3f,R=0x3f3f3f3f;
                bool pointL=false,pointR=false;
                for (int j=0;j<n;j++) if (a[j].x==i){
                    if (L==0x3f3f3f3f){
                        L=a[j].y,pointL=true;
                    } else{
                        R=a[j].y,pointR=true;
                    }
                }
                for (int j=0;j<n;j++){
                    int l=a[j].x,r=a[next[j]].x;
                    if (l>r) swap(l,r);
                    if (l<i&&i<r) (L==0x3f3f3f3f?L:R)=a[j].y+(i-a[j].x)*slope(a[j],a[next[j]]);
                }
                if (L==0x3f3f3f3f||R==0x3f3f3f3f) continue;
                if (L>R) swap(L,R),swap(pointL,pointR);
                if (pointL) L+=eps; else L-=eps;
                if (pointR) R-=eps; else R+=eps;
                //printf("%.3f %.3f\n",L,R);
                int cnt=floor(R)-ceil(L)+1.5;
                if (cnt) okcnt++;
                if (cnt>1) ok1cnt++;
                if (cnt) b[m++]=(rec){i,int(ceil(L))};
            }
            if (okcnt>1){
                if (ok1cnt) ok=true;
                else if (okcnt>2){
                    double s=slope(b[0],b[1]);
                    for (int i=1;i<m;i++) if (sgn(slope(b[i-1],b[i])-s)) ok=true;
                }
            }
            return ok?"Masha":"Petya";
        }
};

// CUT begin
ifstream data("ConvexPolygonGame.sample");

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

bool do_test(vector<int> X, vector<int> Y, string __expected) {
    time_t startClock = clock();
    ConvexPolygonGame *instance = new ConvexPolygonGame();
    string __result = instance->winner(X, Y);
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
        vector<int> X;
        from_stream(X);
        vector<int> Y;
        from_stream(Y);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(X, Y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475389185;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ConvexPolygonGame (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
