<Query Kind="Program">
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	//RunTests();  // Call RunTests() or press Alt+Shift+T to initiate testing.
}

public static class Solution
{
	private static int Directions => RowSteps.Length;
	private static readonly int[] RowSteps = [ 
		1, // down
		-1, // up
		0, // right
		0,  // left
		1,  // down right
		1,  // down left
		-1,  // up right
		-1,  // up left
	];
	private static readonly int[] ColSteps = [
		0, // down
		0, // up
		1, // right
		-1, // left
		1, // down right
		-1, // down left
		1, // up right
		-1, // up left
	];
	private const string Needle = "XMAS";
	
	public static int Solve(string[] grid){
		int matches = 0;
		
		for(int row = 0; row < grid.Length; row++){
			for(int col = 0; col < grid[row].Length; col++){
				for(int i = 0; i < Directions; i++){
					if(Matches(grid, row, col, RowSteps[i], ColSteps[i])){
						matches++;
					}
				}
			}
		}
		
		return matches;
	}
	
	private static bool Matches(string[] grid, int row, int col, int rowStep, int colStep){
		int newRow, newCol;
		
		for(int i = 0; i < Needle.Length; i++){
			newRow = row + i * rowStep;
			newCol = col + i * colStep;
			
			if(!IsWithinBounds(grid, newRow, newCol) || grid[newRow][newCol] != Needle[i]){
				return false;
			}
		}
		
		return true;
	}
	
	private static bool IsWithinBounds(string[] grid, int row, int col){
		return(0 <= row && row < grid.Length && 0 <= col && col < grid[row].Length);
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
	
	Assert.Equal(18, Solution.Solve(grid));
}
#endregion