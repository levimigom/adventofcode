<Query Kind="Program">
  <Namespace>System.Security.Cryptography</Namespace>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	Solution.GeneratePassword("ffykfhsq").Dump();
}

public static class Solution {
	private const int PasswordLength = 8;
	
	public static string GeneratePassword(string doorId){
		char?[] password = new char?[PasswordLength];
		int charactersFound = 0;
		
		for (int i = 0; charactersFound < PasswordLength; i++) {
			byte[] digest = MD5.HashData(Encoding.ASCII.GetBytes($"{doorId}{i}"));
			
			string digestString = Convert.ToHexString(digest);
			if(digestString.StartsWith("00000") && digestString[5].IsNumeric()){
				int position = (int) char.GetNumericValue(digestString[5]);
			
				if(position < PasswordLength && !password[position].HasValue){
					password[position] = digestString[6];
					charactersFound++;
				}
			}
		}
		
		return new string(password.Select(c => c.Value).ToArray()).ToLower();
	}
}

public static class Extensions{
	public static bool IsNumeric(this char c){
		return '0' <= c && c <= '9';
	}
}

#region private::Tests
[Fact]
public void TestGeneratePassword(){
	string password = Solution.GeneratePassword("abc");
	Assert.Equal("05ace8e3", password);
}
#endregion