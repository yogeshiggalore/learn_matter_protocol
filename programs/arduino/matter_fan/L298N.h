#ifndef L298N_H
#define L298N_H

enum L298N_Motor_Dir
{
    L298N_DIR_FORWARD=1,
    L298N_DIR_REVERSE
};

struct L298N_config
{
    int Pin_In1;
    int Pin_In2;
    int Pin_EnA;
    int DirectionA;
    int SpeedA;
    int ADCMin;
    int ADCMax;
};

class L298N
{
private:
    L298N_config cfg;
public:
    L298N( int in1, int in2, int ena, int ADCMin, int ADCMax );
    void begin(void);
    void TurnOff(void);
    void Control_Speed(int direction, int speed);
    ~L298N();
};

#endif