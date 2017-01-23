// BEGIN CUT HERE

// END CUT HERE
#line 5 "YamanoteLine.cpp"
#include<bits/stdc++.h>
using namespace std;

const long long inf=1e12;

struct data
{long long x;
 long long y;
};
struct data dis[110];

struct edge
{int u,v,next;
 data c;
};
struct edge e[10010];

int n,num,flag;
int head[110];
long long d,L,R;

data operator +(data A,data B)
{return (data){A.x+B.x,A.y+B.y};
}

data operator -(data A,data B)
{return (data){A.x-B.x,A.y-B.y};
}

bool operator <(data A,data B)
{return A.x*d+A.y<B.x*d+B.y;
}

void add(int u,int v,data c)
{e[num].u=u;
 e[num].v=v;
 e[num].c=c;
 e[num].next=head[u];
 head[u]=num;
 num++;
}

int spfa()
{int j,i,q,f1=0;
 data s=(data){0,0};
 
 for(i=1;i<=n;i++) dis[i]=(data){0,1e18};
 dis[0]=(data){0,0};
 for(q=1;q<=n*n;q++)
 {	f1=0;
 	for(i=0;i<=n;i++)
 	{	j=head[i];
 		while(j!=-1)
 		{	if(dis[i]+e[j].c<dis[e[j].v])
 			{	dis[e[j].v]=dis[i]+e[j].c;
 				if(dis[e[j].v].y+dis[e[j].v].x*d<0) 
				{	if(dis[e[j].v].x==0) flag=0;
					//if(dis[e[j].v].x==0) cout<<"###"<<endl;
					return dis[e[j].v].x>=0?0:2;
				}
				s=dis[e[j].v];
				f1=1;
 			}
 			j=e[j].next;
 		}
 	}
 	if(!f1) break;
 }

 if(f1) return s.x>=0?0:2;
 return 1;
}

class YamanoteLine
{	public:
	long long howMany(int N, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2)
	{	int i,j,f1;
	 	long long l,r,mid;
	 	
	 	n=N;
	 	
	 	//cout<<n<<endl;
	 	flag=1;
	 	num=0;
	 	memset(head,-1,sizeof(head));
	 	for(i=0;i<s1.size();i++)
	 		if(s1[i]<t1[i])
	 			add(t1[i],s1[i],(data){0,-l1[i]});
	 		else if(s1[i]>t1[i])
	 			add(t1[i],s1[i],(data){1,-l1[i]});
	 	for(i=0;i<s2.size();i++)
		 	if(s2[i]<t2[i])
			 	add(s2[i],t2[i],(data){0,l2[i]});
			else if(s2[i]>t2[i])
				add(s2[i],t2[i],(data){-1,l2[i]});
		for(i=1;i<=n;i++)
			add(i,i-1,(data){0,-1});
		add(0,n,(data){1,0});
		add(n,0,(data){-1,0});
		
		//for(i=0;i<num;i++) cout<<e[i].u<<" "<<e[i].v<<" "<<e[i].c.x<<" "<<e[i].c.y<<endl;
		
	 	l=0;
	 	r=inf;
	 	L=inf+1;
	 	while(l<=r)
	 	{	mid=(l+r)/2;
	 		d=mid;
	 		if(spfa()>=1)
	 		{	L=min(L,mid);
	 			r=mid-1;
	 		}
	 		else
	 			l=mid+1;
	 	}
	 	l=0;
	 	r=inf;
	 	R=0;
	 	while(l<=r)
	 	{	mid=(l+r)/2;
	 		d=mid;
	 		if(spfa()<=1)
	 		{	R=max(R,mid);
	 			l=mid+1;
	 		}
	 		else
	 			r=mid-1;
	 	}
	 	if(R==inf && spfa()==1) return -1;
	
	 	//cout<<L<<" "<<R<<endl;		 				 	 	
	 	return R-L+1;
	}
				 	 	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6();  if ((Case == -1) || (Case == 7)) test_case_7();}
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {0,1,2}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {1,2,0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {1,1,1}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = 1LL; verify_case(0, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_1() { int Arg0 = 3; int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {0,1,2}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {1,2,0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {2,2,2}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = 4LL; verify_case(1, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_2() { int Arg0 = 3; int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {0,1,2}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {2,0,1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {3,3,3}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = 2LL; verify_case(2, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_3() { int Arg0 = 4; int Arr1[] = {0,1,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,3,0,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3,4,4,3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1,3}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {3,1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {5,5}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = 4LL; verify_case(3, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_4() { int Arg0 = 4; int Arr1[] = {0,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {5,5}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1,3}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {3,1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {4,4}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = 0LL; verify_case(4, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_5() { int Arg0 = 5; int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {0,2}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {2,4}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {2,2}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = -1LL; verify_case(5, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_6() { int Arg0 = 10; int Arr1[] = {5,7,2,3,9,4,6,0,4,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,8,3,9,8,0,8,7,1,7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {61,54,20,64,25,73,83,79,86,56}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {4,5,4,0,8,3,8,5,5,9}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {5,2,0,1,1,4,7,6,8,3}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {1951,6102,3625,5737,1590,1228,9234,1342,9060,1008}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = 5726LL; verify_case(6, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_7() { int Arg0 = 41; int Arr1[] = {26, 32, 2, 40, 30, 31, 32, 30, 10, 24, 35, 25, 2, 7, 15, 31, 29, 5, 6, 37, 34, 27, 14, 27, 40, 20, 13, 38, 6, 38, 13, 10, 34, 10, 20, 6, 27, 22, 40, 23}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {32, 23, 7, 28, 3, 20, 0, 2, 6, 6, 7, 14, 37, 8, 40, 20, 5, 2, 32, 36, 36, 18, 12, 40, 11, 26, 37, 32, 33, 17, 19, 14, 37, 39, 10, 5, 10, 10, 15, 27}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1673508, 8172540, 1555291, 8354930, 3641184, 7614552, 2023472, 3124394, 10425705, 6550720, 3498956, 7789224, 9803018, 197011, 7452117, 7615122, 4481254, 10123840, 7252802, 10790451, 298220, 7768707, 10398364, 3220137, 2809348, 2316185, 7163394, 9624368, 7391379, 4809664, 1644479, 1006582, 690392, 8322143, 8671928, 11005488, 5925940, 8085678, 3728513, 1760987}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {19, 0, 32, 29, 38, 23, 14, 31, 12, 24, 24, 16, 18, 26, 14, 17, 31, 9, 36, 5, 0, 24, 5, 27, 33, 27, 5, 7, 21, 27, 39, 4, 20}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {24, 2, 26, 4, 25, 17, 28, 27, 32, 36, 36, 33, 39, 20, 18, 32, 10, 16, 22, 26, 25, 3, 21, 39, 29, 16, 38, 40, 9, 33, 33, 32, 36}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {1576473, 671279, 9508663, 4066329, 7527385, 9374779, 4645028, 10364416, 6274992, 3551443, 3551605, 5146885, 6482132, 8864476, 834828, 4817342, 5109635, 1614562, 6850475, 5755501, 7056775, 5835926, 3826157, 3068928, 10313816, 7421434, 8986685, 8907528, 8166257, 1384195, 9497363, 7846757, 4920822}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); long long Arg7 = 2496LL; verify_case(7, Arg7, howMany(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	YamanoteLine ___test;
	___test.run_test(-1);
	/*
	cout<<___test.howMany(41, 
	{26, 32, 2, 40, 30, 31, 32, 30, 10, 24, 35, 25, 2, 7, 15, 31, 29, 5, 6, 37, 34, 27, 14, 27, 40, 20, 13, 38, 6, 38, 13, 10, 34, 10, 20, 6, 27, 22, 40, 23}
	{32, 23, 7, 28, 3, 20, 0, 2, 6, 6, 7, 14, 37, 8, 40, 20, 5, 2, 32, 36, 36, 18, 12, 40, 11, 26, 37, 32, 33, 17, 19, 14, 37, 39, 10, 5, 10, 10, 15, 27}
	{1673508, 8172540, 1555291, 8354930, 3641184, 7614552, 2023472, 3124394, 10425705, 6550720, 3498956, 7789224, 9803018, 197011, 7452117, 7615122, 4481254, 10123840, 7252802, 10790451, 298220, 7768707, 10398364, 3220137, 2809348, 2316185, 7163394, 9624368, 7391379, 4809664, 1644479, 1006582, 690392, 8322143, 8671928, 11005488, 5925940, 8085678, 3728513, 1760987}
	{19, 0, 32, 29, 38, 23, 14, 31, 12, 24, 24, 16, 18, 26, 14, 17, 31, 9, 36, 5, 0, 24, 5, 27, 33, 27, 5, 7, 21, 27, 39, 4, 20}
	{24, 2, 26, 4, 25, 17, 28, 27, 32, 36, 36, 33, 39, 20, 18, 32, 10, 16, 22, 26, 25, 3, 21, 39, 29, 16, 38, 40, 9, 33, 33, 32, 36}
	{1576473, 671279, 9508663, 4066329, 7527385, 9374779, 4645028, 10364416, 6274992, 3551443, 3551605, 5146885, 6482132, 8864476, 834828, 4817342, 5109635, 1614562, 6850475, 5755501, 7056775, 5835926, 3826157, 3068928, 10313816, 7421434, 8986685, 8907528, 8166257, 1384195, 9497363, 7846757, 4920822})<<endl;
	*/
	return 0;
}
// END CUT HERE
