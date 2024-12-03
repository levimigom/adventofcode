<Query Kind="Program">
  <Reference Relative="input.txt">C:\Dev\Repos\adventofcode\2024\03_mull_it_over\input.txt</Reference>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{	
	Solution.Solve(File.ReadAllText("input.txt")).Dump();
}

public static class Solution {
	public static int Solve(string memory)
	{
		IList<string> instructions = GetValidInstructions(memory);

		int solution = 0;
		
		foreach(var instruction in instructions){
			solution += EvaluateInstruction(instruction);
		}
		
		return solution;
	}
	
	private static IList<string> GetValidInstructions(string memory)
	{
		string pattern = @"mul\(\d{1,3},\d{1,3}\)";
		Regex regex = new Regex(pattern);
		
		return regex.Matches(memory).Select(m => m.Value).ToList();
	}

	public static int EvaluateInstruction(string instruction)
	{
		string pattern = @"mul\((\d{1,3}),(\d{1,3})\)";
		Regex regex = new Regex(pattern);
		
		int x = int.Parse(regex.Match(instruction).Groups[1].Value);
		int y = int.Parse(regex.Match(instruction).Groups[2].Value);
		
		return x * y;
	}
}

#region private::Tests
[Fact]
public void TestExample(){
	string memory = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";
	Assert.Equal(161, Solution.Solve(memory));
}
#endregion