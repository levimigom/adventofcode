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
	
long paths1 = CountPathsWithStops(devices, [ "svr", "dac", "fft", "out" ]);
long paths2 = CountPathsWithStops(devices, [ "svr", "fft", "dac", "out" ]);
	
Console.WriteLine(paths1 + paths2);

void EnsureAdded(Dictionary<string, Device> devices, string label){
    if(!devices.ContainsKey(label)){
        devices.Add(label, new Device(label));
    }
}

long CountPathsWithStops(Dictionary<string, Device> devices, string[] labels){
    Dictionary<string, long> pathCounts = [];
    long paths = CountPaths(devices[labels[0]], pathCounts, labels[1]);
	
    for(int i = 1; i < labels.Length - 1; i++){
        pathCounts.Clear();
        paths *= CountPaths(devices[labels[i]], pathCounts, labels[i + 1]);
    }
	
    return paths;
}

long CountPaths(Device device, Dictionary<string, long> pathCounts, string targetLabel){
    if(pathCounts.ContainsKey(device.Label)){
        return pathCounts[device.Label];
    }
	
    if(device.Label.Equals(targetLabel)){
        return 1;
    }
	
    long paths = 0;
	
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