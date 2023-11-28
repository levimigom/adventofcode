<Query Kind="Program">
  <Namespace>System.Security.Cryptography</Namespace>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	Solution.ShortestPathToVault("rrrbmfta").Dump();
}

public static class Solution {
	private const int Width = 4;
	private const int Height = 4;

	public static string ShortestPathToVault(string passcode){
		Queue<Path> queue = new Queue<Path>();

		queue.Enqueue(new Path(0, 0, string.Empty));
		while(0 < queue.Count() && (queue.Peek().Row != Height - 1 || queue.Peek().Col != Width - 1)){
			ProcessPath(queue.Dequeue(), queue, passcode);
		}
		
		if(queue.Any()){
			return queue.Dequeue().Moves;
		} else {
			return string.Empty;
		}
	}
	
	private static void ProcessPath(Path path, Queue<Path> queue, string passcode){
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
[InlineData("ihgpwlah", "DDRRRD")]
[InlineData("kglvqrro", "DDUDRLRRUDRD")]
[InlineData("ulqzkmiv", "DRURDRUDDLLDLUURRDULRLDUUDDDRR")]
public void TestExamples(string passcode, string expectedPath){
	Assert.Equal(expectedPath, Solution.ShortestPathToVault(passcode));
}
#endregion