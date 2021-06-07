# Gesture recognition for LILYGO TTGO T-Watch

This repo contains scripts for generating data, calculating features, finding the best SVM model, and using the gesture recognition algorithm with LILYGO TTGO T-Watch. Data collected while working on the project has also been inlcuded.

This project was used for the preparation of the Wearables app for the European Project Semester 2021 at the Universitat Politècnica de València.

## Requirements

In order to use the files from the repo you will need:
- Python with Pandas, Numpy, micromlgen and scikit-learn packages installed
- MATLAB/Octave
- PlatformIO
- Arduino IDE
- Bluetooth serial terminal

## Using the existent gestures

If you want to use the ready-to-go gesture recognition algorithm trained with the ten gestures definied by us (see more in Wearables) please follow the below instructions. The accuracy that we obtained using this algorithm was 93%. **In case you want to train the algorithm with your own gestures, proceed to the next section.**

1. Using PlatformIO, open the ***ttgo*** folder as a project.
2. Compile and upload the project to the watch.
3. Connect the watch to your computer from a Bluetooth Serial Terminal.
4. Double-tap the screen of the watch and perform a gesture after you feel the vibration. The number of the recognized gesture will be sent to the Bluetooth Serial Terminal.

## Creating gesture recognition algorithm with your own gestures

1. Open the ***gesture-data*** folder.
2. Clear the folder from existing files. Prepare folders named **Gesture _n_**, where ***n*** is the number of the gesture. Start with ***n = 1*** and go up to the number of gestures that you wish to recognize.
3. In each of the folders create a ***noFiles.txt*** file. The file should contain the number of samples recorder for the gesture, in this case **0**.
4. Configure Arduino IDE for LILYGO TTGO T-Watch.
5. Open the ***AccGenerateTrainingData*** folder. Open the file with the same name in Arduino IDE and compile and upload the file to the watch.
6. Open Bluetooth settings on your computer and pair with **TTGO Watch**.
7. Open the ***generateData*** file in MATLAB. Run the script. If the connection has been estabilished correctly, you should see a **Enter the number of gesture:** prompt. After providing the number, press enter and perform the gesture with the watch (double-tap screen and perform gesture). Follow the instructions of the terminal. In case of an error, reupload the arduino file. Sometimes errors occur while connecting to the watch, in such case also try reuploading the arduino files.
8. After all the data has been collected, use the ***computeFeatures*** MATLAB script to compute a set of features for a pre-recorded sample. Iterate in order to create an array where each row is one sample generated by the script. To each row, add a column with the gesture number corresponding to the sample. You can use a ***importTrainingExample*** script to upload a specific sample of a specific gesture. For more info, open the scripts and check the comments together with function definitions.
9. Shuffle the array, and split it to train and test sets. Save the sets as ***trainData.txt*** and ***evaluateData.txt*** csv files in the ***Python*** folder.
10. Run the ***findSVMParameters*** Python script from the ***Python*** folder. The script will print in the console the fitting results with different parameters as well as the best parameters.
11. Using micromlgen Python library, generate a SVM model C-file. Save it as a ***predict_class.h*** header file.
12. Upload the existing ***predict_class*** in the ***ttgo/src*** directory.
13. Using PlatformIO, open the ***ttgo*** folder as a project.
14. Compile and upload the project to the watch.
15.  Connect the watch to your computer from a Bluetooth Serial Terminal.
16.  Double-tap the screen of the watch and perform a gesture after you feel the vibration. The number of the recognized gesture will be sent to the Bluetooth Serial Terminal.
