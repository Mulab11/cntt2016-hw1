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

const double pi=acos(-1.0);

class SplittingFoxes2 {
    public:
        struct rec{
            double r,i;
            rec(){}
            rec(double r,double i):r(r),i(i){}
            friend inline rec operator +(const rec &a,const rec &b){return rec(a.r+b.r,a.i+b.i);}
            friend inline rec operator -(const rec &a,const rec &b){return rec(a.r-b.r,a.i-b.i);}
            friend inline rec operator *(const rec &a,const rec &b){return rec(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);}
            friend inline rec operator -(const rec &a){return rec(-a.r,-a.i);}
        };
        rec calc_wn(int n){return rec(cos(2*pi/n),sin(2*pi/n));}
        rec sq(rec x){
            double alpha=atan2(x.i,x.r);
            alpha/=2;
            double d=sqrt(x.r*x.r+x.i*x.i);d=sqrt(d);
            return rec(d*cos(alpha),d*sin(alpha));
        }
        rec w[105],dft0[105],dft[105],t[105];
        bool ok(vector<int> a,vector<int> b){
            for (int i=0;i<(int)a.size();i++) if (a[i]!=b[i]) return a[i]<b[i];
            return false;
        }
        vector<int> getPattern(vector<int> amount) {
            int n=amount.size();
            rec wn=calc_wn(n);
            w[0]=rec(1,0);for (int i=1;i<n;i++) w[i]=w[i-1]*wn;
            //for (int i=0;i<n;i++) printf("%.4f %.4f\n",w[i].r,w[i].i);
            for (int i=0;i<n;i++) dft0[i]=rec(0,0);
            for (int i=0;i<n;i++) for (int j=0;j<n;j++) dft0[i]=dft0[i]+rec(amount[j],0)*w[i*j%n];
            //for (int i=0;i<n;i++) printf("%.4f %.4f\n",dft0[i].r,dft0[i].i);
            for (int i=0;i<n;i++) dft0[i]=sq(dft0[i]);
            //for (int i=0;i<n;i++) printf("%.4f %.4f\n",dft0[i].r,dft0[i].i);
            int m=(n+2)>>1;
            vector<int> ans;
            for (int s=0;s<1<<m;s++){
                for (int i=0;i<n;i++) if (s>>min(i,n-i)&1) dft[i]=-dft0[i]; else dft[i]=dft0[i];
                for (int i=0;i<n;i++) t[i]=rec(0,0);
                for (int i=0;i<n;i++) for (int j=0;j<n;j++) t[i]=t[i]+dft[j]*w[i*j%n];
                vector<int> valid;
                for (int i=0;i<n;i++) valid.push_back(int(round(t[i].r/n)));
                int tag=1;
                for (int i=0;i<n;i++) if (valid[i]<0) tag=0;
                for (int i=0;i<n;i++) if (valid[i]!=valid[(n-i)%n]) tag=0;
                for (int i=0;i<n;i++){
                    int s=0;
                    for (int j=0;j<n;j++) s+=valid[j]*valid[(i+n-j)%n];
                    if (s!=amount[i]) tag=0;
                }
                if (!tag) continue;
                if (ans.empty()||ok(valid,ans)) ans=valid;
            }
            if (ans.empty()) ans.push_back(-1);
            return ans;
        }
};

// CUT begin
ifstream data("SplittingFoxes2.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<int> amount, vector<int> __expected) {
    time_t startClock = clock();
    SplittingFoxes2 *instance = new SplittingFoxes2();
    vector<int> __result = instance->getPattern(amount);
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
        vector<int> amount;
        from_stream(amount);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(amount, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484059905;
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
        cout << "SplittingFoxes2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
