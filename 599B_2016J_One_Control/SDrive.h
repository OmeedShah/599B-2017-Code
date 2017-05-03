#include "Catapult.h"

//New Drive Variables
int forward;
int turn;
int newStrafe;


int driveY;
int driveX;
int strafe;

int DEADZONE = 20;


// UPDATING DRIVE VARIABLES
void driveVariables()
{
	if(driver_uyen)
	{
		driveY = vexRT[Ch3];
		driveX = vexRT[Ch1];
	}
	if(driver_omeed)
	{
		driveY = vexRT[Ch3];
		driveX = vexRT[Ch4] + vexRT[Ch1];
	}
	if(driver_brian)
	{
		driveY = vexRT[Ch3];
		driveX = vexRT[Ch4];
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

		motor[front_left_drive] = forward - newStrafe + turn; //testing for better turn and strafe
		motor[front_right_drive] = forward + newStrafe - turn;
		motor[back_left_drive] = forward + newStrafe + turn;
		motor[back_right_drive] = forward - newStrafe - turn;

}

void gyroClearLoop()
{
	while(true)
	{
		SensorValue[vertGyro] = 0;
		wait1Msec(300);
		SensorValue[vertGyro] = 0;
	}
}

void antiTip()
{
	if(SensorValue[vertGyro] > 5)
	{
		updateDriveMotors(-30,-30);
	}
	if(SensorValue[vertGyro] < -5)
	{
		updateDriveMotors(30,30);
	}
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

/*
Drive Code dedicated to Omeed for being the best VEX driver I've ever seen and one of the best friends a team can provide..
*/
