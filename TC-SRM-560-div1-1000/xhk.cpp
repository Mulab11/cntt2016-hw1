// BEGIN CUT HERE

// END CUT HERE
#line 5 "BoundedOptimization.cpp"
#include<bits/stdc++.h>
using namespace std;

const double eps=1e-6;
int n;
int ga[20][20];
double lim,ans;
double b[20],L[20],R[20];
string a;

void check()
{int i,j;
 double s;
 
 s=0;
 for(i=0;i<n;i++)
 {	if(b[i]<L[i] || b[i]>R[i]) return;
 	s+=b[i];
 }
 if(s>lim+eps) return;
 s=0;
 for(i=0;i<n;i++)
 	for(j=i+1;j<n;j++)
 		if(ga[i][j]) s+=b[i]*b[j];
 ans=max(ans,s);
}

class BoundedOptimization
{	public:
	double maxValue(vector <string> expr, vector <int> lowerBound, vector <int> upperBound, int maxSum)
	{	int i,j,k,p,i1,cnt;
		double s1,s2,s;
		
		a="";
		lim=maxSum;
		for(i=0;i<expr.size();i++) a+=expr[i];
		memset(ga,0,sizeof(ga));
		for(i=0;i+1<a.length();i+=3)
		{	ga[a[i]-97][a[i+1]-97]=1;
			ga[a[i+1]-97][a[i]-97]=1;
		}
		n=lowerBound.size();
		for(i=0;i<n;i++)
	 	{	L[i]=lowerBound[i];
		 	R[i]=upperBound[i];
		}
		s=0;
		for(i=0;i<n;i++) s+=R[i];
		if(s<lim) lim=s;
		ans=0;
		for(i=0;i<(1<<n);i++)
			for(j=i;j>=0;j=(j-1)&i)
			{	//cout<<i<<" "<<j<<" "<<((j-1)&i)<<endl;
				s=lim;
				for(k=0;k<n;k++)
					if(i&(1<<k))
					{	if(j&(1<<k))
						{	b[k]=L[k];
							s-=L[k];
						}
						else
						{	b[k]=R[k];
							s-=R[k];
						}
					}
				p=-1;	
				for(k=0;k<n;k++)
					if((i&(1<<k))==0)
					{	p=k;
						break;
					}
				if(p!=-1)
				{	cnt=1;	
					s1=0;
					for(k=0;k<n;k++)
						if((i&(1<<k)) && ga[p][k]) s1+=b[k];
					for(k=p+1;k<n;k++)	
					{	if(i&(1<<k)) continue;
						s2=0;
						for(i1=0;i1<n;i1++)
							if((i&(1<<i1)) && ga[i1][k])
								s2+=b[i1];
						s+=s1-s2;
						cnt++;
					}
					for(k=p;k<n;k++)
					{	if(i&(1<<k)) continue;
						s2=0;
						for(i1=0;i1<n;i1++)
							if((i&(1<<i1)) && ga[i1][k])
								s2+=b[i1];
						b[k]=s/cnt+s2-s1;
					}
				}
				check();
				if(j==0) break;
			}	
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"ba+cb"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; double Arg4 = 2.25; verify_case(0, Arg4, maxValue(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arr0[] = {"ab"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {20, 20, 20}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 12; double Arg4 = 1.0; verify_case(1, Arg4, maxValue(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arr0[] = {"ca+fc+fa+d","b+da+","dc+c","b","+ed+eb+ea"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10,11,12,13,14,15}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {15,16,17,18,19,20}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 85; double Arg4 = 2029.25; verify_case(2, Arg4, maxValue(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { string Arr0[] = {"db+ea+ik+kh+je+","fj+lk+i","d+jb+h","a+gk+mb+ml+lc+mh+cf+fd+","gc+ka+gf+bh+mj+eg+bf+hf+l","b+al+ja+da+i",
"f+g","h+ia+le+ce+gi+d","h+mc+fe+dm+im+kb+bc+","ib+ma+eb+mf+jk+kc+mg+mk+","gb+dl+ek+hj+dg+hi","+ch+ga+ca+fl+ij+fa+jl+dc+dj+fk","+li+jg"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {57,29,50,21,49,29,88,33,84,76,95,55,11}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {58,80,68,73,52,84,100,79,93,98,95,69,97}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 845; double Arg4 = 294978.3333333333; verify_case(3, Arg4, maxValue(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	BoundedOptimization ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
