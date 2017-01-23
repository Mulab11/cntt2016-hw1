// BEGIN CUT HERE

// END CUT HERE
#line 5 "UnknownTree.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
typedef vector<int> VI;
const int mod=1000000009;
int n,tot,ans;
int a[110],b[110],c[110];
map<int,VI> ha,hb,hc;
VI h,w;
pair<int,int> sa[1010];

int fpow(int i,int j)
{int ret=1;
 for(;j;i=(ll)i*i%mod,j/=2)
 	if(j&1) ret=(ll)ret*i%mod;
 return ret;
}

int calc(VI &A)
{int i,last,ret=1;
 
 sort(A.begin(),A.end());
 for(i=0;i<A.size();i=last+1)
 {	last=i;
 	while(last+1<A.size() && A[last+1]==A[i]) last++;
 	if(i!=0)
 		ret=(ll)ret*fpow(i,last-i+1)%mod;
 }
 if(A[0]!=0 || (A.size()>1 && A[1]==0)) return 0;
 return ret;
}

void check_y(int root,int x,int y,int z)
{int i,j,k,f1,f2,f3,s;
 map<int,VI>::iterator p;
 
 ha.clear();
 hb.clear();
 hc.clear();
 h.clear();
 ha[0].push_back(0);
 hb[0].push_back(0);
 hc[0].push_back(0);
 h.push_back(0);
 for(i=1;i<=n;i++)
 	if(i!=root)
 	{	f1=(b[i]-c[i]==y-z);
 		f2=(a[i]-c[i]==x-z);
 		f3=(a[i]-b[i]==x-y);
 		if(f1 && f2 && f3)
 		{	if(a[i]==x) return;
		 	h.push_back(a[i]-x);
		}
		else if(f1 && (!f2 && !f3))
		{	if((x+y-a[i]+b[i])%2!=0) return;
			k=(x+y+a[i]-b[i])/2;
			if(k>=x) return;
			ha[k].push_back(a[i]-k);
		}
		else if(f2 && (!f1 && !f3))
		{	if((y+z-b[i]+c[i])%2!=0) return;
			k=(y+z+b[i]-c[i])/2;
			if(k>=y) return;
			hb[k].push_back(b[i]-k);
		}
		else if(f3 && (!f1 && !f2))
		{	if((z+x-c[i]+a[i])%2!=0) return;
			k=(z+x+c[i]-a[i])/2;
			if(k>=z) return;
			hc[k].push_back(c[i]-k);
		}
		else
			return;
	}

 //cout<<"alive"<<endl;	
 s=calc(h);
 for(p=ha.begin();p!=ha.end();p++) s=(ll)s*calc((*p).second)%mod;
 for(p=hb.begin();p!=hb.end();p++) s=(ll)s*calc((*p).second)%mod;
 for(p=hc.begin();p!=hc.end();p++) s=(ll)s*calc((*p).second)%mod;	 	
 ans=(ans+s)%mod;
 
 //cout<<root<<" "<<ans<<endl;
}

void check_chain(int A[],int B[],int C[],int x,int y)
{int i,j,k,s,f1,f2,f3;
 map<int,VI>::iterator p;
 
 //cout<<x<<" "<<y<<endl;
 
 h.clear();
 ha.clear();
 hc.clear();
 ha[0].push_back(0);
 hc[0].push_back(0);
 h.push_back(0);
 for(i=1;i<=n;i++)
 {	f1=(C[i]-B[i]==y);
 	f2=(A[i]-B[i]==x);
 	f3=(A[i]-C[i]==x-y);
 	if(f3 && f1 && f2)
 	{	if(B[i]==0) return;
 		h.push_back(B[i]);
 	}
 	else if(f1 && (!f2 && !f3))
 	{	if((x+A[i]-B[i])%2!=0) return;
 		k=(x+A[i]-B[i])/2;
 		if(k>=x) return;
 		ha[k].push_back(A[i]-k);
 	}
 	else if(f2 && (!f1 && !f3))
 	{	if((y+C[i]-B[i])%2!=0) return;
 		k=(y+C[i]-B[i])/2;
 		if(k>=y) return;
 		hc[k].push_back(C[i]-k);
 	}
 	else
 		return;
 }
 s=calc(h);
 //if(x==3 && y==1) cout<<"## "<<s<<" "<<h.size()<<" "<<h[0]<<" "<<h[1]<<" "<<h[2]<<".. "<<A[1]<<" "<<B[1]<<" "<<C[1]<<" "<<endl;
 for(p=ha.begin();p!=ha.end();p++) s=(ll)s*calc((*p).second)%mod;
 for(p=hc.begin();p!=hc.end();p++) s=(ll)s*calc((*p).second)%mod;	 	
 ans=(ans+s)%mod;
}

void work(int A[],int B[],int C[])
{int i,j,k;
 
 tot=0;
 for(i=1;i<=n;i++)
 {	sa[++tot]=make_pair(A[i]-B[i],C[i]-B[i]);
 	sa[++tot]=make_pair(A[i]-B[i],B[i]+C[i]);
 	sa[++tot]=make_pair(A[i]+B[i],C[i]-B[i]);
 	sa[++tot]=make_pair(B[i]-A[i],C[i]-B[i]);
 	sa[++tot]=make_pair(A[i]-B[i],B[i]-C[i]);
 }
 sort(sa+1,sa+tot+1);
 for(i=1;i<=tot;i++)
 	if((i==1 || sa[i]!=sa[i-1]) && sa[i].first>0 && sa[i].second>0)
 	{	//cout<<i<<" "<<sa[i].first<<" "<<sa[i].second<<endl;
	 	check_chain(A,B,C,sa[i].first,sa[i].second);
	 	//cout<<ans<<endl;
	}
}

class UnknownTree
{	public:
	int getCount(vector <int> distancesA, vector <int> distancesB, vector <int> distancesC)
	{	int i,j;
		
		n=distancesA.size();
		for(i=1;i<=n;i++) a[i]=distancesA[i-1];
		for(i=1;i<=n;i++) b[i]=distancesB[i-1];
		for(i=1;i<=n;i++) c[i]=distancesC[i-1];
		
		ans=0;
		for(i=1;i<=n;i++) check_y(i,a[i],b[i],c[i]);
		
		//cout<<"## "<<n<<" "<<ans<<endl;
		
		work(a,b,c);
		//cout<<ans<<endl;
		
		//return 0;
		work(b,a,c);
		//cout<<ans<<endl;
		work(a,c,b);
		//cout<<ans<<endl;
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 6; verify_case(0, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(1, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {5, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 8; verify_case(2, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {2, 4, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {4, 6, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(3, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {4, 6, 1, 5, 3, 2, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 2, 3, 1, 3, 2, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {5, 7, 2, 6, 4, 3, 6}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 12; verify_case(4, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {6, 4, 5, 6, 8, 1, 5, 6, 4, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 2, 3, 4, 6, 1, 3, 4, 2, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {6, 4, 5, 6, 8, 3, 5, 6, 4, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 9000; verify_case(5, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_6() { int Arr0[] = {8, 5, 6, 8, 6, 5, 6, 10, 8, 5, 10, 8, 7, 9, 7, 1, 11, 5, 9, 6, 6, 1, 6, 9, 8, 4, 12, 7, 5, 7, 6, 8, 12, 8, 6, 6, 5, 8, 5, 3, 3, 4, 8, 6, 6, 8, 8, 9, 7, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {9, 6, 7, 9, 7, 6, 7, 11, 9, 6, 11, 9, 8, 10, 8, 2, 12, 6, 10, 7, 7, 4, 7, 10, 9, 5, 13, 8, 6, 8, 7, 9, 13, 9, 7, 7, 6, 9, 6, 4, 4, 5, 9, 7, 7, 9, 9, 10, 8, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {8, 9, 6, 8, 2, 5, 6, 10, 8, 5, 10, 8, 7, 9, 1, 5, 11, 5, 9, 6, 6, 7, 6, 9, 8, 4, 12, 7, 5, 7, 6, 8, 12, 8, 6, 6, 5, 8, 1, 7, 3, 4, 8, 6, 6, 8, 8, 3, 7, 5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 770724166; verify_case(6, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_7() { int Arr0[] = {33030780, 30296205, 16842859, 28857842, 37928939, 27190807, 48689043, 33328845, 24254103, 3962046,
31043603, 25699520, 11297547, 27045586, 31603483, 23207518, 44089781, 48470539, 52366295, 39786470,
45623279, 21593844, 38639305, 27260993, 43899542, 36162768, 21640232, 43580853, 33826577, 30501815,
51470990, 2157904, 27823597, 9550575, 39234641, 24163007, 34155133, 42504989, 35821444, 36054200,
29026389, 29716374, 41764139, 19392309, 44258194, 19987908, 56722905, 46771885, 32668277, 40665175}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {16191697, 13457122, 3776, 12018759, 21089856, 10351724, 31849960, 16489762, 7415020, 12877037,
14204520, 8860437, 9035480, 10206503, 14764400, 6368435, 27250698, 31631456, 35527212, 22947387,
28784196, 4754761, 21800222, 10421910, 27060459, 19323685, 4801149, 26741770, 16987494, 13662732,
34631907, 18996987, 10984514, 7288508, 22395558, 7323924, 17316050, 25665906, 18982361, 19215117,
12187306, 12877291, 24925056, 2553226, 27419111, 3148825, 39883822, 29932802, 15829194, 23826092}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {19337227, 16602652, 3149306, 15164289, 24235386, 13497254, 34995490, 19635292, 10560550, 16030119,
17350050, 12005967, 12188562, 13352033, 17909930, 3215353, 30396228, 34776986, 38672742, 26092917,
31929726, 7907843, 24945752, 13567440, 30205989, 22469215, 7946679, 29887300, 20133024, 16808262,
37777437, 22150069, 14130044, 10441590, 25541088, 10469454, 20461580, 28811436, 22127891, 22360647,
15332836, 16022821, 28070586, 5706308, 30564641, 6294355, 43029352, 33078332, 18974724, 26971622}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 101733071; verify_case(7, Arg3, getCount(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	UnknownTree ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
