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
		string password = string.Empty;

		for (int i = 0; password.Length < PasswordLength; i++) {
			byte[] digest = MD5.HashData(Encoding.ASCII.GetBytes($"{doorId}{i}"));
			
			string digestString = Convert.ToHexString(digest);
			if(digestString.StartsWith("00000")){
				password += digestString[5];
			}
		}
		
		return password.ToLower();
	}
}

#region private::Tests
[Fact]
public void TestGeneratePassword(){
	string password = Solution.GeneratePassword("abc");
	Assert.Equal("18f47a30", password);
}
#endregion