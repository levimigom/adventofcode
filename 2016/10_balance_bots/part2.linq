<Query Kind="Program">
  <Reference Relative="input.txt">C:\Development\adventofcode\2016\10_balance_bots\input.txt</Reference>
  <Namespace>Xunit</Namespace>
</Query>

#load "xunit"

void Main()
{
	Factory factory = new Factory();
	
	foreach(string instruction in File.ReadAllLines("input.txt")){
		factory.ParseInstruction(instruction);
	}
	
	factory.Compare();
	
	int result = factory.GetOutputValue(0) * factory.GetOutputValue(1) * factory.GetOutputValue(2);
	result.Dump();
}

public class Factory {
	private List<Robot> _robots;
	private List<Output> _outputs;
	
	public Factory()
	{
		_robots = new List<Robot>();
		_outputs = new List<Output>();
	}
	
	public void ParseInstruction(string instruction){
		if(instruction.StartsWith("value")){
			ParseAssignment(instruction);
		} else {
			ParseComparison(instruction);
		}
	}

	private void ParseAssignment(string instruction)
	{
		Regex regex = new Regex("value (\\d+) goes to bot (\\d+)");
		Match match = regex.Match(instruction);

		if (!match.Success) {
			throw new Exception($"Assignment instruction is in incorrect format '{instruction}'");
		}

		int value = int.Parse(match.Groups[1].Value);
		int robotId = int.Parse(match.Groups[2].Value);

		Robot robot = GetRobot(robotId);
		robot.Values.Add(value);
	}

	private void ParseComparison(string instruction)
	{
		Regex regex = new Regex("bot (\\d+) gives low to (bot|output) (\\d+) and high to (bot|output) (\\d+)");
		Match match = regex.Match(instruction);

		if (!match.Success) {
			throw new Exception($"Comparison instruction is in incorrect format '{instruction}'");
		}

		Robot robot = GetRobot(int.Parse(match.Groups[1].Value));
		robot.Low = GetComparisonOutput(match.Groups[2].Value, int.Parse(match.Groups[3].Value));
		robot.High = GetComparisonOutput(match.Groups[4].Value, int.Parse(match.Groups[5].Value));
	}

	private Robot GetRobot(int id){
		Robot robot = _robots.FirstOrDefault(r => r.Id == id);
		
		if(robot == null){
			robot = new Robot(id);
			_robots.Add(robot);
		}
		
		return robot;
	}
	
	private Output GetOutput(int id){
		Output output = _outputs.FirstOrDefault(o => o.Id == id);
		
		if(output == null){
			output = new Output(id);
			_outputs.Add(output);
		}
		
		return output;
	}

	private ComparisonResultOutput GetComparisonOutput(string type, int id){
		return type == "bot" ? GetRobot(id) : GetOutput(id);
	}
	
	public void Compare(){
		while(_robots.Any(r => r.CanCompare())){
			_robots.First(r => r.CanCompare()).CompareValues();
		}
	}
	
	public int GetOutputValue(int id){
		return GetOutput(id).Value;
	}
}

public abstract class ComparisonResultOutput {
	public abstract void AddValue(int value);
}

public class Robot : ComparisonResultOutput {
	public int Id { get; set; }
	public List<int> Values { get; set; }
	public ComparisonResultOutput Low { get; set; }
	public ComparisonResultOutput High { get; set; }
	
	private bool _hasBeenCompared;
	
	public Robot(int id)
	{
		Id = id;
		Values = new List<int>();
		
		_hasBeenCompared = false;
	}

	public override void AddValue(int value)
	{
		Values.Add(value);
	}
	
	public bool CanCompare(){
		return !_hasBeenCompared && Values.Count() == 2;
	}
	
	public void CompareValues(){
		Low.AddValue(Values.Min());
		High.AddValue(Values.Max());
		_hasBeenCompared = true;
	}
}

public class Output : ComparisonResultOutput {
	public int Id { get; set; }
	public int Value { get; set; }
	
	public Output(int id)
	{
		Id = id;
	}

	public override void AddValue(int value)
	{
		Value = value;
	}
}
