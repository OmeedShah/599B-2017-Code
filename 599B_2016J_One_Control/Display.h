string mainBattery, backupBattery;
string encoderValue, gyroValue;
string leftIntEnc, rightIntEnc, accelerometer;

//Display Options
int autoSelectMode;
int primaryBattery;
int secondaryBattery;
int armEncoder;
int leftDrive;
int rightDrive;
int driveGyro;
int antiTipGyro;
int accel;
int none;

//selection
/***************************************/
/**/int firstLine = autoSelectMode;
/**/int secondLine = none;
/***************************************/

void setDisplay()
{
	//firstLine
	if(firstLine == autoSelectMode)
	{
		if(SensorValue(autoSelector) < 500)
			displayLCDString(0, 0, "Auto 1 Selected");
		if(SensorValue(autoSelector) > 500 && SensorValue(autoSelector) < 1000)
		  displayLCDString(0, 0, "Auto 2 Selected");
		if(SensorValue(autoSelector) > 1000 && SensorValue(autoSelector) < 1500)
			displayLCDString(0, 0, "Auto 3 Selected");
		if(SensorValue(autoSelector) > 1500 && SensorValue(autoSelector) < 2000)
			displayLCDString(0, 0, "Auto 4 Selected");
		if(SensorValue(autoSelector) > 2000 && SensorValue(autoSelector) < 2500)
			displayLCDString(0, 0, "Auto 5 Selected");
		if(SensorValue(autoSelector) > 2500 && SensorValue(autoSelector) < 3000)
			displayLCDString(0, 0, "Auto 6 Selected");
		if(SensorValue(autoSelector) > 3000 && SensorValue(autoSelector) < 3400)
			displayLCDString(0, 0, "Auto 7 Selected");
		if(SensorValue(autoSelector) > 3400 && SensorValue(autoSelector) < 3800)
			displayLCDString(0, 0, "Auto 8 Selected");
		if(SensorValue(autoSelector) > 3800)
			displayLCDString(0, 0, "Skills Selected");
	}
	if(firstLine == primaryBattery)
	{
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);
	}
	if(firstLine == secondaryBattery)
	{
		displayLCDString(0, 0, "Backup: ");
		sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
		displayNextLCDString(backupBattery);
	}
	if(firstLine == armEncoder)
	{
		displayLCDString(0, 0, "Enc Value: ");
		sprintf(encoderValue, "%1.2f%c", SensorValue[RightEncoder]);
		displayNextLCDString(encoderValue);
	}
	if(firstLine == leftDrive)
	{
		displayLCDString(0, 0, "Left Val: ");
		sprintf(leftIntEnc, "%1.2f%c", SensorValue[leftDriveEnc]);
		displayNextLCDString(leftIntEnc);
	}
	if(firstLine == rightDrive)
	{
		displayLCDString(0, 0, "Right Val: ");
		sprintf(rightIntEnc, "%1.2f%c", SensorValue[rightDriveEnc]);	//Build the value to be displayed
		displayNextLCDString(rightIntEnc);
	}
	if(firstLine == driveGyro)
	{
		displayLCDString(0, 0, "Gyro Val: ");
		sprintf(accelerometer, "%1.2f%c", SensorValue[gyro]);	//Build the value to be displayed
		displayNextLCDString(accelerometer);
	}
	if(firstLine == antiTipGyro)
	{
		displayLCDString(0, 0, "|Gyro Val: ");
		sprintf(accelerometer, "%1.2f%c", SensorValue[vertGyro]);	//Build the value to be displayed
		displayNextLCDString(accelerometer);
	}
	if(firstLine == accel)
	{
		displayLCDString(0, 0, "Accel Value: ");
		sprintf(accelerometer, "%1.2f%c", SensorValue[accelY]);	//Build the value to be displayed
		displayNextLCDString(accelerometer);
	}
	if(firstLine == none)
	{
		displayLCDString(0, 0, "          ");
	}

	//second line
	if(secondLine == autoSelectMode)
	{
		if(SensorValue(autoSelector) < 500)
			displayLCDString(1, 0, "Auto 1 Selected");
		if(SensorValue(autoSelector) > 500 && SensorValue(autoSelector) < 1000)
		  displayLCDString(1, 0, "Auto 2 Selected");
		if(SensorValue(autoSelector) > 1000 && SensorValue(autoSelector) < 1500)
			displayLCDString(1, 0, "Auto 3 Selected");
		if(SensorValue(autoSelector) > 1500 && SensorValue(autoSelector) < 2000)
			displayLCDString(1, 0, "Auto 4 Selected");
		if(SensorValue(autoSelector) > 2000 && SensorValue(autoSelector) < 2500)
			displayLCDString(1, 0, "Auto 5 Selected");
		if(SensorValue(autoSelector) > 2500 && SensorValue(autoSelector) < 3000)
			displayLCDString(1, 0, "Auto 6 Selected");
		if(SensorValue(autoSelector) > 3000 && SensorValue(autoSelector) < 3400)
			displayLCDString(1, 0, "Auto 7 Selected");
		if(SensorValue(autoSelector) > 3400 && SensorValue(autoSelector) < 3800)
			displayLCDString(1, 0, "Auto 8 Selected");
		if(SensorValue(autoSelector) > 3800)
			displayLCDString(1, 0, "Skills Selected");
	}
	if(secondLine == primaryBattery)
	{
		displayLCDString(1, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);
	}
	if(secondLine == secondaryBattery)
	{
		displayLCDString(1, 0, "Backup: ");
		sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
		displayNextLCDString(backupBattery);
	}
	if(secondLine == armEncoder)
	{
		displayLCDString(1, 0, "Enc Value: ");
		sprintf(encoderValue, "%1.2f%c", SensorValue[RightEncoder]);
		displayNextLCDString(encoderValue);
	}
	if(secondLine == leftDrive)
	{
		displayLCDString(1, 0, "Left Val: ");
		sprintf(leftIntEnc, "%1.2f%c", SensorValue[leftDriveEnc]);
		displayNextLCDString(leftIntEnc);
	}
	if(secondLine == rightDrive)
	{
		displayLCDString(1, 0, "Right Val: ");
		sprintf(rightIntEnc, "%1.2f%c", SensorValue[rightDriveEnc]);	//Build the value to be displayed
		displayNextLCDString(rightIntEnc);
	}
	if(secondLine == driveGyro)
	{
		displayLCDString(1, 0, "Gyro Val: ");
		sprintf(accelerometer, "%1.2f%c", SensorValue[gyro]);	//Build the value to be displayed
		displayNextLCDString(accelerometer);
	}
	if(secondLine == antiTipGyro)
	{
		displayLCDString(1, 0, "|Gyro Val: ");
		sprintf(accelerometer, "%1.2f%c", SensorValue[vertGyro]);	//Build the value to be displayed
		displayNextLCDString(accelerometer);
	}
	if(secondLine == accel)
	{
		displayLCDString(1, 0, "Accel Value: ");
		sprintf(accelerometer, "%1.2f%c", SensorValue[accelY]);	//Build the value to be displayed
		displayNextLCDString(accelerometer);
	}
	if(secondLine == none)
	{
		displayLCDString(1, 0, "          ");
	}
}

void animation(int final)
{
	for(int a = 0; a < final+1; a++)
	{
		displayLCDString(0, 0, "            ");
		wait1Msec(10);
		displayLCDString(0, 0, ".");
		wait1Msec(10);
		displayLCDString(0, 0, " .");
		wait1Msec(10);
		displayLCDString(0, 0, "  .");
		wait1Msec(10);
		displayLCDString(0, 0, "   .");
		wait1Msec(10);
		displayLCDString(0, 0, "    .");
		wait1Msec(10);
		displayLCDString(0, 0, "     .");
		wait1Msec(10);
		displayLCDString(0, 0, "      .");
		wait1Msec(10);
		displayLCDString(0, 0, "       .");
		wait1Msec(10);
		displayLCDString(0, 0, "        .");
		wait1Msec(10);
		displayLCDString(0, 0, "         .");
		wait1Msec(10);
		displayLCDString(0, 0, "          .");
		wait1Msec(10);
		displayLCDString(0, 0, "           .");
		wait1Msec(10);
		displayLCDString(0, 0, "          .");
		wait1Msec(10);
		displayLCDString(0, 0, "         .");
		wait1Msec(10);
		displayLCDString(0, 0, "        .");
		wait1Msec(10);
		displayLCDString(0, 0, "       .");
		wait1Msec(10);
		displayLCDString(0, 0, "      .");
		wait1Msec(10);
		displayLCDString(0, 0, "     .");
		wait1Msec(10);
		displayLCDString(0, 0, "    .");
		wait1Msec(10);
		displayLCDString(0, 0, "   .");
		wait1Msec(10);
		displayLCDString(0, 0, "  .");
		wait1Msec(10);
		displayLCDString(0, 0, " .");
		wait1Msec(10);
		displayLCDString(0, 0, ".");
		wait1Msec(10);
		displayLCDString(0, 0, "           ");
		wait1Msec(10);
	}
}

	//void waitForPress()
	//{
	//while(nLCDButtons == 0){}
	//wait1Msec(5);
	//}
	////----------------------------------------------------------------

	////Wait for Release------------------------------------------------
	//void waitForRelease()
	//{
	//while(nLCDButtons != 0){}
	//wait1Msec(5);
	//}



	//	const short leftButton = 1;
	//const short centerButton = 2;
	//const short rightButton = 4;

	////Wait for Press--------------------------------------------------

	//	int count = 0;

	//	//------------- Beginning of User Interface Code ---------------
	//	//Clear LCD
	//	clearLCDLine(0);
	//	clearLCDLine(1);
	//	//Loop while center button is not pressed
	//	while(nLCDButtons != centerButton)
	//	{
	//	//Switch case that allows the user to choose from 4 different options
	//	switch(count){
	//	case 0:
	//	//Display first choice
	//	displayLCDCenteredString(0, "Autonomous 1");
	//	displayLCDCenteredString(1, "<    Enter    >");
	//	waitForPress();
	//	//Increment or decrement "count" based on button press
	//	if(nLCDButtons == leftButton)
	//	{
	//	waitForRelease();
	//	count = 6;
	//	}
	//	else if(nLCDButtons == rightButton)
	//	{
	//	waitForRelease();
	//	count++;
	//	}
	//	break;
	//	case 1:
	//	//Display second choice
	//	displayLCDCenteredString(0, "Autonomous 2");
	//	displayLCDCenteredString(1, "<    Enter    >");
	//	waitForPress();
	//	//Increment or decrement "count" based on button press
	//	if(nLCDButtons == leftButton)
	//	{
	//	waitForRelease();
	//	count--;
	//	}
	//	else if(nLCDButtons == rightButton)
	//	{
	//	waitForRelease();
	//	count++;
	//	}
	//	break;
	//	case 2:
	//	//Display third choice
	//	displayLCDCenteredString(0, "Autonomous 3");
	//	displayLCDCenteredString(1, "<    Enter    >");
	//	waitForPress();
	//	//Increment or decrement "count" based on button press
	//	if(nLCDButtons == leftButton)
	//	{
	//	waitForRelease();
	//	count--;
	//	}
	//	else if(nLCDButtons == rightButton)
	//	{
	//	waitForRelease();
	//	count++;
	//	}
	//	break;
	//	case 3:
	//	//Display fourth choice
	//	displayLCDCenteredString(0, "Autonomous 4");
	//	displayLCDCenteredString(1, "<    Enter    >");
	//	waitForPress();
	//	//Increment or decrement "count" based on button press
	//	if(nLCDButtons == leftButton)
	//	{
	//	waitForRelease();
	//	count--;
	//	}
	//	else if(nLCDButtons == rightButton)
	//	{
	//	waitForRelease();
	//	count++;
	//	}
	//	break;
	//	case 4:
	//	//Display fifth choice
	//	displayLCDCenteredString(0, "Autonomous 5");
	//	displayLCDCenteredString(1, "<    Enter    >");
	//	waitForPress();
	//	//Increment or decrement "count" based on button press
	//	if(nLCDButtons == leftButton)
	//	{
	//	waitForRelease();
	//	count--;
	//	}
	//	else if(nLCDButtons == rightButton)
	//	{
	//	waitForRelease();
	//	count++;
	//	}
	//	break;
	//	case 5:
	//	//Display skills choice
	//	displayLCDCenteredString(0, "Skills Auto");
	//	displayLCDCenteredString(1, "<    Enter    >");
	//	waitForPress();
	//	//Increment or decrement "count" based on button press
	//	if(nLCDButtons == leftButton)
	//	{
	//	waitForRelease();
	//	count--;
	//	}
	//	else if(nLCDButtons == rightButton)
	//	{
	//	waitForRelease();
	//	count++;
	//	}
	//	break;
	//	case 6:
	//	//Display test choice
	//	displayLCDCenteredString(0, "Test Auto");
	//	displayLCDCenteredString(1, "<    Enter    >");
	//	waitForPress();
	//	//Increment or decrement "count" based on button press
	//	if(nLCDButtons == leftButton)
	//	{
	//	waitForRelease();
	//	count--;
	//	}
	//	else if(nLCDButtons == rightButton)
	//	{
	//	waitForRelease();
	//	count = 0;
	//	}
	//	break;
	//	default:
	//	count = 0;
	//	break;
	//	}
	//	}
	//	//------------- End of User Interface Code ---------------------
	//	//------------- Beginning of Robot Movement Code ---------------
	//	//Clear LCD
	//	clearLCDLine(0);
	//	clearLCDLine(1);
	//	//Switch Case that actually runs the user choice
	//	switch(count){
	//	case 0:
	//	//If count = 0, run the code correspoinding with choice 1
	//	displayLCDCenteredString(0, "Autonomous 1");
	//	displayLCDCenteredString(1, "is running!");
	//	                        // Robot waits for 2000 milliseconds

	//	selector = 1;
	//	                           // Robot runs previous code for 3000 milliseconds before moving on
	//	break;
	//	case 1:
	//	//If count = 1, run the code correspoinding with choice 2
	//	displayLCDCenteredString(0, "Autonomous 2");
	//	displayLCDCenteredString(1, "is running!");
	//                        // Robot waits for 2000 milliseconds

	//	// Move reverse at full power for 3 seconds
	//	selector = 2;
	//	                            // Robot runs previous code for 3000 milliseconds before moving on
	//	break;
	//	case 2:
	//	//If count = 2, run the code correspoinding with choice 3
	//	displayLCDCenteredString(0, "Autonomous 3");
	//	displayLCDCenteredString(1, "is running!");
	//	                        // Robot waits for 2000 milliseconds

	//	//Turn right for 3seconds
	//	selector = 3;
	//	                            // Robot runs previous code for 3000 milliseconds before moving on
	//	break;
	//	case 3:
	//	//If count = 3, run the code correspoinding with choice 4
	//	displayLCDCenteredString(0, "Autonomous 4");
	//	displayLCDCenteredString(1, "is running!");
	//                        // Robot waits for 2000 milliseconds

	//	//Turn left for 3 seconds
	//	selector = 4;
	//	                            // Robot runs previous code for 3000 milliseconds before moving on
	//	break;
	//	case 4:
	//	//If count = 3, run the code correspoinding with choice 4
	//	displayLCDCenteredString(0, "Autonomous 5");
	//	displayLCDCenteredString(1, "is running!");
	//	                        // Robot waits for 2000 milliseconds

	//	//Turn left for 3 seconds
	//	selector = 5;
	//	                           // Robot runs previous code for 3000 milliseconds before moving on
	//	break;
	//	case 5:
	//	//If count = 3, run the code correspoinding with choice 4
	//	displayLCDCenteredString(0, "Skills Auto");
	//	displayLCDCenteredString(1, "is running!");
	//	                        // Robot waits for 2000 milliseconds

	//	//Turn left for 3 seconds
	//	selector = 6;
	//                            // Robot runs previous code for 3000 milliseconds before moving on
	//	break;
	//	case 6:
	//	//If count = 3, run the code correspoinding with choice 4
	//	displayLCDCenteredString(0, "Test Auto");
	//	displayLCDCenteredString(1, "is running!");
	//	                       // Robot waits for 2000 milliseconds

	//	//Turn left for 3 seconds
	//	selector = 7;
	//	                           // Robot runs previous code for 3000 milliseconds before moving on
	//	break;
	//	default:
	//	displayLCDCenteredString(0, "No valid choice");
	//	displayLCDCenteredString(1, "was made!");
	//	break;
	//	}
	//	//------------- End of Robot Movement Code -----------------------

/*
Display Code dedicated to Ethan for amazingly keeping track of everything we all do.
*/
