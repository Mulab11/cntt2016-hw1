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

class FoxAndHandle {
    public:
    	int c[26],tag[26];
    	string lexSmallestName(string S) {
    		memset(c,0,sizeof(c));
    		int n=S.size();
            for (int i=0;i<n;i++) c[S[i]-'a']++;
            for (int i=0;i<26;i++) tag[i]=c[i]>>1;
            string ansstr;
            for (int kase=n>>1,now=0;kase--;now++){
                int ans=-1;
                for (int i=now;i<n;i++) if (tag[S[i]-'a']){
                    memset(c,0,sizeof(c));
                    for (int j=i+1;j<n;j++) c[S[j]-'a']++;
                    int ok=1;
                    tag[S[i]-'a']--;
                    //for (int j=0;j<26;j++) if (c[j]||tag[j]) printf("%s %d %c %d %d\n",ansstr.c_str(),i,j+'a',c[j],tag[j]);
                    for (int j=0;j<26;j++) if (c[j]<tag[j]) ok=0;
                    tag[S[i]-'a']++;
                    if (!ok) continue;
                    //printf("ok %d\n",i);
                    if (ans<0||S[i]<S[ans]) ans=i;
                }
                now=ans;
                //printf("%d\n",now);
                ansstr+=S[now];
                tag[S[now]-'a']--;
            }
        	return ansstr;
    	}
};

// CUT begin
ifstream data("FoxAndHandle.sample");

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

bool do_test(string S, string __expected) {
    time_t startClock = clock();
    FoxAndHandle *instance = new FoxAndHandle();
    string __result = instance->lexSmallestName(S);
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
        string S;
        from_stream(S);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484325777;
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
        cout << "FoxAndHandle (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
