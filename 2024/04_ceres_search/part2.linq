<Query Kind="Program">
  <Reference Relative="input.txt">C:\Dev\Repos\adventofcode\2024\04_ceres_search\input.txt</Reference>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	Solution.Solve(File.ReadAllLines("input.txt")).Dump();
}

public static class Solution
{	
	public static int Solve(string[] grid)
	{
		int matches = 0;
		
		for(int row = 1; row < grid.Length - 1; row++){
			for(int col = 1; col < grid[row].Length - 1; col++){
				if(Matches(grid, row, col)){
					matches++;
				}
			}
		}
		
		return matches;
	}
	
	private static bool Matches(string[] grid, int row, int col)
	{
		char[][] diagonals = [
			[grid[row - 1][col - 1], grid[row + 1][col + 1]],
			[grid[row + 1][col - 1], grid[row - 1][col + 1]]
		];
	
		return grid[row][col] == 'A' && diagonals.All(diagonal => diagonal.Contains('M') && diagonal.Contains('S'));
	}
}

#region private::Tests
[Fact]
public void TestExample(){
	string[] grid = [
		"MMMSXXMASM",
		"MSAMXMSMSA",
		"AMXSXMAAMM",
		"MSAMASMSMX",
		"XMASAMXAMM",
		"XXAMMXXAMA",
		"SMSMSASXSS",
		"SAXAMASAAA",
		"MAMMMXMMMM",
		"MXMXAXMASX"
	];
	
	Assert.Equal(9, Solution.Solve(grid));
}
#endregion