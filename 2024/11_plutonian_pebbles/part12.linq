<Query Kind="Program">
  <Reference Relative="input.txt">C:\Dev\Repos\adventofcode\2024\11_plutonian_pebbles\input.txt</Reference>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	long[] stones = File.ReadAllText("input.txt").Split(" ").Select(long.Parse).ToArray();
	
	Solution.Solve(stones, 25).Dump();
	Solution.Solve(stones, 75).Dump();
}

public static class Solution {
	public static long Solve(IEnumerable<long> stones, int iterations){
		long count = 0;
		Dictionary<(long, int), long> cache = new();

		foreach (var stone in stones)
		{	
			count += CountStones(stone, iterations, cache);
		}
		
		return count;
	}

	private static long CountStones(long stone, int iterations, Dictionary<(long, int), long> cache)
	{
		if(iterations == 0){
			return 1;
		}
		
		if (!cache.ContainsKey((stone, iterations)))
		{
			long count = 0;

			if (stone == 0)
			{
				count = CountStones(1, iterations - 1, cache);
			}
			else if (CountDigits(stone) % 2 == 0)
			{
				string digits = stone.ToString();

				count = CountStones(long.Parse(digits[..(digits.Length / 2)]), iterations - 1, cache);
				count += CountStones(long.Parse(digits[(digits.Length / 2)..]), iterations - 1, cache);
			}
			else
			{
				count = CountStones(stone * 2024, iterations - 1, cache);
			}

			cache[(stone, iterations)] = count;
		}

		return cache[(stone, iterations)];
	}

	private static int CountDigits(long n) => n.ToString().Length;
}

#region private::Tests
[Fact]
public void TestExample1()
{
	long[] stones = [ 0, 1, 10, 99, 999 ];
	Assert.Equal(7, Solution.Solve(stones, 1));
}

[Fact]
public void TestExample2()
{
	long[] stones = [ 125, 17 ];
	Assert.Equal(22, Solution.Solve(stones, 6));
}
#endregion