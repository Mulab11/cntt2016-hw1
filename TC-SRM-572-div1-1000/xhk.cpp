#include<bits/stdc++.h>
using namespace std;

struct unit
{int sta,x,l,r,val;
};
struct unit f[60],g[60];

int n,nc,pc,tot,ans;
int fa[60],used[60],c[60],d[60],w[60],w1[60];
char a[60],b[60];

bool operator <(unit A,unit B)
{return A.val<B.val;
}

int find(int i)
{return fa[i]==i?i:fa[i]=find(fa[i]);
}

void solve(int st)
{int i,j,k,k1,x,y,z,pre,s,s1,p,flag,f1;
 
 memset(used,0,sizeof(used));
 pre=0;
 i=st;
 k=0;
 k1=0;
 while(1)
 {	if(d[i]) w[++k1]=d[i];
 	if(c[i])
 	{	if(used[c[i]])
 		{	if(pre!=0 && pre!=c[i])
 				return;
	 		f[c[i]].r=i;
		}
		else
		{	f[c[i]].l=f[c[i]].r=i;
			used[c[i]]=1;
			//w1[c[i]]=++k;
			w1[++k]=c[i];
		}
		pre=c[i];
	}
	i=i+1;
	if(i>26) i-=26;
	if(i==st) break;
 }
 flag=1;
 for(i=1;i<=tot;i++)
 	if(w[i]!=w1[i])
 	{	flag=0;
 		break;
 	}
 //cout<<st<<" "<<(char)(st+96)<<endl;
 if(flag)
 {	s=0;
 	for(i=1;i<=tot;i++)
 	{	x=(f[i].l+26-st)%26+1;
 		y=(f[i].r+26-st)%26+1;
 		z=(f[i].x+26-st)%26+1;
 		//cout<<x<<" "<<y<<" "<<z<<endl;
 		if(z>=x && z<=y)
 		{	s+=nc*(z-x);
			s+=pc*(y-z);
		}
		else if(z<x)
			s+=pc*(y-z); 
		else
			s+=nc*(z-x);
 	}
 	if(ans==-1 || s<ans) ans=s;		
 }
 
 flag=0;
 for(i=1;i<=tot;i++)
 {	p=i;
 	flag=1;
 	for(j=1;j<=tot;j++)
 		if(w[j]!=w1[(j+p-1)%tot+1])
 		{	flag=0;
 			break;
 		}
 	if(flag) break;
 }
 //return;
 for(i=1;i<=tot;i++)
 {	g[i].l=(f[i].l+26-st)%26;
 	g[i].r=(f[i].r+26-st)%26;
 	g[i].x=(f[i].x+26-st)%26;
 	g[i].val=(f[i].l+26-st)%26;
 }
 sort(g+1,g+tot+1);
 if(flag && tot<26)
 {	
 	if(st==7)
 	{	for(i=1;i<=tot;i++)
 		{	x=(g[i].l+26-st)%26;
 			y=(g[i].r+26-st)%26;
 			z=(g[i].x+26-st)%26;
 		}
	}
 	s1=0;
 	for(i=1;i<=tot;i++) s1+=(g[i].r-g[i].l);
 	s=s1*nc;
 	flag=0;
 	i=1;
 	while(1)
 	{	if(g[i].r==g[i].x)
 		{	flag=1;
 			for(j=1;j<=tot;j++)
 			{	if(i==j) continue;
 				if((g[j].r<=g[i].x && (g[j].x<g[j].r || g[j].x>g[i].x)) || (g[j].r>g[i].x && (g[j].x>=g[i].x && g[j].x<g[j].r))) flag=0;
 			}
 		}
 		if(!flag)
 		{	g[i].r++;
 			if(g[i].r>=26) g[i].r-=26;
 			s+=nc;
 		}
		if(flag) break;
		//cout<<s<<endl;
		i++;
		if(i>tot) i-=tot;
	}
	for(i=1;i<=tot;i++)
		s+=nc*((g[i].x+26-g[i].r)%26);
 	if(ans==-1 || s<ans) ans=s;
 	
 	s=s1*pc;
 	i=1;
 	flag=0;
 	while(1)
 	{	if(g[i].l==g[i].x)
 		{	flag=1;
 			for(j=1;j<=tot;j++)
 			{	if(i==j) continue;
 				if((g[j].l<g[i].x && (g[j].x>g[j].l && g[j].x<g[i].x)) || (g[j].l>g[i].x && (g[j].x<=g[i].x || g[j].x>g[j].l))) flag=0;
 			}
 		}
 		if(!flag)
 		{	g[i].l--;
 			if(g[i].l<0) g[i].l+=26;
 			s+=pc;
 		}
 		if(flag) break;
 		i++;
 		if(i>tot) i-=tot;
 	}
 	for(i=1;i<=tot;i++)
 		s+=pc*((g[i].l+26-g[i].x)%26);
 	//cout<<st<<" "<<p<<" "<<s<<" "<<endl;	
 	if(ans==-1 || s<ans) ans=s;
 }
 
}
 	
class NextAndPrev
{	public:
	int getMinimum(int nextCost, int prevCost, string start, string goal)
	{	int i,j,k,fx,fy;
		
		nc=nextCost;
		pc=prevCost;
		n=start.length();
		for(i=1;i<=n;i++)
		{	a[i]=start[i-1];
			b[i]=goal[i-1];
		}
		for(i=1;i<=n;i++)
			for(j=i+1;j<=n;j++)
				if(a[i]==a[j] && b[i]!=b[j])
					return -1;
		for(i=1;i<=26;i++) fa[i]=i;
		for(i=1;i<=n;i++)
			for(j=i+1;j<=n;j++)
				if(b[i]==b[j])
				{	fx=find(a[i]-96);
					fy=find(a[j]-96);
					if(fx!=fy) fa[fx]=fy;
				}
		tot=0;		
		for(i=1;i<=26;i++)
		{	if(find(i)!=i) continue;		
			k=0;
			for(j=1;j<=n;j++)
				if(a[j]==96+i)
				{	k=j;
					break;
				}
			if(!k) continue;
			//cout<<k<<endl;
			tot++;
			f[tot].x=b[k]-96;
			f[tot].sta=0;
			for(j=1;j<=n;j++)
				if(find(a[j]-96)==i)
				{	f[tot].sta|=(1<<(a[j]-96));
					f[tot].l=min(f[tot].l,a[j]-96);
					f[tot].r=max(f[tot].r,a[j]-96);
				}
		}
		ans=-1;
		memset(c,0,sizeof(c));
 		for(i=1;i<=tot;i++)
 			for(j=1;j<=26;j++)
 				if(f[i].sta&(1<<j))
 					c[j]=i;
 		memset(d,0,sizeof(d));			
 		for(i=1;i<=tot;i++)
 			d[f[i].x]=i;
		//for(i=1;i<=tot;i++)
		//	cout<<f[i].l<<" "<<f[i].r<<" "<<f[i].x<<endl;	 	
		//for(i=1;i<=26;i++)
		//	cout<<c[i]<<" ";
		//cout<<endl;  			
		for(i=1;i<=26;i++) solve(i);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); if ((Case == -1) || (Case == 8)) test_case_8(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 55; int Arg1 = 654; string Arg2 = "jgjhgjggjhhghghhggjjgjjhhjgjjghgggjhgj"; string Arg3 = "rzrqzrzzrqqzqzqqzzrrzrrqqrzrrzqzzzrqzr"; int Arg4 = 4840; verify_case(0, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 1000; int Arg1 = 1000; string Arg2 = "abcdefghijklmnopqrstuvwxy"; string Arg3 = "nopqrstuvwxyzabcdefghijkl"; int Arg4 = 325000; verify_case(1, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 1; string Arg2 = "srm"; string Arg3 = "srm"; int Arg4 = 0; verify_case(2, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 1000; int Arg1 = 39; string Arg2 = "a"; string Arg3 = "b"; int Arg4 = 975; verify_case(3, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 123; int Arg1 = 456; string Arg2 = "pqrs"; string Arg3 = "abab"; int Arg4 = -1; verify_case(4, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arg0 = 100; int Arg1 = 19; string Arg2 = "topcoder"; string Arg3 = "ssszsffs"; int Arg4 = 676; verify_case(5, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_6() { int Arg0 = 1; int Arg1 = 1000; string Arg2 = "csk"; string Arg3 = "wog"; int Arg4 = 64; verify_case(6, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_7() { int Arg0 = 7; int Arg1 = 6; string Arg2 = "qwerty"; string Arg3 = "jjjjjj"; int Arg4 = 125; verify_case(7, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_8() { int Arg0 = 306; int Arg1 = 26; string Arg2 = "me"; string Arg3 = "ii"; int Arg4 = 572; verify_case(8, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	NextAndPrev ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
