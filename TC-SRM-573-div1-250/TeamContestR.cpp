class TeamContest {
	public:
	int worstRank(vector<int> strength) {
		int f0 = strength[0], f1 = strength[1], f2 = strength[2];
		int b = max(max(f0, f1), f2) + min(min(f0, f1), f2) + 1;
		
		vector<int> a;
		for(int i=3;i<strength.size();i++)
			a.push_back(strength[i]);
		
		sort(a.begin(), a.end());
		int l = 0, r = a.size(), res = 1;
		while(--r >= l)
		{
			l = lower_bound(a.begin()+l, a.begin()+r, b - a[r]) - a.begin();
			if(l + 1 < r) ++res;
			l += 2;
		}

		return res;
	}
};
