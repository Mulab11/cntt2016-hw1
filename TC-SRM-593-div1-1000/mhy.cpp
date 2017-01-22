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

template <typename T> inline void tension(T &a,const T &b){if (a>b) a=b;}
template <typename T> inline void relax(T &a,const T &b){if (a<b) a=b;}

const int mod=1000000007;
inline void inc(int &a,int b){if ((a+=b)>=mod) a-=mod;}
inline void dec(int &a,int b){if (a>=b) a-=b; else a+=mod-b;}
const int MAXN=2000005;

class WolfDelaymasterHard {
    public:
        string s;
        int lastw[MAXN],nextw[MAXN],lasto[MAXN],nexto[MAXN];
        int dp[MAXN>>1],dpsum[MAXN>>1],d[MAXN>>1];
        int countWords(int n, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd) {
            s=string(n,'?');                // Concatenation of N '?'s
            long long x = w0;
            for(int i=0;i<wlen;i++){
                s[x] = 'w';             // Rewrite the x-th (0-based) character of s
                x = (x * wmul + wadd) % n;
            }
            x = o0;
            for(int i=0;i<olen;i++){
                s[x] = 'o';             // Rewrite the x-th (0-based) character of s
                x = (x * omul + oadd) % n;
            }
            lastw[0]=s[0]=='w'?0:-1;for (int i=1;i<n;i++) lastw[i]=s[i]=='w'?i:lastw[i-1];
            lasto[0]=s[0]=='o'?0:-1;for (int i=1;i<n;i++) lasto[i]=s[i]=='o'?i:lasto[i-1];
            nextw[n-1]=s[n-1]=='w'?n-1:-1;for (int i=n-2;~i;i--) nextw[i]=s[i]=='w'?i:nextw[i+1];
            nexto[n-1]=s[n-1]=='o'?n-1:-1;for (int i=n-2;~i;i--) nexto[i]=s[i]=='o'?i:nexto[i+1];
            memset(dp,0,sizeof(dp));
            memset(d,0,sizeof(d));
            dp[0]=1;
            for (int i=0,delta=0;i<=n>>1;i++){
                if (i&&~lastw[(i<<1)-1]){
                    int l=0,r=i-1;
                    int maxw=lastw[(i<<1)-1];
                    tension(r,maxw>>1);
                    relax(l,maxw-i+1);
                    if (~lasto[maxw]){
                        int maxo=lasto[maxw];
                        relax(l,(maxo>>1)+1);
                    }
                    if (~nexto[maxw]){
                        int mino=nexto[maxw];
                        tension(r,mino-i);
                    }
                    if (l<=r){
                        inc(dp[i],dpsum[r]);
                        if (l) dec(dp[i],dpsum[l-1]);
                    }
                }
                inc(delta,d[i]);
                inc(dp[i],delta);
                inc(dpsum[i]=i?dpsum[i-1]:0,dp[i]);
                if (i<n>>1){
                    int l=i+1,r=n>>1;
                    if (~nextw[i<<1]){
                        int minw=nextw[i<<1];
                        tension(r,minw>>1);
                    }
                    if (~nexto[i<<1]){
                        int mino=nexto[i<<1];
                        tension(r,mino-i);
                    }
                    if (l<=r){
                        inc(d[l],dp[i]);
                        if (r<n>>1) dec(d[r+1],dp[i]);
                    }
                }
            }
            return dp[n>>1];
        }
};

// CUT begin
ifstream data("WolfDelaymasterHard.sample");

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

bool do_test(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd, int __expected) {
    time_t startClock = clock();
    WolfDelaymasterHard *instance = new WolfDelaymasterHard();
    int __result = instance->countWords(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd);
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
        int N;
        from_stream(N);
        int wlen;
        from_stream(wlen);
        int w0;
        from_stream(w0);
        int wmul;
        from_stream(wmul);
        int wadd;
        from_stream(wadd);
        int olen;
        from_stream(olen);
        int o0;
        from_stream(o0);
        int omul;
        from_stream(omul);
        int oadd;
        from_stream(oadd);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475388067;
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
        cout << "WolfDelaymasterHard (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
