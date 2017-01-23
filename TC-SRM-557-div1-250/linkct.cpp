#include <bits/stdc++.h>
using namespace std;

class FoxAndMountainEasy{
public:
	string possible(int n, int h0, int hn, string seg){
		if((abs(hn - h0) ^ n) & 1) return "NO"; //Parity of height changes after every step
		int i, m, curh, minh, delta;
		m = seg.length();
		for(i = curh = minh = 0; i < m; ++ i) //Calculate the minimal prefix height & total height of seg
			if(seg[i] == 'U') ++ curh;
			else minh = min(minh, -- curh);
		delta = - min(h0 + minh, 0); //delta x 'U' need to be placed before seg
		return n - delta >= abs(h0 + delta + curh - hn) ? "YES" : "NO";
	}
};
