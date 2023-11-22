<Query Kind="Program">
  <Namespace>System.Security.Cryptography</Namespace>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	Solution.GetNthKeyIndex("qzyelonm", 64).Dump();
}

public static class Solution {
	public static int GetNthKeyIndex(string salt, int n){
		int index, keys;
		
		keys = 0;
		for(index = 0; keys < n; index++){
			if (IsKey(salt, index)) {
				keys++;
			}
		}
		
		return index - 1;
	}

	private static bool IsKey(string salt, int index)
	{
		string hash = StringToMD5($"{salt}{index}");
	
		for(int i = 0; i < hash.Length - 2; i++){
			if(hash[i] == hash[i + 1] && hash[i] == hash[i + 2]){
				for(int j = 1; j <= 1000; j++){
					string nextHash = StringToMD5($"{salt}{index + j}");

					if (nextHash.Contains(new String(hash[i], 5))) {
						return true;
					}
				}
				
				return false;
			}
		}
		
		return false;
	}
	
	private static string StringToMD5(string input)
	{
		return Convert.ToHexString(MD5.HashData(System.Text.Encoding.ASCII.GetBytes(input)));
	}
}

#region private::Tests
[Fact]
public void ExampleTestcase(){
	Assert.Equal(22728, Solution.GetNthKeyIndex("abc", 64));
}
#endregion