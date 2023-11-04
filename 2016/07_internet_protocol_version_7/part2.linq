<Query Kind="Program">
  <Reference Relative="input.txt">C:\Development\adventofcode\2016\07_internet_protocol_version_7\input.txt</Reference>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	string[] addresses = File.ReadAllLines("input.txt");
	
	int count = 0;
	foreach(string address in addresses){
		if(Solution.SupportsSSL(address)){
			count++;
		}
	}
	
	count.Dump();
}

public static class Solution
{
	public static bool SupportsSSL(string address)
	{
		List<string> abaList = new List<string>();
		List<string> babList = new List<string>();
		bool insideHyperNet = false;

		for (int i = 0; i < address.Length - 2; i++) {
			if (address[i] == '[') {
				insideHyperNet = true;
			}
			else if (address[i] == ']') {
				insideHyperNet = false;
			}
			else if (IsAba(address[i..(i + 3)])) {
				if (insideHyperNet) {
					babList.Add(address[i..(i + 3)]);
				}
				else {
					abaList.Add(address[i..(i + 3)]);
				}
			}
		}

		return abaList.Any(aba => babList.Contains($"{aba[1]}{aba[0]}{aba[1]}"));
	}
	
	private static bool IsAba(string input){
		return input[0] == input[2] && input[0] != input[1];
	}
}

#region private::Tests
[Theory]
[InlineData("aba[bab]xyz", true)]
[InlineData("xyx[xyx]xyx", false)]
[InlineData("aaa[kek]eke", true)]
[InlineData("zazbz[bzb]cdb", true)]
public void TestSupportsTLS(string address, bool expectedResult){
	Assert.Equal(expectedResult, Solution.SupportsSSL(address));
}
#endregion