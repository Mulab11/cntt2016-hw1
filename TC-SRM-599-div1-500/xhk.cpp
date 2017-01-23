// BEGIN CUT HERE

// END CUT HERE
#line 5 "FindPolygons.cpp"
#include<bits/stdc++.h>
using namespace std;

struct point
{int x,y,z;
};
struct point a[100010];

int l,n;
double ans;

bool operator <(point p1,point p2)
{return p1.x>p2.x;
}

class FindPolygons
{	public:
	double minimumPolygon(int L)
	{	int i,j,s1,s2,s3,k,ma,mi;
		
		l=L;
		if(l==2 || l%2==1) return -1;
		for(i=0;i<=l/2;i++)
			for(j=0;j<=l/2;j++)
				if((i || j) && i*i+j*j<=l*l/4)
				{	k=(int)sqrt(i*i+j*j);
					if(k*k==i*i+j*j)
					{	a[++n]=(point){i,j,k};
						if(i) a[++n]=(point){-i,j,k};
					}
				}
		//cout<<n<<endl;	
		sort(a+1,a+n+1);	
		ans=-1;		
		for(i=1;i<=n;i++)
		{	if(a[i].x<=0) break;
			for(j=i+1;j<=n;j++)
			{	if(a[i].x*a[j].y-a[j].x*a[i].y==0) continue;
				//s1=(int)sqrt(a[i].x*a[i].x+a[i].y*a[i].y);
				//s2=(int)sqrt(a[j].x*a[j].x+a[j].y*a[j].y);
				s1=a[i].z;
				s2=a[j].z;
				s3=(a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y);
				k=(int)sqrt(s3);
				if(k*k==s3 && s1+s2+k==l)
				{	if(s1>=s2 && s1>=k)
						ma=s1;
					else if(s2>=s1 && s2>=k)
						ma=s2;
					else
						ma=s3;
					if(s1<=s2 && s1<=k)
						mi=s1;
					else if(s2<=s1 && s2<=k)
						mi=s2;
					else
						mi=k;	
					//cout<<s1<<" "<<s2<<" "<<s3<<" "<<k<<" ## "<<a[i].x<<" "<<a[i].y<<" "<<a[j].x<<" "<<a[j].y<<endl;	
					if(ans==-1 || ma-mi<ans)	
					{	ans=ma-mi;
						//cout<<s1<<" "<<s2<<" "<<s3<<" "<<k<<" ## "<<a[i].x<<" "<<a[i].y<<" "<<a[j].x<<" "<<a[j].y<<endl;	
					}
				}
			}
		}
		//cout<<ans<<endl;	
		if(ans==-1) ans=l%4==0?0:1;
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; double Arg1 = 0.0; verify_case(0, Arg1, minimumPolygon(Arg0)); }
	void test_case_1() { int Arg0 = 5; double Arg1 = -1.0; verify_case(1, Arg1, minimumPolygon(Arg0)); }
	void test_case_2() { int Arg0 = 12; double Arg1 = 2.0; verify_case(2, Arg1, minimumPolygon(Arg0)); }
	void test_case_3() { int Arg0 = 4984; double Arg1 = 819.0; verify_case(3, Arg1, minimumPolygon(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	FindPolygons ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
