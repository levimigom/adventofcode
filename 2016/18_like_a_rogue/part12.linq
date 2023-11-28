<Query Kind="Program">
  <Reference Relative="input.txt">C:\Development\adventofcode\2016\18_like_a_rogue\input.txt</Reference>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	string row = File.ReadAllText("input.txt");
	
	// part 1
	Solution.CountSafeTiles(row, 40).Dump();
	// part 2
	Solution.CountSafeTiles(row, 400000).Dump();
}

public static class Solution {
	public static int CountSafeTiles(string firstRow, int rows){
		return GenerateMap(firstRow, rows).Select(row => row.Count(tile => tile == '.')).Sum();
	}

	public static IList<string> GenerateMap(string row, int rows){
		string[] map = new string[rows];
		
		map[0] = row;
		for(int i = 1; i < rows; i++){
			map[i] = GenerateNextRow(map[i - 1]);
		}
		
		return map.ToList();
	}
	
	private static string GenerateNextRow(string currentRow){
		string nextRow = string.Empty;
		
		for(int i = 0; i < currentRow.Length; i++){
			char left = i == 0 ? '.' : currentRow[i - 1];
			char right = i == currentRow.Length - 1 ? '.' : currentRow[i + 1];
			char center = currentRow[i];
			
			nextRow += GenerateTile(left, center, right);
		}
		
		return nextRow;
	}
	
	private static char GenerateTile(char left, char center, char right){
		if(left == '^' && center == '^' && right == '.'){
			return '^';
		}
		
		if(center == '^' && right == '^' && left == '.'){
			return '^';
		}
		
		if(left == '^' && center == '.' && right == '.'){
			return '^';
		}
		
		if(right == '^' && center == '.' && left == '.'){
			return '^';
		}
		
		return '.';
	}
}

#region private::Tests
[Theory]
[InlineData("..^^.", 3, 6)] 
[InlineData(".^^.^.^^^^", 10, 38)] 
public void TestExamples(string firstRow, int rows, int expectedOutput){	
	Assert.Equal(expectedOutput, Solution.CountSafeTiles(firstRow, rows));
}
#endregion