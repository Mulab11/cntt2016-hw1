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

class Ear {
    public:
        vector<int> trans(vector<string> a){
            vector<int> ans;
            for (int i=0,j=0;i<(int)a.size();){
                if ('0'<=a[i][j]&&a[i][j]<='9'){
                    int t=0;
                    for (;i<(int)a.size()&&'0'<=a[i][j]&&a[i][j]<='9';){
                        t=t*10+a[i][j]-'0';
                        j++;
                        if (j==(int)a[i].size()) i++,j=0;
                    }
                    ans.push_back(t);
                } else{
                    j++;
                    if (j==(int)a[i].size()) i++,j=0;
                }
            }
            return ans;
        }
        vector<int> a,x,y;
        double L[1005],R[1005];
        long long sum[100005];
        inline long long calc(int l,int r){return sum[r]-sum[l-1];}
        inline long long cross(int x1,int y1,int x2,int y2){return 1ll*x1*y2-1ll*x2*y1;}
        long long getCount(vector<string> redX, vector<string> blueX, vector<string> blueY) {
            a=trans(redX),x=trans(blueX),y=trans(blueY);
            long long ans=0;
            int n=a.size(),m=x.size();
            std::sort(a.begin(),a.end());
            memset(sum,0,sizeof(sum));
            for (int i=0;i<n;i++) sum[a[i]]++;
            for (int i=1;i<=100001;i++) sum[i]+=sum[i-1];
            for (int i=0;i<n;i++) for (int j=i+1;j<n;j++){
                for (int k=0;k<m;k++) if (a[i]<x[k]&&x[k]<a[j]) L[k]=atan2(y[k],x[k]-a[i]),R[k]=atan2(y[k],a[j]-x[k]);
                for (int k=0;k<m;k++) if (a[i]<x[k]&&x[k]<a[j]) for (int l=0;l<m;l++) if (a[i]<x[l]&&x[l]<a[j]&&y[l]<y[k]){
                    //printf("%d %d %d %d\n",i,j,k,l);
                    if (L[l]<L[k]&&R[l]<R[k]) ans+=calc(a[i]+1,x[l]-1)*calc(x[l]+1,a[j]-1);
                }
            }
            //return ans;
            ans=0;
            for (int i=0;i<n;i++) for (int k=0;k<m;k++) if (a[i]<x[k]) for (int l=0;l<m;l++) if (a[i]<x[l]&&y[l]<y[k]&&cross(x[l]-a[i],y[l],x[k]-a[i],y[k])>0){
                int t=lower_bound(a.begin(),a.end(),(int)max(x[k]+1.0,ceil(x[k]+1.0*(x[l]-x[k])/(y[k]-y[l])*y[k])))-a.begin();
                while (t<n&&cross(x[k]-a[t],y[k],x[l]-a[t],y[l])<=0) t++;
                if (t==n) continue;
                ans+=calc(a[i]+1,x[l]-1)*calc(x[l]+1,a[t]-1)*(n-t);
                t=n-t;
                ans+=calc(a[i]+1,x[l]-1)*(t*(t-1)>>1);
                //printf("%lld\n",ans);
            }
            return ans;
        }
};

// CUT begin
ifstream data("Ear.sample");

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

bool do_test(vector<string> redX, vector<string> blueX, vector<string> blueY, long long __expected) {
    time_t startClock = clock();
    Ear *instance = new Ear();
    long long __result = instance->getCount(redX, blueX, blueY);
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
        vector<string> redX;
        from_stream(redX);
        vector<string> blueX;
        from_stream(blueX);
        vector<string> blueY;
        from_stream(blueY);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(redX, blueX, blueY, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475238034;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Ear (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
