/*
	Project: Test_L298N_Motor
	This project test L298N motor driver.
*/

/* define two motors */
#define L298N_MOTOR_A 1
#define L298N_MOTOR_B 2

/* define motor direction */
#define L298N_DIR_FORWARD	0
#define L298N_DIR_REVERSE	1

/* L298N pin defnition */
#define L298N_PIN_IN1 6
#define L298N_PIN_IN2 7
#define L298N_PIN_IN3 8
#define L298N_PIN_IN4 9
#define L298N_PIN_ENA A0
#define L298N_PIN_ENB A1

/* PWM control value */
#define L298N_SPEED_ADC_MIN	127
#define L298N_SPEED_ADC_MAX	255
#define L298N_SPEED_PER_MIN	0
#define L298N_SPEED_PER_MAX	100

/* set L298N pin modes */
void L298N_Set_Pin_Modes(void);

/* turnoff all motors */
bool L298N_TurnOff_Motor(int motor);

/* control speed and direction */
bool L298N_Control_Speed( int motor, int direction, int speed );

int speedVal = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(" L298N motor driver test code ");
  
  Serial.println("Setting L298N pin modes");
	L298N_Set_Pin_Modes();

  Serial.println("Turn off motors ");
	L298N_TurnOff_Motor(L298N_MOTOR_A);
	L298N_TurnOff_Motor(L298N_MOTOR_B);

}

void loop()
{
	bool ret;

  ret = L298N_Control_Speed( L298N_MOTOR_A, L298N_DIR_FORWARD, speedVal );
	ret = L298N_Control_Speed( L298N_MOTOR_B, L298N_DIR_FORWARD, speedVal );
	delay(5000);
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

bool L298N_Control_Speed( int motor, int direction, int speed )
{
	bool action = false;
	int val=0;
	
	val = map( speed, L298N_SPEED_PER_MIN, L298N_SPEED_PER_MAX, L298N_SPEED_ADC_MIN, L298N_SPEED_ADC_MAX );
  Serial.print("Speed set to: ");
  Serial.println(val);

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