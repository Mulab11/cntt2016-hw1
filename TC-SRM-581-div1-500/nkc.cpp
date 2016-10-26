#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 601
using namespace std;
struct Tree
{
	int n,to[N],nxt[N],pre[N],cnt;
	string s;
	Tree(){n=0;s="";cnt=0;memset(pre,0,sizeof(pre));}
	void ae(int ff,int tt)
	{
		cnt++;
		to[cnt]=tt;
		nxt[cnt]=pre[ff];
		pre[ff]=cnt;
	}
	void AE(int ff,int tt)
	{
		ae(ff,tt);
		ae(tt,ff);
	}
	void predo()
	{
		int len=s.size(),num=0;
		int i,j;
		for(i=0;i<len;i++)
		{
			if(s[i]==' ') n++,AE(num,n),num=0;
			else num=num*10+s[i]-48;
		}
		n++,AE(num,n);
	}
	int p[5];
	void dfs(int x,int d,int F)//当前搜到x节点，与根的距离为d，爹是F 
	{
		p[d]++;
		if(d==4) return;//因为只求dis<=4的点对，多搜没有意义 
		int i,j;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(j==F) continue;
			dfs(j,d+1,x);
		}
	}
	void cal()
	{
		p[1]=p[2]=p[3]=p[4]=0;
		int i,j;
		for(i=0;i<=n;i++)
		dfs(i,0,-1);
	}
}T1,T2;
struct TreeUnion
{
	double expectedCycles(vector <string> tree1, vector <string> tree2, int K)
	{
		int i,j;
		long long ans=0;
		//本题需要先拼接字符串 
		for(i=0;i<tree1.size();i++)
		T1.s+=tree1[i];
		for(i=0;i<tree2.size();i++)
		T2.s+=tree2[i];
		T1.predo();T2.predo();//拼接之后建树 
		T1.cal();T2.cal();//统计dis(A,B)==1,2,3,4的点对数量 
		for(i=1;i<K-2;i++)
		ans+=(long long)T1.p[i]*T2.p[K-2-i];
		return (double)ans/2/T1.n/(T1.n+1);//其实每种连边方法被算了两遍，所以还要除以2 
	}
};
/*int main()
{
	TreeUnion P;
	vector<string> V1,V2;
	V1.push_back("0 1 0 0 4 4 1 0 3 0 8 11 9 0 11 13 0 7 14 15 6 17 ");
	V1.push_back("16 15 0 2 1 17 13 23 29 11 14 24 13 32 28 24 28 37");
	V1.push_back(" 16 20 22 36 41 24 32 41 42 44 11 48 6 17 27 28 46");
	V1.push_back(" 32 43 43 3 25 11 33 46 59 22 5 65 67 56 48 72 66 ");
	V1.push_back("8 64 17 69 38 37 61 52 7 5 62 20 63 50 29 68 35 83"); 
	V1.push_back(" 33 88 61 78 4 36 92 47 66 42 24 23 50 27 95 76 69"); 
	V1.push_back(" 2 66 75 20 77 12 33 9 71 69 81 50 98 104 37 104 8"); 
	V1.push_back("1 58 89 65 90 112 115 1 87 70 132 114 59 75 19 9 1"); 
	V1.push_back("19 97 81 93 84 87 43 21 43 81 53 8 65 100 82 34 8 "); 
	V1.push_back("77 0 5 67 85 19 144 156 116 37 36 129 52 169 125 1");
	V1.push_back("71 41 147 143 50 51 76 163 131 100 73 4 154 79");
	V2.push_back("0 0 2 0 2 3 5 0 3 8 1 8 0 10 0 10 8 12 14 9 13 19 ");
	V2.push_back("1 11 0 11 24 12 25 25 21 20 3 15 2 1 1 33 9 17 26 "); 
	V2.push_back("26 27 41 8 29 31 1 41 37 16 18 38 15 37 21 7 23 35"); 
	V2.push_back(" 37 8 58 29 36 21 63 7 63 37 49 9 24 26 34 2 4 42 "); 
	V2.push_back("36 2 2 2 45 10 11 56 38 1 77 20 54 87 90 33 16 87 "); 
	V2.push_back("38 70 80 58 47 65 36 86 56 65 102 50 103 52 77 25 "); 
	V2.push_back("70 97 98 72 84 61 114 82 30 54 116 27 7 13 51 118 "); 
	V2.push_back("101 46 63 8 44 43 86 63 21 31 19 99 26 97 87 133 1"); 
	V2.push_back("18 34 32 32 111 102 3 3 71 139 99 105 76 35 82 82 "); 
	V2.push_back("88 105 48 13 13 145 81 154 135 44 116 34 67 41 44 "); 
	V2.push_back("100 78 138 136 81 102 167 175 58 87 68 94 1"); 
	cout<<P.expectedCycles(V1,V2,4);
}*/