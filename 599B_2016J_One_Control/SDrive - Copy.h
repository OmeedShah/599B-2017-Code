#include "Catapult.h"
#include "PID.h"

//New Drive Variables
int forward;
int turn;
int newStrafe;


int driveY;
int driveX;
int strafe;

int overrideDrive;

int DEADZONE = 20;




// UPDATING DRIVE VARIABLES
void driveVariables()
{
	if(uyen)
	{
		driveY = vexRT[Ch3];
		driveX = vexRT[Ch1];
		overrideDrive = vexRT[Btn7U];
	}
	if(omeed)
	{
		driveY = vexRT[Ch3];
		driveX = vexRT[Ch4] + vexRT[Ch1];
		overrideDrive = vexRT[Btn7U];
	}
	//strafe = vexRT[Ch4];
}

// This function is essentially a shortcut for our drive code.
// It sets the left and right motors to the left and right side
// of the robot, respectively.
void updateDriveMotors(int left, int right)
{
	motor[front_right_drive] = right;
	motor[front_left_drive] = left;
	motor[back_left_drive] = left;
	motor[back_right_drive] = right;
}

void clearIntegratedEncoders()
{
	if(vexRT[Btn8R] == true)
	{
		nMotorEncoder[back_left_drive] = 0;
		nMotorEncoder[back_right_drive] = 0;
	}
}

//new drive
int setForward(int forVal)
{
	if(abs(forVal) > DEADZONE)
	{
		forward = forVal;
	}
	else
	{
		forward = 0;
	}
	return forward;
}

int setTurn(int turnVal)
{
	if(abs(turnVal) > DEADZONE)
	{
		turn = (turnVal)*0.5;
	}
	else
	{
		turn = 0;
	}
	return turn;
}

int setStrafe(int strafeVal)
{
	if(abs(strafeVal) > DEADZONE)
	{
		newStrafe = strafeVal;
	}
	else
	{
		newStrafe = 0;
	}
	return newStrafe;
}

void newDrive(int forInput, int turnInput, int strafeInput)
{
	setForward(forInput);
	setTurn(turnInput);
	setStrafe(strafeInput);

	if(SensorValue[vertGyro] < 100 && SensorValue[vertGyro] > -100)
	{
		motor[front_left_drive] = forward - newStrafe + turn; //testing for better turn and strafe
		motor[front_right_drive] = forward + newStrafe - turn;
		motor[back_left_drive] = forward + newStrafe + turn;
		motor[back_right_drive] = forward - newStrafe - turn;
	}

	//KAT: Kamen Anti-Tip
	else if(SensorValue[vertGyro] >= 100 && overrideDrive == 0)
	{
		updateDriveMotors(-125,-125);
	}
	//SensorValue[vertGyro] = 0;
	else if(SensorValue[vertGyro] <= -100 && overrideDrive == 0)
	{
		updateDriveMotors(125,125);
	}
	//SensorValue[vertGyro] = 0;
	else if(overrideDrive == 1)
	{
		motor[front_left_drive] = forward - newStrafe + turn; //testing for better turn and strafe
		motor[front_right_drive] = forward + newStrafe - turn;
		motor[back_left_drive] = forward + newStrafe + turn;
		motor[back_right_drive] = forward - newStrafe - turn;
		SensorValue[vertGyro] = 0;
		//updateDriveMotors(0,0);
	}
	else if(SensorValue[vertGyro] <= 100 && SensorValue[vertGyro] >= -100)
	{
		motor[front_left_drive] = forward - newStrafe + turn; //testing for better turn and strafe
		motor[front_right_drive] = forward + newStrafe - turn;
		motor[back_left_drive] = forward + newStrafe + turn;
		motor[back_right_drive] = forward - newStrafe - turn;
	}
}

void decayGyro()
{
	static float decay = SensorValue[vertGyro];
	for(int robodecay = decay; robodecay > 0; robodecay--)
	{
		decay--;
	}
	//decay = decay - 10;
	if(decay <= 0) SensorValue[vertGyro] = 0;
	//SensorValue[vertGyro] = decay;
	//wait1Msec(40);
}

void gyroClearLoop()
{
	static int stable = nPgmTime;
	if(abs(SensorValue[vertGyro]) > 100) stable = nPgmTime;
	if((nPgmTime - stable) == 5000) SensorValue[vertGyro] = 0;
}


/**********************************************************************/
void allDrive()
{
	if(abs(driveY) > DEADZONE)
	{
		motor[front_left_drive] = driveY;
		motor[front_right_drive] = driveY;
		motor[back_left_drive] = driveY;
		motor[back_right_drive] = driveY;
	}
	if(abs(driveX) > DEADZONE)
	{
		motor[front_left_drive] = driveX;
		motor[front_right_drive] = -driveX;
		motor[back_left_drive] = driveX;
		motor[back_right_drive] = -driveX;
	}
	if(abs(strafe) > 60)
	{
		motor[front_right_drive] = strafe;
		motor[front_left_drive] = -strafe;
		motor[back_left_drive] = (strafe/2);
		motor[back_right_drive] = -(strafe/2);
	}
	if(abs(driveY) < DEADZONE && abs(driveX) < DEADZONE && abs(strafe) < DEADZONE)
	{
		motor[front_right_drive] = 0;
		motor[front_left_drive] = 0;
		motor[back_left_drive] = 0;
		motor[back_right_drive] = 0;
	}
}
