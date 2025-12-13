Dictionary<string, Device> devices = [];
	
foreach(string line in File.ReadAllLines("input.txt")){
    string[] labels = line.Split(" ");
		
    string deviceName = labels[0][..(labels[0].Length - 1)];
    
    EnsureAdded(devices, deviceName);
    for(int i = 1; i < labels.Length; i++){
        EnsureAdded(devices, labels[i]);
        devices[deviceName].Outputs.Add(devices[labels[i]]);
    }
}
	
Dictionary<string, int> pathCounts = [];
int pathCount = CountPaths(devices["you"], pathCounts, "out");
Console.WriteLine(pathCount);

void EnsureAdded(Dictionary<string, Device> devices, string label){
    if(!devices.ContainsKey(label)){
        devices.Add(label, new Device(label));
    }
}

int CountPaths(Device device, Dictionary<string, int> pathCounts, string targetLabel){
    if(pathCounts.ContainsKey(device.Label)){
        return pathCounts[device.Label];
    }
	
    if(device.Label.Equals(targetLabel)){
        return 1;
    }
	
    int paths = 0;
	
    pathCounts[device.Label] = 0;
    foreach(Device output in device.Outputs){
        paths += CountPaths(output, pathCounts, targetLabel);
    }
    pathCounts[device.Label] = paths;
	
    return paths;
}

public sealed class Device(string label) {
    public string Label { get; } = label;
    public List<Device> Outputs { get; } = [];
}