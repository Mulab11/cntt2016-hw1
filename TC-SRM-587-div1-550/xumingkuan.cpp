class TriangleXor
{
public:
	int theArea(int W)
	{
		double ans = (W + 1.0) / W;
		for(int i = 0; i < W; i++)//inclusion-exclusion principle
			ans += (i & 1 ? 2.0 : -2.0) * (W - i) / (W + i + 1);
		return ans * W * W / 2;
	}
};

