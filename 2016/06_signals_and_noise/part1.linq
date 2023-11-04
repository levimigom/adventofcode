<Query Kind="Program">
  <Reference Relative="input.txt">C:\Development\adventofcode\2016\06_signals_and_noise\input.txt</Reference>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	List<string> recording = File.ReadAllLines("input.txt").ToList();
	Solution.DecryptMessage(recording).Dump();
}

public static class Solution {
	public static string DecryptMessage(List<string> recording){
		string message = string.Empty;

		for (int i = 0; i < recording.First().Length; i++) {
			int[] characterFrequency = new int['z' - 'a' + 1];
			
			foreach(string word in recording){
				characterFrequency[word[i] - 'a']++;
			}

			message += characterFrequency.Select((count, index) => (count, (char) ('a' + index))).Max().Item2;
		}
		
		return message;
	}
}

#region private::Tests
[Fact]
public void TestDecryptMessage(){
	List<string> recording = new List<string>() {
		"eedadn",
		"drvtee",
		"eandsr",
		"raavrd",
		"atevrs",
		"tsrnev",
		"sdttsa",
		"rasrtv",
		"nssdts",
		"ntnada",
		"svetve",
		"tesnvt",
		"vntsnd",
		"vrdear",
		"dvrsen",
		"enarar",
	};
	
	Assert.Equal("easter", Solution.DecryptMessage(recording));
}
#endregion