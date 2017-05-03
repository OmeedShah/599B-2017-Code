#include "SDrive.h"
#include "Catapult.h"
#include "Vex_Competition_Includes.c"
#include "PID.h"

bool backup = true;
int previousSpeed;
float convertRatio = .91837;

/*
Directory:
?Parameters.....23
?Auto 1.........153
?Auto 2.........193
?Auto 3.........294
?Auto 4.........367
?Auto 5.........438
?Auto 6.........583
?Skills Auto....736
?Test...........1092
*/

void Strafe(int speed)//Line 23
{
	motor[front_right_drive] = speed;
	motor[front_left_drive] = -speed;
	motor[back_left_drive] = speed;
	motor[back_right_drive] = -speed;
}
//Not Used

void setArmUp(int angle, int speed)
{
	while(SensorValue[RightEncoder] < angle)
	{
		updateCatMotors(speed);
	}
	updateCatMotors(0);
}
/*How to use setArmUp:
Write setArmUp and then the desired value of the encoder and the desired speed of the motors*/

void setArmDown(int angle, int speed)
{
	while(SensorValue[RightEncoder] > angle)
	{
		updateCatMotors(-speed);
	}
	updateCatMotors(0);
}
/*How to use setArmDown:
Write setArmDown and then the desired value of the encoder and the desired speed of the motors*/

void driveStraight(int speed,int time)//set speed (-127 - 127) and then time (in milliseconds)
{
	updateDriveMotors(speed,speed);
	wait1Msec(time);
	updateDriveMotors(0,0);
}
/*How to use driveStraight:
Write driveStraight and then the desired speed. The time is amount it will be running.*/

void clearGyro()
{
	SensorValue[gyro] = 0;
	wait1Msec(20);
}

void releaseClaw()
{
	motor[left_claw_motor] = 85;
	motor[right_claw_motor] = 85;
	wait1Msec(300);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;
}

void setClawSpeed(int speed)
{
	motor[left_claw_motor] = speed;
	motor[right_claw_motor] = speed;
}
/*How to use setClawSpeed:
Write setClawSpeed and then the motor speed.*/

bool contingencyPlan(int time)
{
	{
		backup = true;
		wait1Msec(time);
	//wait10Msec(500);
	//updateBackup(0);
	//wait1Msec(10000);
	//updateBackup(1);
	//return backup == 1;
	}
	return backup == false;
}

/*How to use contingencyPlan:
Use before while loops with integrated encoders.
Write contingencyPlan(); with the proper time amount in the ().
Then, in the while loop, create an || (or) statement which says backup == true.*/


//managed dynamic acceleration profile:
int rampDown(int speed, int cycle, int increment)
{
	for(int robotSpeed = 0; robotSpeed < cycle; robotSpeed++)
	{
		updateDriveMotors(speed = speed - increment,speed = speed - increment);
		previousSpeed = robotSpeed;
		wait1Msec(50);//wait for update loop
	}
	if(speed < 0)
	updateDriveMotors(0,0);
	return previousSpeed;
}
/*How to use rampDown:
Write rampDown and then the speed amount, amount of cycles you want the code to run, and then the increment amount.
(Default should be (127,30,2))
You can also write previousSpeed for the speed amount if this is following a rampUp.*/

int rampUp(int speed,int cycle,int increment)
{
	for(int robotSpeed = 0; robotSpeed < cycle; robotSpeed++)
	{
		updateDriveMotors(speed = speed + increment,speed = speed + increment);
		previousSpeed = speed;
		wait1Msec(50);//wait for update loop
	}
	//updateDriveMotors(127,127);
	return previousSpeed;
}
/*How to use rampUp:
Write rampUp and then the speed amount, amount of cycles you want the code to run, and then the increment amount.
(Default should be (30,30,2))
You can also write previousSpeed for the speed amount if this is following a rampDown.*/

void accelerate(int speed, int time)
{
	if(time<1000)
	time = 1000;
	rampUp(speed,13,3);
	wait1Msec(time - 1000);
	rampDown(previousSpeed,13,3);
	updateDriveMotors(0,0);
}
/*How to use accelerate:
Write accelerate and then the INITIAL speed amount followed by the amount of TOTAL time you want this to run.*/

//----------------------------------------------------------------------------------------------------------//

void auto1()//Line 153
//Drives forward to hit stars off of fence. Either side
{
	displayLCDCenteredString(0, "Now Playing...");
	displayLCDCenteredString(1, "   Auto 1   ");
	//Lift Arms
	//copy and paste below \/
	motor[left_claw_motor] = -36;
	motor[right_claw_motor] = -36;
	//wait1Msec(200);

	//drive forward and lift arm
	updateDriveMotors(110,110);
	SensorValue[RightEncoder] = 0;
	while(SensorValue[RightEncoder] < 65)
	{
		updateCatMotors(127);
	}
	updateCatMotors(0);
	wait1Msec(500);
	SensorValue[RightEncoder] = 0;

	//closing claws
	wait1Msec(310);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;

	//Drive forward

	wait1Msec(475);
	updateDriveMotors(0,0);
	wait1Msec(400);

	//Driving backwards
	updateDriveMotors(-90,-90);
	wait1Msec(150);    //to be changed 50
	updateDriveMotors(0,0);
	wait1Msec(200);

}
void auto2()//Line 193
//Grabs cube and drops it in the center Starts left side.
{
	displayLCDCenteredString(0, "Now Playing...");
	displayLCDCenteredString(1, "   Auto 2   ");

	setClawSpeed(-70);
	wait1Msec(100);
	setClawSpeed(0);

	driveStraight(95,500);
	wait1Msec(500);

	//Turn Right 90 degrees
	updateDriveMotors(120,-120);
	wait1Msec(500);//TODO: Get correct value
	updateDriveMotors(0,0);

	driveStraight(105,500);
	wait1Msec(200);

	//backup
	updateDriveMotors(-70,-70);
	wait1Msec(200);
	updateDriveMotors(0,0);

	//lower catapult
	//setClawSpeed(60);
	//wait1Msec(200);
	updateCatMotors(90);
	wait1Msec(100);
	updateCatMotors(0);
	wait1Msec(100);
	updateDriveMotors(50,50);
	wait1Msec(200);
	updateDriveMotors(0,0);

	//Close claws
	motor[left_claw_motor] = -80; //temp
	motor[right_claw_motor] = -80;
	wait1Msec(500);
	updateCatMotors(-100);
	wait1Msec(100);
	updateCatMotors(0);
	wait1Msec(800);

	//Lift arms up
	updateCatMotors(120);
	wait1Msec(500);
	updateCatMotors(0);
	wait1Msec(500);

	//Drive forward
	updateDriveMotors(105,105);
	wait1Msec(450);
	updateDriveMotors(0,0);
	wait1Msec(200);

	//Turn left 90 degrees
	updateDriveMotors(127,-127);
	wait1Msec(1200);//TODO: Get correct value
	updateDriveMotors(0,0);

	updateCatMotors(85);

	//Drive forward toward gate
	updateDriveMotors(-127,-127);
	wait1Msec(1100);
	updateDriveMotors(0,0);
	//wait1Msec(200);

	//Open claws
	motor[left_claw_motor] = 60; //temp
	motor[right_claw_motor] = 60;
	wait1Msec(300);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;
	updateCatMotors(0);
	wait1Msec(500);
	updateDriveMotors(-100,-100);
	wait1Msec(500);
	updateCatMotors(-85);
	wait1Msec(200);
	updateDriveMotors(0,0);
	updateCatMotors(0);

	//close claws
	//motor[left_claw_motor] = -80; //temp
	//motor[right_claw_motor] = -80;
	//wait1Msec(300);
	//motor[left_claw_motor] = 0;
	//motor[right_claw_motor] = 0;
	//wait1Msec(150);
	//updateCatMotors(0);
	//wait1Msec(500);

	////Back up
	//updateDriveMotors(-127,-127);
	//wait1Msec(200);
	//updateDriveMotors(0,0);
	//wait1Msec(200);

	////open claws
	//motor[left_claw_motor] = 60; //temp
	//motor[right_claw_motor] = 60;
	//wait1Msec(300);
	//motor[left_claw_motor] = 0;
	//motor[right_claw_motor] = 0;
	//wait1Msec(500);

	////forward
	//updateDriveMotors(127,127);
	//wait1Msec(200);
	//updateDriveMotors(0,0);
	//wait1Msec(200);
}

void auto3()//Line 294
//Swipes stars off of right fence and then swipes the center. Starts from right side.
{
	displayLCDCenteredString(0, "Now Playing...");
	displayLCDCenteredString(1, "   Auto 3   ");

	//close claws and lift arm
	motor[left_claw_motor] = -55;
	motor[right_claw_motor] = -55;
	SensorValue[RightEncoder] = 0;
	while(SensorValue[RightEncoder] < 65)
	{
		updateCatMotors(127);
	}
	updateCatMotors(0);
//	wait1Msec(500);
	SensorValue[RightEncoder] = 0;

	//closing claws
	wait1Msec(510);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;
	wait1Msec(200);

	//Drive forward
	updateDriveMotors(127,127);
	wait1Msec(1500);
	updateDriveMotors(0,0);
	wait1Msec(400);

	//Driving backwards
	updateDriveMotors(-100,-100);
	wait1Msec(150);    //to be changed 50
	updateDriveMotors(0,0);
	wait1Msec(200);

	//Turning 90 degrees left
	SensorValue[gyro] = 0;
	while(abs(SensorValue(gyro)) < 490)
	{
		updateDriveMotors(-80,80);
	}
	if(abs(SensorValue(gyro)) >= 490)
	{
		updateDriveMotors(0,0);
	}

	//bring arms down
	updateCatMotors(-83);
	wait1Msec(150);
	updateCatMotors(0);
	wait1Msec(270);
	updateDriveMotors(0,0);
	wait1Msec(100);

	//drive forward
	updateDriveMotors(125,125);
	wait1Msec(300);
	updateDriveMotors(100,125);
	wait1Msec(1100);
	updateDriveMotors(0,0);

	//lift arms up
	updateCatMotors(127);
	wait1Msec(200);
	updateCatMotors(0);
	wait1Msec(100);

	//turn left
	updateDriveMotors(-80,80);
	wait1Msec(200);
	updateDriveMotors(0,0);
}

void auto4()//Line 367
//
{
	displayLCDCenteredString(0, "Now Playing...");
	displayLCDCenteredString(1, "   Auto 4   ");

	//close claws and lift arm
	motor[left_claw_motor] = -53;
	motor[right_claw_motor] = -53;
	SensorValue[RightEncoder] = 0;
	while(SensorValue[RightEncoder] < 60)
	{
		updateCatMotors(127);
	}
	updateCatMotors(10);
	SensorValue[RightEncoder] = 0;

	//closing claws
	wait1Msec(510);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;
	wait1Msec(200);

	//Drive forward
	updateDriveMotors(127,127);
	wait1Msec(1650);
	updateDriveMotors(0,0);

	//Driving backwards
	updateDriveMotors(-110,-110);
	wait1Msec(230);    //to be changed 50
	updateDriveMotors(0,0);
	wait1Msec(200);

	//Turning 90 degrees left
	SensorValue[gyro] = 0;
	while(abs(SensorValue(gyro)) < 490)
	{
		updateDriveMotors(80,-80);
	}
	if(abs(SensorValue(gyro)) >= 490)
	{
		updateDriveMotors(0,0);
	}

		//bring arms down
	updateCatMotors(-84);
	wait1Msec(150);
	updateCatMotors(0);
	wait1Msec(270);
	updateDriveMotors(0,0);
	wait1Msec(100);

	//drive forward
	updateDriveMotors(125,100);
	wait1Msec(1600);
	updateDriveMotors(0,0);

	//lift arms up
	updateCatMotors(127);
	wait1Msec(200);
	updateCatMotors(0);
	wait1Msec(100);

	//turn right
	updateDriveMotors(80,-80);
	wait1Msec(300);
	updateDriveMotors(0,0);
}
void auto5()//Line 438
//Swipes stars off of right fence and then throws cube over. Starts on right side.
{
	displayLCDCenteredString(0, "Now Playing...");
	displayLCDCenteredString(1, "   Auto 5   ");

	static controlPID_t theGyro;
	SensorValue[gyro] = 0;

	//close claws and lift arm
	motor[left_claw_motor] = -55;
	motor[right_claw_motor] = -55;
	wait1Msec(105);
	SensorValue[RightEncoder] = 0;
	while(SensorValue[RightEncoder] < 65)
	{
		updateCatMotors(127);
	}
	updateCatMotors(10);
	wait1Msec(100);
	SensorValue[RightEncoder] = 0;

	//closing claws
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;
	wait1Msec(200);

	//Drive forward
	//updateDriveMotors(127,127);
	rampUp(30,30,2);
	wait1Msec(300);
	//wait1Msec(1850);//1750
	updateDriveMotors(0,0);
	wait1Msec(400);

	//Driving backwards
	updateDriveMotors(-80,-80);
	wait1Msec(170);    //to be changed 50
	updateDriveMotors(0,0);
	wait1Msec(200);

	driveStraight(-120,580);

	//Turning 90 degrees left
	SensorValue[gyro] = 0;
	while(abs(SensorValue(gyro)) < 545)
	{
		updateDriveMotors(-65,65);
	}
	if(abs(SensorValue(gyro)) >= 545)
	{
		updateDriveMotors(0,0);
	}

	//bring arms down
	updateCatMotors(-80);
	wait1Msec(120);
	updateCatMotors(0);
	wait1Msec(300);
	updateCatMotors(-127);
	wait1Msec(800);
	updateCatMotors(0);
	wait1Msec(100);

	//drive forward
	updateDriveMotors(95,95);
	wait1Msec(500);
	updateDriveMotors(0,0);

	//close claws
	motor[left_claw_motor] = -95;
	motor[right_claw_motor] = -95;
	wait1Msec(700);

	//raise arm up
	SensorValue[gyro] = 0;
	updateCatMotors(127);
	wait1Msec(680);
	updateCatMotors(10);

	driveStraight(120,830);

	//turn left
	SensorValue[gyro] = 0;
	wait1Msec(20);
	while(abs(SensorValue(gyro)) < 555)
	{
		updateDriveMotors(-65,65);
	}
	if(abs(SensorValue(gyro)) >= 555)
	{
		updateDriveMotors(0,0);
	}

	//drive backward
	updateDriveMotors(-117,-117);
	wait1Msec(670);

	//raise arm and stop driving
	updateCatMotors(127);
	wait1Msec(450);
	updateDriveMotors(0,0);
	//wait1Msec(155);

	//open claws
	motor[left_claw_motor] = 90;
	motor[right_claw_motor] = 90;
	wait1Msec(535);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;
	updateCatMotors(10);

	//lower arm
	updateCatMotors(-92);
	wait1Msec(370);
	updateCatMotors(0);

	//180 gyro turn (PID)
	updateDriveMotors(120,120);
	wait1Msec(550);
	clearGyro();
	initPID(theGyro, 0.335, 0.23, 0.26, 200, 5000, 1800);
	while(theGyro.isMoving)
	{
		theGyro.currentValue = SensorValue(gyro);

		int motorValue = calcPID(theGyro);

		if(motorValue > 60)
		{
			motorValue = 60;
		}
		if(motorValue < -60)
		{
			motorValue = -60;
		}
		updateDriveMotors(-motorValue,motorValue);
		wait1Msec(40);
	}
	wait1Msec(100);

	//knock off stars
	updateDriveMotors(120,120);
	wait1Msec(470);
	updateDriveMotors(0,0);
	wait1Msec(100);
	updateDriveMotors(-127,-127);
	wait1Msec(350);
	updateDriveMotors(0,0);
}

void auto6()//Line 583
//Swipes stars off of left fence and then throws cube over. Starts on left side.
{
	displayLCDCenteredString(0, "Now Playing...");
	displayLCDCenteredString(1, "   Auto 6   ");

	static controlPID_t theGyro;
	SensorValue[gyro] = 0;

	//close claws and lift arm
	motor[left_claw_motor] = -58;
	motor[right_claw_motor] = -58;
	wait1Msec(175);
	SensorValue[RightEncoder] = 0;
	while(SensorValue[RightEncoder] < 64)
	{
		updateCatMotors(127);
	}
	updateCatMotors(10);
	wait1Msec(200);
	SensorValue[RightEncoder] = 0;

	//closing claws
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;
	wait1Msec(200);

	//Drive forward
	updateDriveMotors(107,127);
	wait1Msec(1750);
	updateDriveMotors(0,0);
	wait1Msec(400);

	//Driving backwards
	updateDriveMotors(-70,-80);
	wait1Msec(150);    //to be changed 50
	updateDriveMotors(0,0);

	driveStraight(-120,560);

	//Turning 90 degrees right
	//SensorValue[gyro] = 0;
	//while(abs(SensorValue(gyro)) > -460)
	//{
	//	updateDriveMotors(65,-65);
	//}
	//if(abs(SensorValue(gyro)) <= -460)
	//{
	//	updateDriveMotors(0,0);
	//}
	SensorValue[leftDriveEnc] = 0;
	SensorValue[rightDriveEnc] = 0;
	while(SensorValue[leftDriveEnc] < (/*convertRatio*-405*/ 369) && SensorValue[rightDriveEnc] < (/*convertRatio*-315*/369)/*nMotorEncoder[back_left_drive] > -405 && nMotorEncoder[back_right_drive] > -315*/)
	{
		updateDriveMotors(60,-60);
	}
	updateDriveMotors(0,0);

	//bring arms down
	updateCatMotors(-80);
	wait1Msec(120);
	updateCatMotors(0);
	wait1Msec(300);

	//lower arm
	updateCatMotors(-127);
	wait1Msec(800);
	updateCatMotors(0);
	wait1Msec(100);

	//drive forward
	updateDriveMotors(95,95);
	wait1Msec(500);
	updateDriveMotors(0,0);

	//close claws
	motor[left_claw_motor] = -95;
	motor[right_claw_motor] = -95;
	wait1Msec(700);

	//raise arm
	SensorValue[gyro] = 0;
	updateCatMotors(127);
	wait1Msec(500);
	updateCatMotors(0);

	driveStraight(120,840);

	//right turn
	//SensorValue[gyro] = 0;
	//while(abs(SensorValue(gyro)) > -500)
	//{
	//	updateDriveMotors(-65,65);
	//}
	//if(abs(SensorValue(gyro)) <= -500)
	//{
	//	updateDriveMotors(0,0);
	//}
	//SensorValue[leftDriveEnc] = 0;
	//SensorValue[rightDriveEnc] = 0;
	//nMotorEncoder[back_left_drive] = 0;
	//nMotorEncoder[back_right_drive] = 0;
	//while(SensorValue[leftDriveEnc] < (/*convertRatio*-405*/ 455) && SensorValue[rightDriveEnc] < (/*convertRatio*-315*/455)/*nMotorEncoder[back_left_drive] > -405 && nMotorEncoder[back_right_drive] > -315*/)
	//{
	//	updateDriveMotors(95,-95);
	//}
	//updateDriveMotors(0,0);
	updateDriveMotors(127,-127);
	wait1Msec(1200);//TODO: Get correct value
	updateDriveMotors(0,0);

	//drive backward
	updateDriveMotors(-100,-100);
	wait1Msec(400);

	//raise arm and stop driving
	updateCatMotors(117);
	wait1Msec(560);
	updateDriveMotors(0,0);

	//open claws
	motor[left_claw_motor] = 89;
	motor[right_claw_motor] = 89;
	wait1Msec(560);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;
	updateCatMotors(10);
	wait1Msec(100);

	//lower arm
	updateCatMotors(-120);
	wait1Msec(500);
	updateCatMotors(0);

	//180 degree gyro turn (PID)
	updateDriveMotors(120,120);
	wait1Msec(450);
	clearGyro();
	initPID(theGyro, 0.335, 0.23, 0.26, 200, 5000, 1800);
	while(theGyro.isMoving)
	{
		theGyro.currentValue = SensorValue(gyro);

		int motorValue = calcPID(theGyro);

		if(motorValue > 60)
		{
			motorValue = 60;
		}
		if(motorValue < -60)
		{
			motorValue = -60;
		}
		updateDriveMotors(-motorValue,motorValue);
		wait1Msec(40);
	}
	wait1Msec(100);

	//knock off stars
	updateDriveMotors(120,120);
	wait1Msec(410);
	updateDriveMotors(0,0);
}

void auto7()
{
	displayLCDCenteredString(0, "Now Playing...");
	displayLCDCenteredString(1, "   Auto 7   ");

	static controlPID_t theGyro;
	SensorValue[gyro] = 0;

	setClawSpeed(-32);
	setArmUp(65,110);
	setClawSpeed(-40);
	wait1Msec(1500);
	setClawSpeed(-10);
	setArmDown(0,110);
	//wait1Msec(100);
	updateDriveMotors(127,127);
	setClawSpeed(-22);
	wait1Msec(750);
	updateDriveMotors(0,0);
	setClawSpeed(-65);
	wait1Msec(500);
	setArmUp(60,120);
	updateDriveMotors(-127,-75);
	wait1Msec(558);
	setClawSpeed(0);
	wait1Msec(470);

	SensorValue[gyro] = 0;
	wait1Msec(20);
	while(abs(SensorValue(gyro)) < 600)
	{
		updateDriveMotors(-75,75);
	}
	if(abs(SensorValue(gyro)) >= 600)
	{
		updateDriveMotors(0,0);
	}
	updateDriveMotors(-120,-120);
	wait1Msec(700);
	updateCatMotors(127);
	wait1Msec(700);
	setClawSpeed(95);
	updateCatMotors(0);
	updateDriveMotors(0,0);
	wait1Msec(500);
	setClawSpeed(0);

	setArmDown(105,120);
	wait1Msec(100);
	driveStraight(120,750);

	clearGyro();
	initPID(theGyro, 0.335, 0.23, 0.26, 200, 5000, 1800);
	while(theGyro.isMoving)
	{
		theGyro.currentValue = SensorValue(gyro);

		int motorValue = calcPID(theGyro);

		if(motorValue > 60)
		{
			motorValue = 60;
		}
		if(motorValue < -60)
		{
			motorValue = -60;
		}
		updateDriveMotors(-motorValue,motorValue);
		wait1Msec(40);
	}

	driveStraight(120,850);
	driveStraight(-100,300);
}

void auto8()
{
	displayLCDCenteredString(0, "Now Playing...");
	displayLCDCenteredString(1, "   Auto 8   ");

	static controlPID_t theGyro;
	SensorValue[gyro] = 0;

	setClawSpeed(-32);
	setArmUp(65,110);
	setClawSpeed(-40);
	wait1Msec(1500);
	setClawSpeed(-10);
	wait1Msec(200);
	setArmDown(0,110);
	//wait1Msec(100);
	updateDriveMotors(122,122);
	setClawSpeed(-22);
	wait1Msec(750);
	updateDriveMotors(0,0);
	setClawSpeed(-65);
	wait1Msec(500);
	setArmUp(60,120);
	updateDriveMotors(-55,-127);
	wait1Msec(578);
	setClawSpeed(0);
	wait1Msec(470);

	SensorValue[leftDriveEnc] = 0;
	SensorValue[rightDriveEnc] = 0;
	nMotorEncoder[back_left_drive] = 0;
	nMotorEncoder[back_right_drive] = 0;
	while(SensorValue[leftDriveEnc] < (/*convertRatio*-405*/ 509) && SensorValue[rightDriveEnc] < (/*convertRatio*-315*/509)/*nMotorEncoder[back_left_drive] > -405 && nMotorEncoder[back_right_drive] > -315*/)
	{
		updateDriveMotors(127,-127);
	}
	updateDriveMotors(-120,-120);
	wait1Msec(900);
	updateCatMotors(117);
	wait1Msec(500);
	setClawSpeed(115);
	updateCatMotors(0);
	updateDriveMotors(0,0);
	wait1Msec(500);
	setClawSpeed(0);

	setArmDown(100,120);
	wait1Msec(100);
	driveStraight(120,750);

	clearGyro();
	initPID(theGyro, 0.335, 0.23, 0.26, 200, 5000, 1800);
	while(theGyro.isMoving)
	{
		theGyro.currentValue = SensorValue(gyro);

		int motorValue = calcPID(theGyro);

		if(motorValue > 60)
		{
			motorValue = 60;
		}
		if(motorValue < -60)
		{
			motorValue = -60;
		}
		updateDriveMotors(-motorValue,motorValue);
		wait1Msec(40);
	}

	driveStraight(120,850);
	driveStraight(-100,300);
}

void auto9()
{
	displayLCDCenteredString(0, "Now Playing...");
	displayLCDCenteredString(1, "   Auto 9   ");

	static controlPID_t theGyro;
	SensorValue[gyro] = 0;

	//Lift Arms
	//copy and paste below \/
	motor[left_claw_motor] = -42;
	motor[right_claw_motor] = -42;
	//wait1Msec(200);

	//drive forward and lift arm
	updateDriveMotors(110,110);
	SensorValue[RightEncoder] = 0;
	while(SensorValue[RightEncoder] < 65)
	{
		updateCatMotors(127);
	}
	updateCatMotors(0);
	wait1Msec(500);
	SensorValue[RightEncoder] = 0;

	//closing claws
	wait1Msec(310);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;

	//Drive forward

	wait1Msec(475);
	updateDriveMotors(0,0);
	wait1Msec(400);

	//Driving backwards
	updateDriveMotors(-110,-110);
	wait1Msec(1600);    //to be changed 50
	updateDriveMotors(0,0);
	wait1Msec(200);

	setClawSpeed(90);
	setArmDown(0,120);
	wait1Msec(100);
	setClawSpeed(0);

	updateDriveMotors(90,90);
	wait1Msec(200);
	updateDriveMotors(0,0);
	wait1Msec(10);

	updateDriveMotors(-120,120);
	wait1Msec(500);//TODO: Get correct value
	updateDriveMotors(0,0);

	setClawSpeed(-32);
	setArmUp(65,110);
	setClawSpeed(-40);
	wait1Msec(1500);
	setClawSpeed(-10);
	setArmDown(0,110);
	//wait1Msec(100);
	updateDriveMotors(122,122);
	setClawSpeed(-25);
	wait1Msec(720);
	updateDriveMotors(0,0);
	setClawSpeed(-65);
	wait1Msec(500);
	setArmUp(60,120);
	updateDriveMotors(-127,-75);
	wait1Msec(578);
	setClawSpeed(0);
	wait1Msec(470);

	SensorValue[gyro] = 0;
	wait1Msec(20);
	while(abs(SensorValue(gyro)) < 600)
	{
		updateDriveMotors(-75,75);
	}
	if(abs(SensorValue(gyro)) >= 600)
	{
		updateDriveMotors(0,0);
	}
	updateDriveMotors(-120,-120);
	wait1Msec(700);
	updateCatMotors(127);
	wait1Msec(700);
	setClawSpeed(100);
	updateCatMotors(0);
	updateDriveMotors(0,0);
	wait1Msec(500);
	setClawSpeed(0);
}

void auto10()
{
	displayLCDCenteredString(0, "Now Playing...");
	displayLCDCenteredString(1, "   Auto 10   ");

	static controlPID_t theGyro;
	SensorValue[gyro] = 0;

	//Lift Arms
	//copy and paste below \/
	motor[left_claw_motor] = -42;
	motor[right_claw_motor] = -42;
	//wait1Msec(200);

	//drive forward and lift arm
	updateDriveMotors(110,110);
	SensorValue[RightEncoder] = 0;
	while(SensorValue[RightEncoder] < 65)
	{
		updateCatMotors(127);
	}
	updateCatMotors(0);
	wait1Msec(500);
	SensorValue[RightEncoder] = 0;

	//closing claws
	wait1Msec(310);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;

	//Drive forward

	wait1Msec(475);
	updateDriveMotors(0,0);
	wait1Msec(400);

	//Driving backwards
	updateDriveMotors(-110,-110);
	wait1Msec(1450);    //to be changed 50
	updateDriveMotors(0,0);
	wait1Msec(200);

	setClawSpeed(90);
	setArmDown(0,120);
	wait1Msec(100);
	setClawSpeed(0);

	updateDriveMotors(90,90);
	wait1Msec(200);
	updateDriveMotors(0,0);
	wait1Msec(10);

	updateDriveMotors(120,-120);
	wait1Msec(500);//TODO: Get correct value
	updateDriveMotors(0,0);

	setClawSpeed(-32);
	setArmUp(65,110);
	setClawSpeed(-40);
	wait1Msec(1500);
	setClawSpeed(-10);
	wait1Msec(200);
	setArmDown(0,110);
	//wait1Msec(100);
	updateDriveMotors(122,122);
	setClawSpeed(-25);
	wait1Msec(740);
	updateDriveMotors(0,0);
	setClawSpeed(-65);
	wait1Msec(500);
	setArmUp(60,120);
	updateDriveMotors(-55,-127);
	wait1Msec(578);
	setClawSpeed(0);
	wait1Msec(470);

	SensorValue[leftDriveEnc] = 0;
	SensorValue[rightDriveEnc] = 0;
	nMotorEncoder[back_left_drive] = 0;
	nMotorEncoder[back_right_drive] = 0;
	while(SensorValue[leftDriveEnc] < (/*convertRatio*-405*/ 509) && SensorValue[rightDriveEnc] < (/*convertRatio*-315*/509)/*nMotorEncoder[back_left_drive] > -405 && nMotorEncoder[back_right_drive] > -315*/)
	{
		updateDriveMotors(127,-127);
	}
	updateDriveMotors(-120,-120);
	wait1Msec(900);
	updateCatMotors(117);
	wait1Msec(500);
	setClawSpeed(95);
	updateCatMotors(0);
	updateDriveMotors(0,0);
	wait1Msec(500);
	setClawSpeed(0);
}

void noCode()
{
	updateDriveMotors(0,0);
	updateCatMotors(0);
	setClawSpeed(0);
}

void skillsAuto()//Line 736
//Part 1: Throws 2 cubes over while hitting 2 stars and throws 2 stars over.
//Part 2: Grabs the center cube and then throws it on the right side.
//Part 3: Grabs the last cube and throws that over.
//Part 4: Grabs 3 more stars and swipes another 1-3.
{
	static controlPID_t theGyro;
	//Part 1: 2 Kyubeys, 5 Stars  [][] *****--------
	displayLCDCenteredString(0, "Part 1:");
	displayLCDCenteredString(1, "2 Cubes, 5 Stars");

	//close claw & lift arm
	SensorValue[RightEncoder] = 0;
	setClawSpeed(-90);
	wait1Msec(150);
	setArmUp(60,127);

	//set new speed for arm
	wait1Msec(900);
	setClawSpeed(-70);
	wait1Msec(500);

	//drive forward
	rampUp(30,30,2);
	wait1Msec(100);
	updateDriveMotors(0,0);

	setArmUp(75,100);
	wait1Msec(200);

	driveStraight(120,300);
	wait1Msec(200);

	//Back up slightly
	driveStraight(-80,250);

	//gyro guided 180 degree turn
	clearGyro();
	initPID(theGyro, 0.340, 0.23, 0.26, 200, 5000, 1800);
	while(theGyro.isMoving)
	{
		theGyro.currentValue = SensorValue(gyro);

		int motorValue = calcPID(theGyro);

		if(motorValue > 60)
		{
			motorValue = 60;
		}
		if(motorValue < -60)
		{
			motorValue = -60;
		}
		updateDriveMotors(-motorValue,motorValue);
		wait1Msec(40);
	}
	updateDriveMotors(0,0);
	updateDriveMotors(-95,-95);
	wait1Msec(100);

	//throw cube
	while(SensorValue[RightEncoder] < 120)
	{
		updateCatMotors(80);
	}
	updateCatMotors(0);
	motor[left_claw_motor] = 85;
	motor[right_claw_motor] = 85;
	wait1Msec(100);
	updateDriveMotors(0,0);
	wait1Msec(600);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;

	//lower arm back to grabbing position
	while(SensorValue[RightEncoder] > 100)
	{
		updateCatMotors(-45);
	}
	updateCatMotors(0);

	//drive forward
	//driveStraight(127,1200);
	//rampUp(50,2,40);
	//rampDown(100,4,25);
	rampUp(30,26,2);
	updateDriveMotors(0,0);


	wait1Msec(1000);

	//close claws
	motor[left_claw_motor] = -95;
	motor[right_claw_motor] = -95;
	wait1Msec(800);

	//drive backward toward gate
	updateDriveMotors(-127,-127);
	wait1Msec(800);

	//set arm over gate
	while(SensorValue[RightEncoder] < 120)
	{
		updateCatMotors(67);
	}
	updateCatMotors(0);
	motor[left_claw_motor] = 80;
	motor[right_claw_motor] = 80;
	wait1Msec(100);
	updateDriveMotors(0,0);

	//release cube
	wait1Msec(600);
	motor[left_claw_motor] = -40;
	motor[right_claw_motor] = -40;
	wait1Msec(500);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;
	wait1Msec(100);

	//raise arm up
	while(SensorValue[RightEncoder] > 10)
	{
		updateCatMotors(-60);
	}
	updateCatMotors(0);
	wait1Msec(200);

	//drive forward
	rampUp(30,26,2);
	updateDriveMotors(0,0);
	wait1Msec(400);

	//close claws
	motor[left_claw_motor] = -95;
	motor[right_claw_motor] = -95;
	wait1Msec(800);

	//drive backward toward gate
	updateDriveMotors(-127,-127);
	wait1Msec(600);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;
	motor[left_claw_motor] = -105;
	motor[right_claw_motor] = -105;
	wait1Msec(100);

	//set arm over gate
	while(SensorValue[RightEncoder] < 120)
	{
		updateCatMotors(127);
	}
	updateCatMotors(0);
	updateDriveMotors(0,0);

	//release stars
	releaseClaw();
	wait1Msec(300);

	//Part 2: Kyubey Central []*----------
	displayLCDCenteredString(0, "Part 2:");
	displayLCDCenteredString(1, "  Cube Central  ");

	//lower arm to floor
	setArmDown(70,127);
	wait1Msec(200);

	driveStraight(115,700);
	wait1Msec(100);

	//turn to face cube
	//contingencyPlan(500);
	SensorValue[leftDriveEnc] = 0;
	SensorValue[rightDriveEnc] = 0;
	nMotorEncoder[back_left_drive] = 0;
	nMotorEncoder[back_right_drive] = 0;
	while(SensorValue[leftDriveEnc] > (/*convertRatio*420*/-300) && SensorValue[rightDriveEnc] > (/*convertRatio*420*/-300)/*(nMotorEncoder[back_left_drive] < 365 && nMotorEncoder[back_right_drive] < 365) || backup == true*/)
	{
		updateDriveMotors(-87,87);
	}
	updateDriveMotors(0,0);
	wait1Msec(200);
	//left:360 right:253

	//aim arm at cube
	setArmDown(10,127);
	wait1Msec(200);
	updateDriveMotors(127,127);
	wait1Msec(500);
	updateDriveMotors(0,0);

	//begin closing claws
	setClawSpeed(-85);
	wait1Msec(350);

	//leave with cube
	setArmUp(50,100);
	wait1Msec(300);
	rampUp(30,25,2);
  wait1Msec(100);
	updateDriveMotors(0,0);
	wait1Msec(200);

	//lift arm up
	setArmUp(60,100);

	//stop closing claws (to prevent breaking the stars)
	setClawSpeed(-20);
	wait1Msec(200);

	//turn right
	updateDriveMotors(107,-107);
	wait1Msec(750);//TODO: Get correct value
	updateDriveMotors(0,0);
	wait1Msec(200);

	//drive back
	updateDriveMotors(-80,-80);
	wait1Msec(800);

	//raise arm
	updateCatMotors(120);
	wait1Msec(700);
	updateDriveMotors(0,0);
	updateCatMotors(0);

	//releaseClaw();
	motor[left_claw_motor] = 95;
	motor[right_claw_motor] = 95;
	wait1Msec(200);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;
	wait1Msec(200);

	//lower arm to floor
	setArmDown(10,100);
	wait1Msec(200);

	//Part 3: The Final Kyubey []----
	displayLCDCenteredString(0, "Part 3:");
	displayLCDCenteredString(1, "The Final Cube");

	driveStraight(100,900);
	wait1Msec(200);

	setClawSpeed(-85);
	wait1Msec(600);

	setArmUp(70,120);
	wait1Msec(200);

	updateDriveMotors(-100,-100);
	wait1Msec(730);

	//raise up arm and ensure no drive motion
	updateCatMotors(127);
	wait1Msec(120);
	updateDriveMotors(0,0);
	updateCatMotors(0);

	//throw cube
	releaseClaw();
	wait1Msec(40);
	setClawSpeed(105);
	wait1Msec(200);
	setClawSpeed(0);

	//Part 4: STAR RUSH!****------
	displayLCDCenteredString(0, "Part 4");
	displayLCDCenteredString(1, "STAR RUSH!");

	//
	setArmDown(90,120);
	wait1Msec(200);

	driveStraight(120,1650);
	wait1Msec(200);

	driveStraight(-110,200);
	wait1Msec(200);

	//right turn (encoder)
	SensorValue[leftDriveEnc] = 0;
	SensorValue[rightDriveEnc] = 0;
	nMotorEncoder[back_left_drive] = 0;
	nMotorEncoder[back_right_drive] = 0;
	while(SensorValue[leftDriveEnc] < (/*convertRatio*-405*/ 350) && SensorValue[rightDriveEnc] < (/*convertRatio*-315*/350)/*nMotorEncoder[back_left_drive] > -405 && nMotorEncoder[back_right_drive] > -315*/)
	{
		updateDriveMotors(127,-127);
	}
	updateDriveMotors(0,0);
	wait1Msec(200);//-438,-233

	driveStraight(-120,250);
	wait1Msec(200);

	setArmDown(10,120);
	wait1Msec(100);

	//grab stars
	setClawSpeed(-25);
	driveStraight(120,1350);
	wait1Msec(200);

	setClawSpeed(-85);
	wait1Msec(600);

	setArmUp(70,120);
	wait1Msec(200);

	driveStraight(-120,1100);
	wait1Msec(200);

	//left turn
	SensorValue[leftDriveEnc] = 0;
	SensorValue[rightDriveEnc] = 0;
	nMotorEncoder[back_left_drive] = 0;
	nMotorEncoder[back_right_drive] = 0;
	while(SensorValue[leftDriveEnc] > (/*convertRatio*349*/ -400) && SensorValue[rightDriveEnc] > (/*convertRatio*349*/-400)/*nMotorEncoder[back_left_drive] < 349 && nMotorEncoder[back_right_drive] < 349*/)
	{
		updateDriveMotors(-127,127);
	}
	updateDriveMotors(0,0);
	wait1Msec(200);

	driveStraight(-120,1400);
	wait1Msec(100);

	setArmUp(120,120);
	wait1Msec(100);

	//open claws
	motor[left_claw_motor] = 127;
	//
	motor[right_claw_motor] = 127;
	//phantom line (1065)
	wait1Msec(500);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;

	setArmDown(0,120);

	//close claws
	motor[left_claw_motor] = -95;
	motor[right_claw_motor] = -95;
	wait1Msec(400);

	//swipe under fence
	updateDriveMotors(-127,90);
	wait1Msec(200);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;
	wait1Msec(900);//1200
	updateDriveMotors(0,0);
	wait1Msec(100);
	updateDriveMotors(127,-90);
	wait1Msec(220);
	updateDriveMotors(0,0);

	setArmUp(100,120);
}

/*void antiTipDemo()
{
	SensorValue[vertGyro] = 0;

	setArmUp(150,100);

	if(SensorValue[vertGyro] >= 100 && overrideDrive == 0)
	{
		updateDriveMotors(-115,-115);
	}
	//SensorValue[vertGyro] = 0;
	else if(SensorValue[vertGyro] <= -100 && overrideDrive == 0)
	{
		updateDriveMotors(115,115);
	}
}*/

void testAuto()//Line 1092
//Test bed for all of auto.
{
	accelerate(30,1200);
}

//void hangTest()
//{
//	driveStraight(120,400);

//	wait1Msec(200);
//	updateDriveMotors(0,0);
//	updateDriveMotors(80,-120);
//	wait1Msec(200);
//	updateDriveMotors(0,0);
//	driveStraight(-120,300);
//	wait1Msec(200);
//	updateDriveMotors(80,80);
//	setArmUp(200,120);
//	updateDriveMotors(0,0);
//	setArmDown(0,120);
//	motor[left_claw_motor] = 127;
//	motor[right_claw_motor] = 127;
//	wait1Msec(400);
//	motor[left_claw_motor] = 0;
//	motor[right_claw_motor] = 0;
//}

//Code written and designed by Samuel Fischbach, 599 (2016-17)
