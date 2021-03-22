# EE494PiEnvExplorer
Software Source for EE494 - PiEnvExplorer

USER GUIDE
1.	Set the cycle parameter in the input file CoreConfiguration.json.
-	This file is saved on the UMS. User only need to change two parameters: how often the data will be collected and how long the cycle will run.
2.	Power on the system (make sure the input is 5V-2.5A)
3.	First, the LED will blink every 0.5 seconds, indicating that the system is initializing to get ready. The LED will turn off once the system finished its inialization.
4.	Next, the LED will turn ON, meaning that the cycle is starts running (i.e. the sensor is collecting data and the CCU log the data to a file simultaneously). The cycle runs based on the setting in the input CoreConfiguration.json file. Once the cycle finishes, the LED will turn OFF.
5.	Finally, the LED will blink faster (every 0.25s) for a couple seconds to settle the system for a proper shutdown. Once the LED turns OFF, user can shut down the system.
6.	Remove the UMS and connect to the computer. All output files will be saved under “CycleLog_timestamp” folder. The folder includes two output files: system.csv and data.csv
-	system.csv logs all the status of the system during its operation
-	data.csv logs all the output sensor data.
