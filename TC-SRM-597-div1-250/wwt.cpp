#include <bits/stdc++.h>

using namespace std;

int ap[1000],bp[1000];

class LittleElephantAndString
{
public:
	int getNumber(string A, string B)
	{
		for(auto p : A) ap[p] ++;
		for(auto p : B) bp[p] ++;
		for(char x = 'A';x <= 'Z';x ++)
			if (ap[x] != bp[x]) return -1; //A和B出现的字符要相同
		for(int i = B.length() - 1,j = i;i >= 0;i --) //找到B最长的后缀使得他是A的一个子序列
		{
			for(;j >= 0 && A[j] != B[i];j --);
			if (j < 0) return i + 1;
			j --;
		}
		return 0;
	}
};
