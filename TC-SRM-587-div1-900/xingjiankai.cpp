#include <bits/stdc++.h>
using namespace std;
int n,m,mp[55][55],_mp[55][55],col[55];
vector<string> ans;
bool dfs(int u,int d)
{
    col[u]=d;
    for(int i=0;i<n;i++)
    if(mp[u][i]!=-1)
    {
        if(col[i]!=-1) 
        {
            if(col[i]==col[u]&&mp[u][i]==1) return 0;
            if(col[i]!=col[u]&&mp[u][i]==0) return 0;
        }
        else if(!dfs(i,d^mp[u][i])) return 0;
    }
    return 1;
}
bool check()
{
    memset(col,-1,sizeof(col));
    for(int i=0;i<n;i++) 
    if(col[i]==-1&&!dfs(i,0)) return 0;
    return 1;
}
class ThreeColorability
{
public:
    vector<string> lexSmallest(vector<string> s)
    {
        n=s.size(),m=s[0].length();
        memset(mp,-1,sizeof(mp));
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            for(int k=j+1;k<n;k++)
            if(s[j][i]!='?'&&s[k][i]!='?')
            {
                if(s[j][i]==s[k][i]) 
                {
                    if(mp[j][k]==1) return ans;
                    mp[j][k]=mp[k][j]=0;
                }
                else 
                {
                    if(mp[j][k]==0) return ans;
                    mp[j][k]=mp[k][j]=1;
                }
            }
        }
        //将确定关系的行连边，相同连0，不同连1.
        if(!check()) return ans;
        //判断是否有解
        for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        if(s[i][j]=='?')
        {
            bool flag=0;
            memcpy(_mp,mp,sizeof(mp));
            for(int k=0;k<n;k++)
            if(k!=i&&s[k][j]!='?')
            {
                if(s[k][j]=='N')
                {
                    if(mp[i][k]==1) {flag=1;break;}
                    mp[i][k]=mp[k][i]=0;
                }
                else 
                {
                    if(mp[i][k]==0) {flag=1;break;}
                    mp[i][k]=mp[k][i]=1;
                }
            }
            //试着填一个N并连边
            if(!flag&&check()) s[i][j]='N';
            else
            {
                memcpy(mp,_mp,sizeof(mp));
                s[i][j]='Z';
                for(int k=0;k<n;k++)
                if(k!=i&&s[k][j]!='?')
                {
                    if(s[k][j]=='Z') mp[i][k]=mp[k][i]=0;
                    else mp[i][k]=mp[k][i]=1;
                }
            	//不行的话恢复，再填Z，重新连边
            } 
        }
        return s;
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"Z"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"Z" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, lexSmallest(Arg0)); }
	void test_case_1() { string Arr0[] = {"??", "?N"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NN", "NN" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, lexSmallest(Arg0)); }
	void test_case_2() { string Arr0[] = {"ZZZ", "ZNZ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, lexSmallest(Arg0)); }
	void test_case_3() { string Arr0[] = {"N?N??NN","??ZN??Z","NN???Z?","ZZZ?Z??","Z???NN?","N?????N","ZZ?N?NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, lexSmallest(Arg0)); }
	void test_case_4() { string Arr0[] = {"ZZZZ","ZZZZ","ZZZZ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"ZZZZ", "ZZZZ", "ZZZZ" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, lexSmallest(Arg0)); }

// END CUT HERE
  
};  
  
// BEGIN CUT HERE  
int main()  
{  
ThreeColorability ___test;  
___test.run_test(-1);  
}  
// END CUT HERE 
