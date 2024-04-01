/*
	Project: Test_L298N_Motor
	This project test L298N motor driver.
*/

#define L298N_MOTOR_A 1
#define L298N_MOTOR_B 2

#define L298N_DIR_FORWARD	0
#define L298N_DIR_REVERSE	1

/* L298N pin defnition */
#define L298N_PIN_IN1 6
#define L298N_PIN_IN2 7
#define L298N_PIN_IN3 8
#define L298N_PIN_IN4 9
#define L298N_PIN_ENA 9
#define L298N_PIN_ENB 10

#define L298N_SPEED_ADC_MIN	0
#define L298N_SPEED_ADC_MAX	255
#define L298N_SPEED_PER_MIN	0
#define L298N_SPEED_PER_MAX	100


void L298N_Set_Pin_Modes(void);
bool L298N_TurnOff_Motor(int motor);
bool L298N_Control_Speed( int motor, int speed, int direction );

int speedVal = 0;

void setup()
{
	L298N_Set_Pin_Modes();
	L298N_TurnOff_Motor(L298N_MOTOR_A);
	L298N_TurnOff_Motor(L298N_MOTOR_B);
}

void loop()
{
	L298N_Control_Speed( L298N_MOTOR_A, speedVal );
	L298N_Control_Speed( L298N_MOTOR_B, speedVal );
	delay(10000);
	speedVal += 10;
	if( speedVal > 100 )
	{
		speedVal = 0;
	}
}

void L298N_Set_Pin_Modes(void)
{
	pinMode(L298N_PIN_IN1, OUTPUT);
	pinMode(L298N_PIN_IN2, OUTPUT);
	pinMode(L298N_PIN_IN3, OUTPUT);
	pinMode(L298N_PIN_IN4, OUTPUT);
	pinMode(L298N_PIN_ENA, OUTPUT);
	pinMode(L298N_PIN_ENB, OUTPUT);
}

bool L298N_TurnOff_Motor(int motor)
{
	bool action = false;

	if (motor == L298N_MOTOR_A)
	{
		analogWrite(L298N_PIN_ENA, 0);
		action = true;
	}
	else if (motor == L298N_MOTOR_B)
	{
		analogWrite(L298N_PIN_ENA, 0);
		action = true;
	}
	else
	{
		action = false;
		// do nothing
	}

	return action;
}

bool L298N_Control_Speed( int motor, int speed, int direction )
{
	bool action = false;
	int val=0;
	
	val = map( speed, L298N_SPEED_PER_MIN, L298N_SPEED_PER_MAX, L298N_SPEED_ADC_MIN, L298N_SPEED_ADC_MAX );

	if (motor == L298N_MOTOR_A)
	{
		analogWrite( L298N_PIN_ENA, val );
		if( direction == L298N_DIR_FORWARD )
		{
			digitalWrite( L298N_PIN_IN1, LOW );
			digitalWrite( L298N_PIN_IN2, HIGH );
		}
		else
		{
			digitalWrite( L298N_PIN_IN1, HIGH );
			digitalWrite( L298N_PIN_IN2, LOW );
		}
		action = true;
	}
	else if (motor == L298N_MOTOR_B)
	{
		analogWrite( L298N_PIN_ENB, val );
		if( direction == L298N_DIR_FORWARD )
		{
			digitalWrite( L298N_PIN_IN3, LOW );
			digitalWrite( L298N_PIN_IN4, HIGH );
		}
		else
		{
			digitalWrite( L298N_PIN_IN3, HIGH );
			digitalWrite( L298N_PIN_IN4, LOW );
		}
		action = true;
	}
	else
	{
		action = false;
		// do nothing
	}

	return action;
}