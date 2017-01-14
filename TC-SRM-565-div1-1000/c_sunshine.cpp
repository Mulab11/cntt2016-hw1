#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
using namespace std;
typedef long long LL;
const int M=1000000009;

#define mp make_pair
#define pr pair<int,int>

class UnknownTree
{
	public:
	
	int one(vector<int> d)//One special node
	{
		//Let's make it root, each node can choose a parent among the root and the nodes closer to the root than it. 
		int res=1;
		sort(d.begin(),d.end());
		for(int i=0,j=0;i<d.size();i++)
		{
			for(;j<=d.size()&&d[j]<d[i];j++);
			res=(LL)res*(j+1)%M;//j+1 choices for i's parent.
		}
		return res;
	}
	
	int two(vector<pr> v)
	{
		//Each node's information is pair (dist to B,dist to A)
		int n=v.size();
		sort(v.begin(),v.end());
		//There must only be one starting vertex for this branch.
		if(n>1&&v[0].first==v[1].first)return 0;
		int A=0;
		for(;v[A].second;A++);//Get A.
		vector<pr > branchA;
		vector<int> branchO;
		if(!A)
		{
			for(int i=1;i<n;i++)//check the difference of the distance
				if(v[i].first-v[i].second==v[0].first)branchO.push_back(v[i].second);
				else return 0;
			return one(branchO);
		}
		//Select the branch for each i
		for(int i=1;i<n;i++)
		{
			int dtA=v[i].second-v[0].second;
			int dtB=v[i].first-v[0].first;
			if(dtA==dtB)branchO.push_back(dtA);//In the other branch.
			else branchA.push_back(v[i]);//In A's branch.
			if(dtA+dtB<0)return 0;
		}
		return (LL)one(branchO)*two(branchA)%M;//Solve the subproblem.
	}
	
	int three_chain(vector<int> &dA,vector<int> &dB,vector<int> &dC)//C is between A,B: A-C-B
	{
		int n=dA.size();
		set<pr> ACBC;
		int ac,bc;
		//Look for candidates for AC and BC
		for(int i=0;i<n;i++)
		{
			//Assume it is in neither A's or B's branch:
			//dC[i] = x
			//dA[i] = AC + x , AC = dA[i] - dc[i]
			//dB[i] = BC + x , BC = dB[i] - dc[i]
			ac=dA[i]-dC[i];
			bc=dB[i]-dC[i];
			if(ac>0&&bc>0)ACBC.insert(mp(ac,bc));
			//Now assume it is in A's branch, between A and C
			//AC = dA[i] + dC[i]
			//BC = dB[i] - dC[i]
			ac=dA[i]+dC[i];
			bc=dB[i]-dC[i];
			if(bc>0)ACBC.insert(mp(ac,bc));
			//Assume it is in A's branch, after A.
			//dC[i] = dA[i] + AC
			ac=dC[i]-dA[i];
			if(ac>0&&bc>0)ACBC.insert(mp(ac,bc));
			//Same two cases with B's branch:
			ac=dA[i]-dC[i];
			bc=dB[i]+dC[i];
			if(ac>0)ACBC.insert(mp(ac,bc));
			bc=dC[i]-dB[i];
			if(ac>0&&bc>0)ACBC.insert(mp(ac,bc));
		}
		int res=0,tmp;
		for(set<pr>::iterator it=ACBC.begin();it!=ACBC.end();it++)
		{
			ac=it->first,bc=it->second;
			vector<pr> branchA,branchB;
			vector<int> branchO;
			branchA.push_back(mp(0,ac));
			branchA.push_back(mp(ac,0));
			branchB.push_back(mp(0,bc));
			branchB.push_back(mp(bc,0));
			bool flag=1;
			int dtA,dtB,dtC;
			//We simply divide the nodes set into three part branch A, branch B and branch O(C).
			//Solve them as subproblems and multiple the number of ways.
			for(int i=0;i<n&&flag;i++)
			{
				dtC=dC[i];
				dtA=dA[i]-ac;
				dtB=dB[i]-bc;
				if(dtA==dtC&&dtB==dtC)//other
					branchO.push_back(dC[i]);
				else if(dtB==dtC)//A's
					branchA.push_back(mp(dC[i],dA[i]));
				else if(dtA==dtC)//B's
					branchB.push_back(mp(dC[i],dB[i]));
				else flag=0;//something wrong.
			}
			if(flag)
			{
				tmp=one(branchO);
				tmp=(LL)tmp*two(branchA)%M;
				tmp=(LL)tmp*two(branchB)%M;
				res=(res+tmp)%M;
			}
		}
		return res;
	}
	
	int three_center(vector<int> &dA,vector<int> &dB,vector<int> &dC,int p)//p is the center
	{
		/*******
		    A
		    |
		    p
		   / \
		  B   C
		********/
		int n=dA.size();
		vector<pr> branchA,branchB,branchC;
		vector<int> branchO;
		branchA.push_back(mp(0,dA[p]));
		branchA.push_back(mp(dA[p],0));
		branchB.push_back(mp(0,dB[p]));
		branchB.push_back(mp(dB[p],0));
		branchC.push_back(mp(0,dC[p]));
		branchC.push_back(mp(dC[p],0));
		for(int i=0;i<n;i++)
			if(i!=p)
			{
				int dtA=dA[i]-dA[p];
				int dtB=dB[i]-dB[p];
				int dtC=dC[i]-dC[p];
				if(dtA>0&&dtA==dtB&&dtA==dtC)//It is in a branch different to A's, B's or C's
					branchO.push_back(dtA);
				else if(dtB>0&&dtB==dtC)//It is in A's branch.
					branchA.push_back(mp(dtB,dA[i]));
				else if(dtC>0&&dtC==dtA)//It is in B's branch.
					branchB.push_back(mp(dtC,dB[i]));
				else if(dtA>0&&dtA==dtB)//It is in C's branch.
					branchC.push_back(mp(dtA,dC[i]));
				else return 0;//something wrong.
			}
		int res=one(branchO);
		res=(LL)res*two(branchA)%M;
		res=(LL)res*two(branchB)%M;
		res=(LL)res*two(branchC)%M;
		return res;
	}
	
	int getCount(vector<int> distancesA,vector<int> distancesB,vector<int> distancesC)
	{
		int res=0,n=distancesA.size();
		for(int i=0;i<n;i++)//Pick the center.
			res=(res+three_center(distancesA,distancesB,distancesC,i))%M;
		//chain:
		res=(res+three_chain(distancesB,distancesC,distancesA))%M;
		res=(res+three_chain(distancesC,distancesA,distancesB))%M;
		res=(res+three_chain(distancesA,distancesB,distancesC))%M;
		return res;
	}
};

