#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;

class FoxAndChess
{
public:
	string ableToMove(string begin, string target)
	{
		const int n = begin.size();
		int ptr1 = 0, ptr2 = 0;//two pointers
		while(1)
		{
			while(ptr1 < n && begin[ptr1] == '.')
				ptr1++;
			while(ptr2 < n && target[ptr2] == '.')
				ptr2++;
			if(ptr1 == n && ptr2 == n)
				return "Possible";
			if(ptr1 == n || ptr2 == n || begin[ptr1] != target[ptr2] || (begin[ptr1] == 'L' && ptr1 < ptr2) || (begin[ptr1] == 'R' && ptr1 > ptr2))
				return "Impossible";
			ptr1++, ptr2++;
		}
	}
};

