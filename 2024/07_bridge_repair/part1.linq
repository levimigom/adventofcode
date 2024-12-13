<Query Kind="Program">
  <Reference Relative="input.txt">C:\Dev\Repos\adventofcode\2024\07_bridge_repair\input.txt</Reference>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	Solution.Solve(File.ReadAllLines("input.txt")).Dump();
}

public static class Solution {
	public static long Solve(string[] lines){
		long calibrationResult = 0;
		
		foreach(var line in lines){
			string[] parts = line.Replace(": ", " ").Split(" ");
			
			long[] numbers = parts[1..].Select(long.Parse).ToArray();
			long result = long.Parse(parts[0]);
			
			if(CanEvaluateToResult(numbers, 1, numbers[0], result)){
				calibrationResult += result;
			} 
		}
		
		return calibrationResult;
	}
	
	private static bool CanEvaluateToResult(long[] numbers, int index, long solution, long result){
		if(index == numbers.Length){
			return solution == result;
		}
		
		return CanEvaluateToResult(numbers, index + 1, solution + numbers[index], result)
			|| CanEvaluateToResult(numbers, index + 1, solution * numbers[index], result);
	}
}

#region private::Tests
[Fact]
public void TestExample(){
	string[] lines = [
		"190: 10 19",
		"3267: 81 40 27",
		"83: 17 5",
		"156: 15 6",
		"7290: 6 8 6 15",
		"161011: 16 10 13",
		"192: 17 8 14",
		"21037: 9 7 18 13",
		"292: 11 6 16 20"
	];
	
	Assert.Equal(3749, Solution.Solve(lines));
}
#endregion