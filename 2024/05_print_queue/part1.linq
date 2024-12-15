<Query Kind="Program">
  <Reference Relative="example.txt">C:\Dev\Repos\adventofcode\2024\05_print_queue\example.txt</Reference>
  <Reference Relative="input.txt">C:\Dev\Repos\adventofcode\2024\05_print_queue\input.txt</Reference>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	//RunTests();  // Call RunTests() or press Alt+Shift+T to initiate testing.
}

public static class Solution {
	public static int Solve(string[] lines){
		Dictionary<int, Rule> rules = ParseRules(lines.Where(l => l.Contains("|")).ToArray());
		List<int[]> pages = ParsePages(lines.Where(l => l != "" && !l.Contains("|")).ToArray());
		
		foreach(var page in pages){
			if(ValidatePage(page, rules)){
				page.Dump();
			}
		}
		
		return 0;
	}
	
	private static bool ValidatePage(int[] page, Dictionary<int, Rule> rules){
		for(int i = 0; i < page.Length; i++)
		{
			int number = page[i];
			
			foreach(int before in rules[number].Before){
				if(page.Contains(before) && Array.IndexOf(page, before) < i){
					return false;
				}
			}
		}
		
		return true;
	}

	private static Dictionary<int, Rule> ParseRules(string[] lines)
	{
		Dictionary<int, Rule> rules = [];
		
		foreach(string line in lines){
			string[] parts = line.Split("|");
			
			int a = int.Parse(parts[0]);
			int b = int.Parse(parts[1]);
			
			if(!rules.ContainsKey(a)){
				rules[a] = new Rule();
			}
			
			if(!rules.ContainsKey(b)){
				rules[b] = new Rule();
			}
			
			rules[b].After.Add(a);
			rules[a].Before.Add(b);
		}
		
		return rules;
	}
	
	private static List<int[]> ParsePages(string[] lines){
		return lines.Select(l => l.Split(",").Select(int.Parse).ToArray()).ToList();
	}
	
	private sealed class Rule {
		public IList<int> Before { get; }
		public IList<int> After { get; }
		
		public Rule()
		{
			Before = [];
			After = [];
		}
	}
}

#region private::Tests
[Fact]
public void TestExample(){
	Assert.Equal(143, Solution.Solve(File.ReadAllLines("example.txt")));
}
#endregion