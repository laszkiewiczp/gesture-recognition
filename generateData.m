% Find a Bluetooth connection object.
obj1 = instrfind('Type', 'bluetooth', 'Name', 'Bluetooth-TTGo Watch:1', 'Tag', '');

% Create the Bluetooth connection object if it does not exist
% otherwise use the object that was found.
if isempty(obj1)
    obj1 = Bluetooth('TTGo Watch', 1);
else
    fclose(obj1);
    obj1 = obj1(1);
end

% Connect to instrument object, obj1.
fopen(obj1);

directory = "gesture-data/Gesture %s";
keep_running = true;

noGesture = input("Enter the number of gesture: ", 's');

while keep_running
    
    currentDirectory = sprintf(directory, noGesture);
    numberFiles = importdata(currentDirectory + "/noFiles.txt"); %noFiles.txt stores information about the current amount of samples of the gesture
    file1 = fscanf(obj1);
    no_samples = str2num(file1);
    acc_data = [];

    for i = 1:no_samples
        file2 = fscanf(obj1);
        split_data = strsplit(file2);
        acc_data = [acc_data; str2num(split_data{1}), str2num(split_data{2}), str2num(split_data{3})];
    end
    
    if isempty(acc_data)
        keep_running = false;
        fprintf("ERROR occured while collecting the data. The program will stop");
        break
    end
    
    numberFiles = numberFiles + 1;
    dataDirectory = currentDirectory + "/" + numberFiles + ".txt";
    writematrix(acc_data, dataDirectory);
    writematrix(numberFiles, currentDirectory + "/noFiles.txt");
    
    if (input("Type N to stop, press any key to continue recording: ", 's') == "N")
        if (input ("Type C to change the gesture number, press any key to end: ", 's') ~= "C")
            keep_running = false;
        else
            noGesture = input("Enter the number of gesture: ", 's');
        end
    end   
end
fclose(obj1);