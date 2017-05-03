#include "SDrive.h"
#include "Catapult.h"
#include "Vex_Competition_Includes.c"
#include "PID.h"

void Strafe(int speed)
{
	motor[front_right_drive] = speed;
	motor[front_left_drive] = -speed;
	motor[back_left_drive] = speed;
	motor[back_right_drive] = -speed;
}

void setArmUp(int angle, int speed)
{
	while(SensorValue[RightEncoder] < angle)
	{
		updateCatMotors(speed);
	}
	updateCatMotors(0);
}

void setArmDown(int angle, int speed)
{
	while(SensorValue[RightEncoder] > angle)
	{
		updateCatMotors(-speed);
	}
	updateCatMotors(0);
}

void turnTo(int angle)
{
	while(abs(SensorValue[gyro]) < angle)
	{
		if(angle < 1800)
		{
			updateDriveMotors(-60,60);
		}
		else if(angle > 1799)
		{
			updateDriveMotors(60,-60);
		}
	}
	updateDriveMotors(0,0);
	if(abs(SensorValue[gyro]) > angle)
	{
		if(angle < 1800)
		{
			updateDriveMotors(60,-60);
		}
		else if(angle > 1799)
		{
			updateDriveMotors(-60,60);
		}
	}
	updateDriveMotors(0,0);
}

void driveStraight(int speed,int time)
{
	updateDriveMotors(speed,speed);
	wait1Msec(time);
	updateDriveMotors(0,0);
}

void clearGyro()
{
	SensorValue[gyro] = 0;
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

void skillsAuto()
{
	static controlPID_t theGyro;

	//Part 1: 2 Kyubeys, 5 Stars  [][] *****--------

	//theGyro.Kp = 4;
	//theGyro.Ki = .5;
	//theGyro.Kd = .25;
	//theGyro.waitTime = 200;
	//theGyro.timeout = 10000;

	SensorValue[RightEncoder] = 0;
	setArmUp(60,127);
	/*wait1Msec(600);
	updateCatMotors(0);

	updateCatMotors(-100);*/

	wait1Msec(400);
	setClawSpeed(-90);
	wait1Msec(900);
	setClawSpeed(-70);
	wait1Msec(500);

	//closing claws
	//wait1Msec(810);
	//motor[left_claw_motor] = 0;
	//motor[right_claw_motor] = 0;
	//wait1Msec(200);
	//updateCatMotors(0);

	//Drive forward
	driveStraight(120,1550);

	setArmUp(75,100);

	wait1Msec(200);

	driveStraight(120,300);

	wait1Msec(200);

	//driveStraight(-90,280);
	//wait1Msec(200);

	//updateDriveMotors(107,-107);
	//wait1Msec(3000);
	//updateDriveMotors(0,0);


	//Back up slightly
	driveStraight(-80,250);

	//Set arm back
	//while(SensorValue[RightEncoder] < 55)
	//{
	//	updateCatMotors(-127);
	//}
	//updateCatMotors(0);

	//wait1Msec(100);

	//turn around
	clearGyro();
	//while(abs(SensorValue[gyro]) < 1800)
	//{
	//	updateDriveMotors(25,-25);
	//}
	initPID(theGyro, 0.345, 0.23, 0.25, 200, 5000, 1880);
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

		//static int oldMotorValue;

		//if(abs(motorValue - oldMotorValue) > 10)
		//{
		//	motorValue = oldMotorValue+(10*((motorValue - oldMotorValue)/-(motorValue - oldMotorValue)));
		//}

		//if(motorValue - motor[front_right_drive] < -10)
		//{
		//	motorValue = motor[front_right_drive]+10;
		//}

		updateDriveMotors(-motorValue,motorValue);

		//oldMotorValue = motorValue;

		wait1Msec(40);
	}

	updateDriveMotors(0,0);

	driveStraight(-100,500);

	//while(SensorValue[RightEncoder] < 105)
	//{
	//	updateCatMotors(-127);
	//}
	//updateCatMotors(0);

	while(SensorValue[RightEncoder] < 120)
	{
		updateCatMotors(120);
	}
	updateCatMotors(0);
	wait1Msec(100);
	//while(SensorValue[RightEncoder] > 130)
	//{
	//	updateCatMotors(45);
	//}

	//updateCatMotors(0);
	motor[left_claw_motor] = 85;
	motor[right_claw_motor] = 85;
	wait1Msec(700);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;

	while(SensorValue[RightEncoder] > 100)
	{
		updateCatMotors(-45);
	}
	updateCatMotors(0);

	//drive forward
	driveStraight(127,1200);
	wait1Msec(1000);

	//close claws
	motor[left_claw_motor] = -95;
	motor[right_claw_motor] = -95;
	wait1Msec(500);

	//drive backward toward gate
	updateDriveMotors(-127,-127);
	wait1Msec(1350);
	updateDriveMotors(0,0);

	//set arm over gate
	while(SensorValue[RightEncoder] < 120)
	{
		updateCatMotors(127);
	}
	updateCatMotors(0);
	wait1Msec(100);

	//release cube
	motor[left_claw_motor] = 80;
	motor[right_claw_motor] = 80;
	wait1Msec(600);
	motor[left_claw_motor] = -40;
	motor[right_claw_motor] = -40;
	wait1Msec(650);
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
	updateDriveMotors(100,100);
	wait1Msec(900);
	updateDriveMotors(0,0);
	wait1Msec(400);

	//close claws
	motor[left_claw_motor] = -95;
	motor[right_claw_motor] = -95;
	wait1Msec(800);

	//drive backward toward gate
	updateDriveMotors(-127,-127);
	wait1Msec(1000);
	updateDriveMotors(0,0);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;

	motor[left_claw_motor] = -105;
	motor[right_claw_motor] = -105;
	wait1Msec(100);
	//motor[left_claw_motor] = 0;
	//motor[right_claw_motor] = 0;

	//set arm over gate
	while(SensorValue[RightEncoder] < 120)
	{
		updateCatMotors(127);
	}
	updateCatMotors(0);

	//release stars
	releaseClaw();
	wait1Msec(300);

	//Part 2: Kyubey Central []*----------
//lower arm to floor
	setArmDown(70,127);
	wait1Msec(200);

	driveStraight(120,700);

	wait1Msec(100);


	//turn left 90 degrees
	//initPID(theGyro, 0.245, 0.23, 0.25, 200, 5000, 570);
	//while(theGyro.isMoving)
	//{
	//	theGyro.currentValue = SensorValue(gyro);

	//	int motorValue = calcPID(theGyro);

	//	if(motorValue > 60)
	//	{
	//		motorValue = 60;
	//	}
	//	if(motorValue < -60)
	//	{
	//		motorValue = -60;
	//	}

	//	updateDriveMotors(motorValue,-motorValue);

	//	wait1Msec(40);
	//}
	nMotorEncoder[back_left_drive] = 0;
	nMotorEncoder[back_right_drive] = 0;
	while(nMotorEncoder[back_left_drive] < 440 && nMotorEncoder[back_right_drive] < 440)
	{
		updateDriveMotors(-87,87);
	}
	updateDriveMotors(0,0);
	wait1Msec(200);
	//left:360 right:253

	setArmDown(10,127);
	wait1Msec(200);
	updateDriveMotors(120,120);
	wait1Msec(500);
	updateDriveMotors(0,0);

	//begin closing claws
	setClawSpeed(-85);
	wait1Msec(350);

	setArmUp(50,100);
	wait1Msec(300);

	updateDriveMotors(120,120);
	wait1Msec(1200);
	updateDriveMotors(0,0);
	wait1Msec(200);

	//driveStraight(100,200);

	//lift arm up
	//setArmUp(120,127);
	while(SensorValue[RightEncoder] < 60)
	{
		updateCatMotors(100);
	}
	updateCatMotors(0);
	wait1Msec(200);

	//stop closing claws (to prevent breaking the stars)
	setClawSpeed(-20);
	wait1Msec(200);

	//turn right left 90
	//initPID(theGyro, 0.345, 0.23, 0.25, 200, 5000, 970);
	//while(theGyro.isMoving)
	//{
	//	theGyro.currentValue = SensorValue(gyro);

	//	int motorValue = calcPID(theGyro);

	//	if(motorValue > 60)
	//	{
	//		motorValue = 60;
	//	}
	//	if(motorValue < -60)
	//	{
	//		motorValue = -60;
	//	}

	//	updateDriveMotors(-motorValue,motorValue);

	//	wait1Msec(40);
	//}
	updateDriveMotors(127,-127);
	wait1Msec(850);//TODO: Get correct value
	updateDriveMotors(0,0);
	wait1Msec(200);

	driveStraight(-80,1500);
	wait1Msec(200);

	while(SensorValue[RightEncoder] < 100)
	{
		updateCatMotors(100);
	}
	updateCatMotors(0);
	wait1Msec(100);

	//releaseClaw();
	motor[left_claw_motor] = 85;
	motor[right_claw_motor] = 85;
	wait1Msec(200);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;
	wait1Msec(200);

	//lower arm to floor
	setArmDown(10,100);
	wait1Msec(200);

	//Part 3: The Final Kyubey []----

	driveStraight(100,900);
	wait1Msec(200);

	//turn
	//initPID(theGyro, 0.345, 0.23, 0.25, 200, 5000, -970);
	//while(theGyro.isMoving)
	//{
	//	theGyro.currentValue = SensorValue(gyro);

	//	int motorValue = calcPID(theGyro);

	//	if(motorValue > 60)
	//	{
	//		motorValue = 60;
	//	}
	//	if(motorValue < -60)
	//	{
	//		motorValue = -60;
	//	}

	//	updateDriveMotors(-motorValue,motorValue);

	//	wait1Msec(40);
	//}
	//updateDriveMotors(-127,127);
	//wait1Msec(500);//TODO: Get correct value
	//updateDriveMotors(0,0);
	//wait1Msec(200);

	//driveStraight(110,700);
	//wait1Msec(200);

	//initPID(theGyro, 0.345, 0.23, 0.25, 200, 5000, 970);
	//while(theGyro.isMoving)
	//{
	//	theGyro.currentValue = SensorValue(gyro);

	//	int motorValue = calcPID(theGyro);

	//	if(motorValue > 60)
	//	{
	//		motorValue = 60;
	//	}
	//	if(motorValue < -60)
	//	{
	//		motorValue = -60;
	//	}

	//	updateDriveMotors(-motorValue,motorValue);

	//	wait1Msec(40);
	//}
	//updateDriveMotors(127,-127);
	//wait1Msec(500);//TODO: Get correct value
	//updateDriveMotors(0,0);
	//wait1Msec(200);

	//driveStraight(100,350);
	//wait1Msec(200);

	setClawSpeed(-85);
	wait1Msec(600);

	setArmUp(70,120);
	wait1Msec(200);

	driveStraight(-100,900);
	wait1Msec(200);

	setArmUp(120,127);
	wait1Msec(80);

	releaseClaw();
	wait1Msec(40);
	setClawSpeed(105);
	wait1Msec(200);
	setClawSpeed(0);

	//Part 4: STAR RUSH!****------

	setArmDown(90,120);
	wait1Msec(200);

	driveStraight(120,1650);
	wait1Msec(200);

	driveStraight(-110,200);
	wait1Msec(200);

	nMotorEncoder[back_left_drive] = 0;
	nMotorEncoder[back_right_drive] = 0;
	while(nMotorEncoder[back_left_drive] > -405 && nMotorEncoder[back_right_drive] > -315)
	{
		updateDriveMotors(127,-127);
	}
	updateDriveMotors(0,0);
	wait1Msec(200);
		//-438,-233

	driveStraight(-120,250);
	wait1Msec(200);

	setArmDown(10,120);
	wait1Msec(100);

	setClawSpeed(-25);
	driveStraight(120,1350);
	wait1Msec(200);

	setClawSpeed(-85);
	wait1Msec(600);

	setArmUp(70,120);
	wait1Msec(200);

	driveStraight(-120,1100);
	wait1Msec(200);

	nMotorEncoder[back_left_drive] = 0;
	nMotorEncoder[back_right_drive] = 0;
	while(nMotorEncoder[back_left_drive] < 349 && nMotorEncoder[back_right_drive] < 349)
	{
		updateDriveMotors(-127,127);
	}
	updateDriveMotors(0,0);
	wait1Msec(200);

	driveStraight(-120,1400);
	wait1Msec(100);

	setArmUp(120,120);
	wait1Msec(100);

	motor[left_claw_motor] = 127;
	motor[right_claw_motor] = 127;
	wait1Msec(500);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;

	setArmDown(0,120);
	wait1Msec(200);

	motor[left_claw_motor] = -95;
	motor[right_claw_motor] = -95;
	wait1Msec(400);

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

	//driveStraight(-120,700);
	//wait1Msec(100);

	//releaseClaw();
	//wait1Msec(100);

	//releaseClaw();
//	setArmUp(100,120);
	//wait1Msec(100);

	//driveStraight(120,950);

	//updateDriveMotors(120,-100);
	//wait1Msec(450);
	//updateDriveMotors(0,0);
}
