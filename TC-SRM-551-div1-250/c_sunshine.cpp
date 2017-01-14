#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class ColorfulChocolates
{
	public:
	
	vector<int> p[26];
	
	int maximumSpread(string chocolates,int maxSwaps)
	{
		string C=chocolates;
		int n=C.size();
		for(int i=0;i<n;i++)
			p[C[i]-'A'].push_back(i);
		int ans=0;
		for(int c=0;c<26;c++)//Pick the color of chocolates which have the longest adjacent segment.
		{
			int m=p[c].size();
			//for each interval of this color of chocolates,
			//we check if it is possible to do some swaps to make them adjacent.
			for(int i=0;i<m;i++)
				for(int j=i;j<m;j++)
				{
					//We can prove that at least one chocolate remain unmoved,
					//so we can pick it.
					int w=0;
					//Calculate the cost when the position of i-th chocolate with color c is conserved.
					for(int k=i;k<=j;k++)
						w+=p[c][k]-(p[c][i]+k-i);
					//Pick all chocolates whose position remain unchanged, and maintain the cost.
					for(int k=i;k<=j;k++)
					{
						if(w<=maxSwaps)//Update the answer.
							ans=max(ans,j-i+1);
						//Let d be the distance between the k-th and k+1-th chocolate of color c,
						//we can simply find the change of cost which is ((k-i)-(j-k-1))*d.
						if(k<j)
							w=w+((k-i)-(j-k-1))*(p[c][k+1]-p[c][k]-1);
					}
				}
		}
		return ans;
	}
};

