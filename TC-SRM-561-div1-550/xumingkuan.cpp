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
#include <queue>
#include <map>
#include <cassert>
using namespace std;
template <class Key, class Val> class Unordered_map
{
	private:
		static const int MOD = 129127;
		static const int SIZE = 454545;
		class Edge
		{
			public:
				Key k;
				Val v;
				int next;
		}e[SIZE + 1];
		int head[MOD], en;
	public:
		typedef Edge* iterator;
		typedef const Edge* const_iterator;
		void clear()
		{
			en = 0;
			memset(head, 0, sizeof(head));
		}
		Unordered_map()
		{
			clear();
		}
		const_iterator begin() const
		{
			return const_iterator(e + 1);
		}
		const_iterator end() const
		{
			return const_iterator(e + en + 1);
		}
		const_iterator find(const Key &k) const
		{
			const int u = k % MOD;
			for(int i = head[u]; i; i = e[i].next)
				if(e[i].k == k)
					return const_iterator(e + i);
			return end();
		}
		pair <iterator, bool> insert(const Key &k, const Val &v)
		{
			const int u = k % MOD;
			for(int i = head[u]; i; i = e[i].next)
				if(e[i].k == k)
					return make_pair(iterator(e + i), false);
			assert(en < SIZE);
			e[++en].k = k;
			e[en].v = v;
			e[en].next = head[u];
			head[u] = en;
			return make_pair(iterator(e + en), true);
		}
		const Val &operator [](const Key &k) const
		{
			return find(k)->v;
		}
		Val &operator [](const Key &k)
		{
			const int u = k % MOD;
			for(int i = head[u]; i; i = e[i].next)
				if(e[i].k == k)
					return e[i].v;
			assert(en < SIZE);
			e[++en].k = k;
			e[en].next = head[u];
			return e[head[u] = en].v;
		}
};
class Tree
{
	public:
		Tree *fa;
		vector <Tree*> son;
		unsigned long long v;//hash value
		Tree()
		{
			fa = 0;
			v = 0;
		}
		void calc()
		{
			if(v)
				return;
			if(son.empty())
			{
				v = 1;
				return;
			}
			unsigned long long tmp = 0;
			for(vector <Tree*> :: iterator it = son.begin(); it != son.end(); it++)
			{
				(*it)->calc();
				v += (*it)->v * (*it)->v;
				tmp ^= (*it)->v;
			}
			v = v * 1112333 + tmp;
		}
};
class CirclesGame
{
	private:
	Unordered_map <unsigned long long, int> f;//SG function 
	vector <Tree*> root;
	Tree a[60];
	int sqr(int x)
	{
		return x * x;
	}
	void dfs(Tree *p, Tree *q, bool *h)
	{
		for(vector <Tree*> :: iterator it = q->son.begin(); it != q->son.end(); it++)
			dfs(p, *it, h);
		int now = 0;//draw a red point in circle q
		Tree *r = 0;
		while(r != p)
		{
			for(vector <Tree*> :: iterator it = q->son.begin(); it != q->son.end(); it++)
				if(*it != r)
					now ^= search(*it);
			r = q;
			q = q->fa;
		}
		h[now] = true;
	}
	int search(Tree *p)
	{
		if(f.find(p->v) != f.end())
			return f[p->v];
		bool h[60];//for calculating mex
		memset(h, false, sizeof(h));
		dfs(p, p, h);
		int tmp = 0;
		while(h[tmp])
			tmp++;
		return f[p->v] = tmp;
	}
	public:
	string whoCanWin(vector<int> x, vector<int> y, vector<int> r)
	{
		f.clear();
		root.clear();
		int n = x.size();
		for(int i = 0; i < n; i++)
		{
			a[i].fa = 0;
			a[i].v = 0;
			a[i].son.clear();
		}
		for(int i = 0; i < n; i++)
		{
			int tmp = -1;//the smallest circle which contains circle i
			for(int j = 0; j < n; j++)
				if(r[j] > r[i] && sqr(r[j] - r[i]) > sqr(x[j] - x[i]) + sqr(y[j] - y[i]) && (tmp == -1 || r[j] < r[tmp]))
					tmp = j;
			if(tmp == -1)
				root.push_back(a + i);
			else
			{
				a[tmp].son.push_back(a + i);
				a[i].fa = a + tmp;
			}
		}
		int ans = 0;
		for(vector <Tree*> :: iterator it = root.begin(); it != root.end(); it++)
		{
			(*it)->calc();
			ans ^= search(*it);//xor the SG value of the trees to get the SG value of the whole forest
		}
		return ans ? "Alice" : "Bob";
	}
};

