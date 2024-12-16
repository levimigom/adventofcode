<Query Kind="Program">
  <Reference Relative="input.txt">C:\Dev\Repos\adventofcode\2024\09_disk_fragmenter\input.txt</Reference>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	Solution.Solve(File.ReadAllText("input.txt")).Dump();
}

public static class Solution {
	public static long Solve(string map){
		int[] blocks = ConvertMapToBlocks(map);
		
		return Checksum(Compress(blocks));
	}
	
	private static int[] ConvertMapToBlocks(string map){
		int[] digits = map.ToCharArray().Select(c => c - '0').ToArray();
		List<int> blocks = [];
		
		for(int i = 0; i < digits.Length; i++){
			for(int j = 0; j < digits[i]; j++){
				if(i % 2 == 0){
					blocks.Add(i / 2);
				} else {
					blocks.Add(-1);
				}
			}
		}
		
		return blocks.ToArray();
	}
	
	private static int[] Compress(int[] blocks){
		int i = 0, j = blocks.Length - 1;
		
		while(i < j){
			if(blocks[j] == -1){
				j--;
			} else if(blocks[i] != -1){
				i++;
			} else {
				blocks[i] = blocks[j];
				blocks[j] = -1;
			}
		}
		
		return blocks;
	}
	
	private static long Checksum(int[] blocks){
		long checksum = 0;
		
		for(int i = 0; i < blocks.Length; i++){
			if(blocks[i] != -1){
				checksum += i * blocks[i];
			}
		}
		
		return checksum;
	}
}

#region private::Tests
[Fact]
public void TestExample(){
	Assert.Equal(Solution.Solve("2333133121414131402"), 1928);  
}
#endregion