<Query Kind="Program">
  <Namespace>System.Security.Cryptography</Namespace>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	Solution.LongestPathToVault("rrrbmfta").Dump();
}

public static class Solution {
	private const int Width = 4;
	private const int Height = 4;

	public static int LongestPathToVault(string passcode){
		Queue<Path> queue = new Queue<Path>();
		int[,] pathLengths = new int[Height, Width];

		queue.Enqueue(new Path(0, 0, string.Empty));
		while(0 < queue.Count()){
			ProcessPath(queue.Dequeue(), queue, pathLengths, passcode);
		}
		
		return pathLengths[Height - 1, Width - 1];
	}

	private static void ProcessPath(Path path, Queue<Path> queue, int[,] pathLengths, string passcode){
		pathLengths[path.Row, path.Col] = path.Moves.Length;
		
		if(path.Row == Height - 1 && path.Col == Width - 1){
			return;
		}
		
		string hash = ConvertToMD5($"{passcode}{path.Moves}");
		
		// up
		if(0 < path.Row && "BCDEF".Contains(hash[0])){
			queue.Enqueue(new Path(path.Row - 1, path.Col, path.Moves + "U"));
		}

		// down
		if (path.Row < Height - 1 && "BCDEF".Contains(hash[1])) {
			queue.Enqueue(new Path(path.Row + 1, path.Col, path.Moves + "D"));
		}

		// left
		if (0 < path.Col && "BCDEF".Contains(hash[2])) {
			queue.Enqueue(new Path(path.Row, path.Col - 1, path.Moves + "L"));
		}

		// right
		if (path.Col < Width - 1 && "BCDEF".Contains(hash[3])) {
			queue.Enqueue(new Path(path.Row, path.Col + 1, path.Moves + "R"));
		}
	}
	
	private static string ConvertToMD5(string input){
		return Convert.ToHexString(MD5.HashData(Encoding.UTF8.GetBytes(input)));
	}

	internal sealed class Path{
		public int Row { get; set; }
		public int Col { get; set; }
		public string Moves { get; set; }
		
		public Path(int row, int col, string moves){
			Row = row;
			Col = col;
			Moves = moves;
		}
	}
}

#region private::Tests
[Theory]
[InlineData("ihgpwlah", 370)]
[InlineData("kglvqrro", 492)]
[InlineData("ulqzkmiv", 830)]
public void TestExamples(string passcode, int expectedPathLength){
	Assert.Equal(expectedPathLength, Solution.LongestPathToVault(passcode));
}
#endregion