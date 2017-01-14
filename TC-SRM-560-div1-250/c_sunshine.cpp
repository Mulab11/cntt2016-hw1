#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class TomekPhone
{
	public:
	vector<int> s;
	int minKeystrokes(vector<int> frequencies,vector<int> keySizes)
	{
		//Get all labels.
		for(int i=0;i<keySizes.size();i++)
			for(int j=1;j<=keySizes[i];j++)
				s.push_back(j);
		//We can prove it best to match them with labels in increasing order and frequencies in decreasing order.
		sort(s.begin(),s.end());
		sort(frequencies.begin(),frequencies.end());
		reverse(frequencies.begin(),frequencies.end());
		if(s.size()<frequencies.size())return -1;
		int ans=0;
		//Calculate the answer.
		for(int i=0;i<frequencies.size();i++)
			ans+=frequencies[i]*s[i];
		return ans;
	}
};

