// BEGIN CUT HERE

// END CUT HERE
#line 5 "WallGameDiv1.cpp"
#include<bits/stdc++.h>
using namespace std;

//增强限制如果一个人经过了一个格子而没有选择从这个格子往下一行，那么之后经过这个格子也不能从这里往下一行走。 

const int inf=1e9;
int n,m,ans;
int a[110][110],b[110],s[110],f[110],g[110][110][110],h[110];

int calc(int i,int l,int r) //记忆化搜索求出g[i][l][r]表示当前在i,l~r已被堵住的最优方案。 
{int j,s1,ret;
 
 if(i<=0 || i>m) return g[i][l][r]=inf;
 if(g[i][l][r]!=-1) return g[i][l][r];
 if(!l)
 {	s1=inf;
 	if(i>1) s1=min(s1,calc(i-1,i,i));
 	if(i<m) s1=min(s1,calc(i+1,i,i));
 	ret=b[i]+max(f[i],s1);
 	//ret=b[i]+max(f[i],min(calc(i-1,i,i),calc(i+1,i,i)));
 }
 else if(i<l)
 {	if(i==1 && l==2 && r==m)
 		ret=b[i]+f[i];
 	else
 	{	s1=inf;
 		if(i>1) s1=min(s1,calc(i-1,i,r));
 		if(r<m) s1=min(s1,s[r]-s[i]+calc(r+1,i,r));
	 	//ret=b[i]+max(f[i],min(calc(i-1,i,r),r<m?(s[r]-s[i]+calc(r+1,i,r)):inf));
	 	ret=b[i]+max(f[i],s1);
	}
 }
 else if(i>r)
 {	if(i==m && l==1 && r==m-1)
 		ret=b[i]+f[i];
 	else
 	{	s1=inf;
 		if(i<m) s1=min(s1,calc(i+1,l,i));
 		if(l>1) s1=min(s1,s[i-1]-s[l-1]+calc(l-1,l,i));
 		ret=b[i]+max(f[i],s1);
	 	//ret=b[i]+max(f[i],min(calc(i+1,l,i),l>1?(s[i-1]-s[l-2]+calc(l-1,l,i)):inf));
	}
 }
 g[i][l][r]=ret;
 return ret;
}	

void work(int p)
{int i,j;
 
 memset(g,-1,sizeof(g));
 for(i=1;i<=m;i++) h[i]=calc(i,0,0);
 for(i=1;i<=m;i++) f[i]=h[i];
}

class WallGameDiv1
{	public:
	int play(vector <string> costs)
	{	int i,j;
		
		n=costs.size();
		m=costs[0].length();
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				a[i][j]=costs[i-1][j-1]-48;
		if(m==1)
		{	ans=0;
			for(i=1;i<=n;i++) ans+=a[i][1];
			return ans;
		}
		for(i=1;i<=m;i++) f[i]=a[n][i];
		for(i=n-1;i>=1;i--) //从最后一行开始倒推dp值 
		{	for(j=1;j<=m;j++)
			{	b[j]=a[i][j];
				s[j]=s[j-1]+b[j];
			}
			work(i);
		}
		ans=inf;
		for(i=1;i<=m;i++) ans=min(ans,f[i]);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"12"
,"34"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(0, Arg1, play(Arg0)); }
	void test_case_1() { string Arr0[] = {"99999"
,"99999"
,"99999"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 99; verify_case(1, Arg1, play(Arg0)); }
	void test_case_2() { string Arr0[] = {"11111"
,"90005"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(2, Arg1, play(Arg0)); }
	void test_case_3() { string Arr0[] = {"4417231387449337370319219832088987579792"
,"3117295688208899006196193430472892512797"
,"0835796222361526836944954410684516919758"
,"1988200069973565052900745230547016216225"
,"8080511471118865780390486996601082102418"
,"4229084185957675819725844582167613108400"
,"9068653877952162764545674979144308771754"
,"8551565425951612499712254182109991511690"
,"7090525592007482152807163656647658543093"
,"9198968742256995592729889137556032960142"
,"2071864379877766468141740053503050313101"
,"1055375249261868472993219156394129253481"
,"2461178270502857106406495509025426298874"
,"8216781259733537757203421037984512664825"
,"4693452554407216935375049784445568498482"
,"2709693439640250842244170297203200674391"
,"5122217695676372684217182241705137947908"
,"6668814191410691246849638388008228444294"
,"4952122070212780440963814752538149378639"
,"9827737761436134120332969866554332504400"
,"3412406588339828249986707470540386748886"
,"7521506848088506994554600408372456405830"
,"1916926179183007872881163173153907665999"
,"6636166791472761992310264951474925339024"
,"6679667717747231380196787943691121008076"
,"3218993234115685151069259138068533004433"
,"4920152552986426962081492913852060211795"
,"0365186235986445521382132973036266396894"
,"3205351414936828189305188614651974318855"
,"3144278971529524658788277656125598825426"
,"5525287537572356662391582052968411726245"
,"2130137226726919525622574701068062252930"
,"2369996694245544770519574837226971226841"
,"6806769058165410189286521891570936341547"
,"0448109211631660241710734664066810078242"
,"4622919135804954122810530631429501069659"
,"0235247446548732490429856705369583140671"
,"2193399741215975228987754171460722199304"
,"1203037020703833716225328076959743850915"
,"5419885193880826109484912489603262199432"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7366; verify_case(3, Arg1, play(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	WallGameDiv1 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
