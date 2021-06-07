When copying data from Arduino console to NotePad++ you need to replace the linefeed character with a tab. \r\n with \t
Copy the line in a row in a Excel sheet and save it as a "csv" file.
Then, open the file in NotePad++ and change the encoding to ANSI (to remove some weird characters).
Train the classes by running the command "python train_attack.py" or "python_train_defense.py".
Copy and paste the resulting code in NotePad++ and replace "float" with "int16_t" and the REGEX "\.[0-9]" with ""
Rename the class name with "RandomForestAttack" or "RandomForestDefense"