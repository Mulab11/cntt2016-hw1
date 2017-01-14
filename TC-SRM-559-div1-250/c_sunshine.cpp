#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
const LL dx[4]={-1,-1,1,1};
const LL dy[4]={-1,1,-1,1};
class HyperKnight
{
	public:
	vector<int> row,col;
	bool inner(LL a,LL n)
	{
		return a>=1&&a<=n;
	}
	LL countCells(int a,int b,int numRows,int numColumns,int k)
	{
		row.push_back(0);
		row.push_back(numRows);
		row.push_back(a);
		row.push_back(b);
		row.push_back(numRows-a);
		row.push_back(numRows-b);
		col.push_back(0);
		col.push_back(numColumns);
		col.push_back(a);
		col.push_back(b);
		col.push_back(numColumns-a);
		col.push_back(numColumns-b);
		//We insert all possible rows and columns through which the number of valid jumps may change.
		for(int i=0;i<row.size();i++)
			if(row[i]<0||row[i]>numRows)
				swap(row[i],row.back()),row.pop_back();
		for(int i=0;i<col.size();i++)
			if(col[i]<0||col[i]>numColumns)
				swap(col[i],col.back()),col.pop_back();
		sort(row.begin(),row.end());
		sort(col.begin(),col.end());
		row.erase(unique(row.begin(),row.end()),row.end());
		col.erase(unique(col.begin(),col.end()),col.end());
		LL ans=0;
		//We count the valid jumps for each equivalent class that is a rectangle.
		for(int i=1;i<row.size();i++)
			for(int j=1;j<col.size();j++)
			{
				LL x=row[i],y=col[j];
				int cnt=0;
				for(int t=0;t<2;t++)
				{
					for(int d=0;d<4;d++)
						if(inner(x+dx[d]*a,numRows)&&inner(y+dy[d]*b,numColumns))
							cnt++;
					swap(a,b);
				}
				if(cnt==k)//Add its area to the answer.
					ans+=(LL)(row[i]-row[i-1])*(col[j]-col[j-1]);
			}
		return ans;
	}
};

