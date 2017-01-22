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
#include <map>

using namespace std;

class HolyNumbers {
    public:
        static const int MAXN=1000005;
        int prime[MAXN],fac[MAXN];
        //map<pair<int,long long>,long long> dp;
        struct Hash_Table{
            static const int hash_size=1000007,MAXN=1000005;
            int head[hash_size],next[MAXN];int n;
            pair<int,long long> a[MAXN];long long v[MAXN];
            inline long long find(pair<int,long long> x){
                int h=(x.second*10000000+x.first)%hash_size;
                for (int i=head[h];i;i=next[i]) if (a[i]==x) return v[i];
                return -1;
            }
            inline void insert(pair<int,long long> x,long long y){
                if (n==MAXN-1) return;
                int h=(x.second*10000000+x.first)%hash_size;
                a[++n]=x,v[n]=y;next[n]=head[h],head[h]=n;
            }
            void init(){memset(head,0,sizeof(head)),n=0;}
        } dp;
        long long DP(int n,long long N){
            if (n>*prime||prime[n]>N) return 1;
            //if (dp.find(make_pair(n,N))!=dp.end()) return dp[make_pair(n,N)];
            {
                long long t=dp.find(make_pair(n,N));
                if (~t) return t;
            }
            long long p=prime[n];
            if (p*p*p>N&&(n<*prime&&p*prime[n+1]>N)){
                int l=n,r=(*prime)+1;
                for (int mid;r-l>1;(prime[mid]<=N?l:r)=mid) mid=(l+r)>>1;
                long long ans=r-n+1;
                //dp[make_pair(n,N)]=ans;
                dp.insert(make_pair(n,N),ans);
                //printf("%lld %lld %lld %d %d\n",p,N,ans,prime[n],prime[l]);
                return ans;
            }
            long long pn=p,ans=DP(n+1,N);
            for (int i=1;pn<=N;pn*=p*p,i++){
                if (pn==N) {ans++;break;}
                ans+=DP(n+1,N/pn);
            }
            //dp[make_pair(n,N)]=ans;
            dp.insert(make_pair(n,N),ans);
            //printf("%lld %lld %lld\n",p,N,ans);
            return ans;
        }
        long long count(long long N, int n) {
            //dp.clear();
            dp.init();
            for (int i=2;i<=n;i++){
                if (!fac[i]) fac[i]=prime[++*prime]=i;
                for (int x,j=1;j<=*prime&&(x=i*prime[j])<=n;j++) if ((fac[x]=prime[j])==fac[i]) break;
            }
            return DP(1,N);
        }
};

// CUT begin
ifstream data("HolyNumbers.sample");

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

bool do_test(long long upTo, int maximalPrime, long long __expected) {
    time_t startClock = clock();
    HolyNumbers *instance = new HolyNumbers();
    long long __result = instance->count(upTo, maximalPrime);
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
        long long upTo;
        from_stream(upTo);
        int maximalPrime;
        from_stream(maximalPrime);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(upTo, maximalPrime, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483287344;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "HolyNumbers (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
