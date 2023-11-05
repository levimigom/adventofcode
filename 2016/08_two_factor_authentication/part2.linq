<Query Kind="Program">
  <Reference Relative="input.txt">C:\Development\adventofcode\2016\08_two_factor_authentication\input.txt</Reference>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	Screen screen = new Screen();
	
	foreach(string instruction in File.ReadAllLines("input.txt")){
		screen.ExecuteInstruction(instruction);
	}
	
	screen.Dump();
}

public class Screen {
	private const int Rows = 6;
	private const int Cols = 50;

	private bool[,] _pixels;
	
	public Screen()
	{
		_pixels = new bool[Rows, Cols];
	}
	
	public void ExecuteInstruction(string instruction){
		string pattern = "(rect|rotate column|rotate row)[^\\d]*(\\d+)[^\\d]*(\\d+)";
		Regex regex = new Regex(pattern);
		Match match = regex.Match(instruction);

		if (!match.Success) {
			throw new Exception($"Invalid instruction {instruction}");
		}
		
		string action = match.Groups[1].Value;
		int a = int.Parse(match.Groups[2].Value);
		int b = int.Parse(match.Groups[3].Value);
		
		if(action == "rect"){
			TurnOnRectangle(a, b);
		} else if(action == "rotate row"){
			RotateRow(a, b);
		} else {
			RotateColumn(a, b);
		}
	}
	
	public void Dump(){
		_pixels.Dump();
	}

	private void TurnOnRectangle(int a, int b){
		for(int i = 0; i < b; i++){
			for(int j = 0; j < a; j++){
				_pixels[i, j] = true;
			}
		}
	}
	
	private void RotateRow(int row, int shift){
		bool[] rotatedRow = new bool[Cols];
		
		for(int i = 0; i < Cols; i++){
			rotatedRow[i] = _pixels[row, (i - shift + Cols) % Cols];
		}
		
		for(int i = 0; i < Cols; i++){
			_pixels[row, i] = rotatedRow[i];
		}
	}
	
	private void RotateColumn(int col, int shift){
		bool[] rotatedCol = new bool[Rows];
		
		for(int i = 0; i < Rows; i++){
			rotatedCol[i] = _pixels[(i - shift + Rows) % Rows, col];
		}
		
		for(int i = 0; i < Rows; i++){
			_pixels[i, col] = rotatedCol[i];
		}
	}
}