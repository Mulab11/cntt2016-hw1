#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <stack>
#include <map>
using namespace std;
class Number
{
	public:
		long long val;//the number
		bool type;//true if it can be affected by "-1"
		Number(){}
		Number(long long val, bool type): val(val), type(type) {}
		Number operator +(const Number &b) const
		{
			return Number(val + b.val, type || b.type);
		}
};
class Suminator
{
	private:
	stack <Number> s;
	Number gettop()
	{
		if(s.empty())
			return Number(0, 0);
		Number ret = s.top();
		s.pop();
		return ret;
	}
	Number run(const vector <int> &program)
	{
		while(!s.empty())
			s.pop();
		for(int i = 0; i < program.size(); i++)
			if(program[i] == 0)
				s.push(gettop() + gettop());
			else if(program[i] > 0)
				s.push(Number(program[i], 0));
			else
				s.push(Number(0, 1));
		return gettop();
	}
	public:
	int findMissing(vector<int> program, int wantedResult)
	{
		for(int i = 0; i < program.size(); i++)
			if(program[i] == -1)
			{
				program[i] = 0;//try 0
				if(run(program).val == wantedResult)//success
					return 0;
				program[i] = -1;//try any positive number
				Number now = run(program);
				if(!now.type || now.val >= wantedResult)
					return -1;
				return wantedResult - now.val;//the only possible value
			}
		return -1;
	}
};

