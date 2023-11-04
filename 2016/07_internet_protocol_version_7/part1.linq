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
		if(Solution.SupportsTLS(address)){
			count++;
		}
	}
	
	count.Dump();
}

public static class Solution {
	public static bool SupportsTLS(string address){
		bool containsAbba, insideHyperNet;
		
		containsAbba = insideHyperNet = false;
		for(int i = 0; i < address.Length - 3; i++){
			if(address[i] == '['){
				insideHyperNet = true;
			} else if(address[i] == ']'){
				insideHyperNet = false;
			}
			
			if(IsAbba(address[i..(i+4)])){
				if(insideHyperNet){
					return false;
				} else {
					containsAbba = true;
				}
			}
		}
		
		return containsAbba;
	}
	
	private static bool IsAbba(string input){
		return(input[0] != input[1] && input[1] == input[2] && input[0] == input[3]);
	}
}

#region private::Tests
[Theory]
[InlineData("abba[mnop]qrst", true)]
[InlineData("abcd[bddb]xyyx", false)]
[InlineData("aaaa[qwer]tyui", false)]
[InlineData("ioxxoj[asdfgh]zxcvbn", true)]
public void TestSupportsTLS(string address, bool expectedResult){
	Assert.Equal(expectedResult, Solution.SupportsTLS(address));
}
#endregion