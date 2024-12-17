<Query Kind="Program">
  <Reference Relative="input.txt">C:\Dev\Repos\adventofcode\2024\11_plutonian_pebbles\input.txt</Reference>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	long[] stones = File.ReadAllText("input.txt").Split(" ").Select(long.Parse).ToArray();
	
	Solution.Solve(stones, 25, new Dictionary<(long, int), long>()).Dump();
	Solution.Solve(stones, 75, new Dictionary<(long, int), long>()).Dump();
}

public static class Solution {
	public static long Solve(IEnumerable<long> stones, int iterations, Dictionary<(long, int), long> cache){
		if(iterations == 0){
			return stones.Count();
		}
		
		long count = 0;

		foreach (var stone in stones)
		{
			if(!cache.ContainsKey((stone, iterations - 1))){
				cache[(stone, iterations - 1)] = Solve(Blink(stone), iterations - 1, cache);
			}
			
			count += cache[(stone, iterations - 1)];
		}
		
		return count;
	}

	private static IEnumerable<long> Blink(long stone)
	{
		if (stone == 0)
		{
			yield return 1;
		}
		else if (CountDigits(stone) % 2 == 0)
		{
			string digits = stone.ToString();

			yield return long.Parse(digits[..(digits.Length / 2)]);
			yield return long.Parse(digits[(digits.Length / 2)..]);
		}
		else
		{
			yield return stone * 2024;
		}
	}

	private static int CountDigits(long n) => n.ToString().Length;
}

#region private::Tests
[Fact]
public void TestExample1()
{
	long[] stones = [ 0, 1, 10, 99, 999 ];
	Assert.Equal(7, Solution.Solve(stones, 1, new Dictionary<(long, int), long>()));
}

[Fact]
public void TestExample2()
{
	long[] stones = [ 125, 17 ];
	Assert.Equal(22, Solution.Solve(stones, 6, new Dictionary<(long, int), long>()));
}
#endregion