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

class EnclosingTriangle {
    public:
        struct rec{
            int x,y;
            rec(){}
            rec(int x,int y):x(x),y(y){}
            friend inline rec operator -(const rec &a,const rec &b){return rec(a.x-b.x,a.y-b.y);}
        } a[1000005];
        int next[1000005];
        inline long long cross(const rec &a,const rec &b){return 1ll*a.x*b.y-1ll*a.y*b.x;}
        int n;
        inline bool ok(int i,int j){if (i==j) return false;if (i>j) j+=n;return j<=next[i];}
        long long sum[1000005];
        long long calc(int i,int j,int k){
            while (k<j) k+=n;
            if (next[j]<k) return 0;
            int l=lower_bound(next+i+1,next+j+1,k)-next,r=lower_bound(next+i+1,next+j+1,i+n)-next-1;
            //printf("%d %d %d %d %lld\n",i,j,k,l,sum[j]-sum[l-1]-(j-l+1)*k+j-l+1);
            return (j-r)*(i+n-j-1)+(sum[r]-sum[l-1]-(r-l+1ll)*k+r-l+1);
        }
        long long getNumber(int m, vector<int> X, vector<int> Y) {
            n=0;
            for (int i=0;i<m;i++) a[++n]=rec(0,i);
            for (int i=0;i<m;i++) a[++n]=rec(i,m);
            for (int i=0;i<m;i++) a[++n]=rec(m,m-i);
            for (int i=0;i<m;i++) a[++n]=rec(m-i,0);
            for (int i=1;i<=n;i++) a[i+n]=a[i];
            m=X.size();
            for (int i=1,j=1;i<=n;i++){
                if (j<=i) j=i+1;
                for (;;j++){
                    bool tag=true;
                    for (int k=0;k<m;k++) if (cross(a[i]-a[j],rec(X[k],Y[k])-a[j])<0) tag=false;
                    if (!tag) break;
                }
                next[i]=j-1;
                //printf("next[%d]=%d\n",i,next[i]);
            }
            for (int i=1;i<=n;i++) next[i+n]=next[i]+n;
            for (int i=1;i<=n;i++) next[i+2*n]=next[i]+2*n;
            for (int i=1;i<=n*3;i++) sum[i]=sum[i-1]+next[i];
            long long ans=0;
            for (int i=1,k=n;i<=n;i++){
                int j=next[i];
                while (ok(k?k-1:n,i)) k?k--:k=n;
                while (!ok(k,i)) k<n?k++:k=1;
                ans+=calc(i,j,k);
                //printf("%d %d %d\n",i,j,k);
            }
            return ans/3;
        }
};

// CUT begin
ifstream data("EnclosingTriangle.sample");

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

bool do_test(int m, vector<int> x, vector<int> y, long long __expected) {
    time_t startClock = clock();
    EnclosingTriangle *instance = new EnclosingTriangle();
    long long __result = instance->getNumber(m, x, y);
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
        int m;
        from_stream(m);
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(m, x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475502949;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "EnclosingTriangle (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
