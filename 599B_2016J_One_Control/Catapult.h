// CATAPULT VARIABLES
int cocksBack;
int shootFwd;
int openClaw;
int closeClaw;
int override;
int halfSpeed;
int scoreButton;
int releaseButton;
int secretButton;
int scoreVal;
int secretOVal;
int secretUVal;
int secretBVal;

int calibrate;
int fold;

int driver_uyen;
int driver_omeed;
int driver_brian;

/*
int rightEncVal;
int leftEncVal;
int encValDiff;
float encDiffRatio;
float encAvg;
*/

void driverSelect(string driver)
{
	string uyen;
	string omeed;
	string brian;

	if(driver == uyen)
	{
		driver_uyen = 1;
		driver_omeed = 0;
		driver_brian = 0;
	}
	if(driver == omeed)
	{
		driver_uyen = 0;
		driver_omeed = 1;
		driver_brian = 0;
	}
	if(driver == brian)
	{
		driver_uyen = 0;
		driver_omeed = 0;
		driver_brian = 1;
	}
}


// UPDATE CATAPULT VARIABLES
void catVariables()
{
	if(driver_uyen)
	{
		shootFwd = vexRT[Btn5D];
		cocksBack = vexRT[Btn5U];
		openClaw = vexRT[Btn6D];
		closeClaw = vexRT[Btn6U];
		override = vexRT[Btn7U];
		scoreButton = vexRT[Btn8U];
		releaseButton = vexRT[Btn7L];
		secretButton = vexRT[Btn8L];
			calibrate = vexRT[Btn8R];
	}
	if(driver_omeed)
	{
		shootFwd = vexRT[Btn5U];
		cocksBack = vexRT[Btn5D];
		openClaw = vexRT[Btn6U];
		closeClaw = vexRT[Btn6D];
		override = vexRT[Btn7U];
		scoreButton = vexRT[Btn8U];
		releaseButton = vexRT[Btn7L];
		calibrate = vexRT[Btn8R];
		fold = vexRT[Btn7R];
		secretButton = vexRT[Btn8L];
	}
	if(driver_brian)
	{
		shootFwd = vexRT[Btn6U];
		cocksBack = vexRT[Btn6D];
		openClaw = vexRT[Btn5U];
		closeClaw = vexRT[Btn5D];
		override = vexRT[Btn7U];
		scoreButton = vexRT[Btn8U];
		releaseButton = vexRT[Btn7L];
		calibrate = vexRT[Btn8R];
		fold = vexRT[Btn7R];
		//secretButton = vexRT[Btn8L];
	}

	//rightEncVal = SensorValue[rightEncoder];
	//leftEncVal = -(SensorValue[leftEncoder]);
	//encValDiff = rightEncVal - leftEncVal; //deadzone
	//encDiffRatio = (1 + abs(encValDiff/360));
	//encAvg = (encValDiff)/2;
}

void updateRightCatMotors(int Speed)
{
	motor[top_right_cat] = Speed;
	motor[bot_right_cat] = -Speed;
}

void updateLeftCatMotors(int Speed)
{
	motor[bot_left_cat] = -Speed;
	motor[top_left_cat] = Speed;
}


// This function is essentially a shortcut for our catapult code.
// It sets the motors all to the same speed, so once the function
// is used elsewhere, all motors move at the same directed speed.
void updateCatMotors(int Speed)
{
	updateRightCatMotors(Speed);
	updateLeftCatMotors(Speed);
}

void releaseBands()
{
	while(SensorValue[RightEncoder] < 180)
	{
		updateCatMotors(127);
	}
	updateCatMotors(0);
	wait1Msec(50);
	while(SensorValue[RightEncoder] > 100)
	{
		updateCatMotors(-127);
	}
	updateCatMotors(0);
}

void calibrateArm()
{
	if(calibrate)
	{
		updateCatMotors(-50);
		wait1Msec(2000);
		updateCatMotors(0);
		SensorValue[RightEncoder] = 0;
	}
}

void raiseArmTeleop()
{
	if(vexRT[Btn8D] == true && SensorValue[RightEncoder] < 90)
	{
		while(SensorValue[RightEncoder] < 70)
		{
			updateCatMotors(70);
		}
		updateCatMotors(0);
	}
	else if(vexRT[Btn8D] == true && SensorValue[RightEncoder] >= 90)
	{
		while(SensorValue[RightEncoder] > 90)
		{
			updateCatMotors(-90);
		}
		updateCatMotors(0);
	}
}

void moveClaw()
{
	if(openClaw)
	{
		motor[left_claw_motor] = 127;
		motor[right_claw_motor] = 127;
	}
	else if(closeClaw)
	{
		motor[left_claw_motor] = -127;
		motor[right_claw_motor] = -127;
	}
	else
	{
		motor[left_claw_motor] = 0;
		motor[right_claw_motor] = 0;
	}
}

// This is the actual code for the catapult. It checks if a button
// is pressed (cocksBack or shootFwd), then acts accordingly. If
// it cocks back, then the motors all move at a speed of 100; if
// it shoots forward, all motors move at a speed of -100. If
// nothing is pressed, the catapult motors do not move.
void catapult()
{
	if(cocksBack == 1)
	{
		updateCatMotors(-100); //goin dwn
	}
	else if(shootFwd == 1 && SensorValue[RightEncoder] < 110 && override == 0)
	{
		updateCatMotors(127);
	}
	else if(shootFwd == 1 && override == 1)
	{
		updateCatMotors(127);
	}
	else
	{
		updateCatMotors(0);
	}

	if(releaseButton == 1)
	{
		releaseBands();
	}
}

void ArmUp(int angle, int speed)
{
	while(SensorValue[RightEncoder] < angle)
	{
		updateCatMotors(speed);
	}
	updateCatMotors(0);
}

void ArmDown(int angle, int speed)
{
	while(SensorValue[RightEncoder] > angle)
	{
		updateCatMotors(-speed);
	}
	updateCatMotors(0);
}

void ClawSpeed(int speed)
{
	motor[left_claw_motor] = speed;
	motor[right_claw_motor] = speed;
}

void foldArm()
{
	if(fold == 1)
	{
		//get the arm and the claw to a "known" position.
		//The arm is down and the claw is closed.
		updateCatMotors(-50);
		ClawSpeed(-70);
		wait1Msec(3500);
		updateCatMotors(0);
		SensorValue[RightEncoder] = 0;

		//Begin raising the arm to get the claw within a certain closed area.
		ClawSpeed(60);
		ArmUp(100,90);
		ClawSpeed(90);
		wait1Msec(100);
		ClawSpeed(0);

		//Lower the arm and ensure the claw is at the folded position.
		ArmDown(0,120);
		ClawSpeed(90);
		wait1Msec(150);
		ClawSpeed(0);
	}
}

void score()
{
	if(scoreButton == 1 && secretButton == 0)
	{
		scoreVal = 1;
	}
	if(driver_omeed == 1 && scoreButton == 1 && secretButton == 1)
	{
		secretOVal = 1;
	}
	else if(driver_omeed == 0 || (scoreButton == 0 || secretButton == 0))
	{
		secretOVal = 0;
	}
	if(driver_uyen == 1 && scoreButton == 1 && secretButton == 1)
	{
		secretUVal = 1;
	}
	else if(driver_uyen == 0 || (scoreButton == 0 || secretButton == 0))
	{
		secretUVal = 0;
	}
	if(driver_brian == 1 && scoreButton == 1 && secretButton == 1)
	{
		secretBVal = 1;
	}
	else if(driver_brian == 0 || (scoreButton == 0 || secretButton == 0))
	{
		secretBVal = 0;
	}
}

/*
void adjustCatapult()
{
	if(abs(encValDiff) > 30)
	{
		if(rightEncVal < leftEncVal)
		{
			updateLeftCatMotors(100);
			updateRightCatMotors(100*encDiffRatio);
		}
		else
		{
			updateLeftCatMotors(100*encDiffRatio);
			updateRightCatMotors(100);
		}
	}
	else
	{
		catapult();
	}
}

void setEncPosition()
{
	if(cocksBack == 1 && shootFwd == 1)
	{
		while((encAvg%360) > 0)
		{
			updateCatMotors(100);
		}
	}
	else
	{
		catapult();
	}
}
*/

/*
Catapult Code dedicated to Shruti for being the true "Star" and propelling 599B over the fence and beyond.
*/
