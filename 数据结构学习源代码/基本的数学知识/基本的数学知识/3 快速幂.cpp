int quick_m(int a, int p, int mod)
{
	int ans = 1;
	while (p)
	{
		if (p & 1)
		{
			ans = ans * a % mod;
		}
		a = a * a % mod;
		p >>= 2;
	}
	return ans % mod;
}