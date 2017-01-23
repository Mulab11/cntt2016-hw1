// BEGIN CUT HERE

// END CUT HERE
//#line 5 "UndoHistory.cpp"
#include<bits/stdc++.h>
using namespace std;
#include <set>
#include <string>

int ans;

class UndoHistory
{	
	public:
	int minPresses(vector <string> lines)
	{	int i,j,k;
		int bs=0,hs=0;
		
		set<string> h;  
		h.insert(""); 
		string b="";
		 		
		ans=0;
		for(i=0;i<lines.size();i++)
		{	bs=b.size();  
			hs=0;  
			for(j=lines[i].size();j>=1;j--)
				if(!h.insert(lines[i].substr(0,j)).second)
				{  	hs=j;  
					break;  
				}  
			if(hs<bs+2 && b==lines[i].substr(0,bs)) //·ÖÀàÌÖÂÛ 
			{	ans+=lines[i].size()-bs+1;  
				for(j=bs+1;j<=lines[i].size();j++)  
					h.insert(lines[i].substr(0,j));
			}   
			else if(hs>0)
			{	ans+=lines[i].size()-hs+3;  
				for(j=hs+1;j<=lines[i].size();j++)
					h.insert(lines[i].substr(0,j));
			}   
			else
			{	ans+=lines[i].size()+3;
				for(j=1;j<=lines[i].size();j++)  
					h.insert(lines[i].substr(0,j));  
			}  
			b=lines[i];  
		}    
		return ans;  
    } 
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"tomorrow", "topcoder"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 18; verify_case(0, Arg1, minPresses(Arg0)); }
	void test_case_1() { string Arr0[] = {"a","b"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(1, Arg1, minPresses(Arg0)); }
	void test_case_2() { string Arr0[] = {"a", "ab", "abac", "abacus" }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(2, Arg1, minPresses(Arg0)); }
	void test_case_3() { string Arr0[] = {"pyramid", "sphinx", "sphere", "python", "serpent"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 39; verify_case(3, Arg1, minPresses(Arg0)); }
	void test_case_4() { string Arr0[] = {"ba","a","a","b","ba"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; verify_case(4, Arg1, minPresses(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	UndoHistory ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
