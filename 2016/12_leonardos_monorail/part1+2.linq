<Query Kind="Program">
  <Reference Relative="input.txt">C:\Development\adventofcode\2016\12_leonardos_monorail\input.txt</Reference>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	Console.WriteLine("== Part 1:");
	
	Computer c1 = new Computer();
	c1.ExecuteInstructions(File.ReadAllLines("input.txt").ToList());
	c1.GetRegisterValue('a').Dump();

	Console.WriteLine("== Part 2:");
	Computer c2 = new Computer();
	c2.SetRegisterValue('c', 1);
	c2.ExecuteInstructions(File.ReadAllLines("input.txt").ToList());
	c2.GetRegisterValue('a').Dump();
}

public class Computer {
	private Dictionary<char, int> _registers;
	
	public Computer()
	{
		_registers = new Dictionary<char, int>();
		_registers['a'] = 0;
		_registers['b'] = 0;
		_registers['c'] = 0;
		_registers['d'] = 0;
	}
	
	public void ExecuteInstructions(List<string> instructions){
		for (int i = 0; i < instructions.Count(); i++) {
			string instruction = instructions[i];
			
			// cpy x y
			if(instruction.StartsWith("cpy")){
				string x = instruction.Split(' ')[1];
				char y = instruction.Split(' ')[2].First();
				
				Copy(x, y);
			}
			// inc x
			else if(instruction.StartsWith("inc")){
				Increment(instruction[4]);	
			}
			// dec x
			else if(instruction.StartsWith("dec")){
				Decrement(instruction[4]);
			}
			// jnz x y
			else {
				string x = instruction.Split(' ')[1];
				int value = x.IsNumeric() ? int.Parse(x) : _registers[x.First()];
				
				int y = int.Parse(instruction.Split(' ')[2]);
				
				if(0 != value){
					i += int.Parse(instruction.Split(' ')[2]) - 1;
				}
			}
		}
	}
	
	private void Copy(string x, char y){
		if(int.TryParse(x, out int value)){
			_registers[y] = value;
		} else {
			_registers[y] = _registers[x.First()];
		}
	}
	
	private void Increment(char register){
		_registers[register]++;
	}
	
	private void Decrement(char register){
		_registers[register]--;
	}
	
	public int GetRegisterValue(char register)
	{
		return _registers[register];
	}
	
	public void SetRegisterValue(char register, int value){
		_registers[register] = value;
	}
}

public static class Extensions {
	public static bool IsNumeric(this string s){
		return int.TryParse(s, out _);
	}
}

#region private::Tests
[Fact]
public void TestExample(){
	Computer sut = new Computer();

	sut.ExecuteInstructions(new List<string>(){
		"cpy 41 a",
		"inc a",
		"inc a",
		"dec a",
		"jnz a 2",
		"dec a"
	});
	
	Assert.Equal(42, sut.GetRegisterValue('a'));
}
#endregion