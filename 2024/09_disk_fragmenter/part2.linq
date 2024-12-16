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
		int[] compressed = Compress(blocks);
		return Checksum(compressed);
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
	
	public static int[] Compress(int[] blocks){
		for(int i = blocks.Length - 1; 0 <=  i; i--){
			if(blocks[i] != -1){
				int j;
				for(j = i; 0 < j && blocks[j - 1] == blocks[i]; j--);

				int length = i - j + 1;
				int index = IndexOf(blocks, length);
				
				if(index != -1 && index < i){
					for(int k = index; k < index + length; k++){
						blocks[k] = blocks[i];
					}
					
					for(int k = j; k <= i; k++){
						blocks[k] = -1;
					}
				}
				
				i = j;
			}
		}
		
		return blocks;
	}
	
	private static int IndexOf(int[] blocks, int empty){
		int consecutiveEmpty = 0;
		
		for(int i = 0; i < blocks.Length; i++){
			if(blocks[i] == -1){
				consecutiveEmpty++;
				
				if(consecutiveEmpty == empty){
					return i - empty + 1;
				}
			} else {
				consecutiveEmpty = 0;
			}
		}
		
		return -1;
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
	Assert.Equal(Solution.Solve("2333133121414131402"), 2858);  
}
#endregion