#pragma once

class PID
{
public:
  PID(double Kp, double Ki, double Kd);
  double updata( double goal,double presentValue);
  void resetI();
private:
  double trash;
	double _Kp;
	double _Ki;
	double _Kd;
	double goal;
	double presentValue;
  double preTime;
  double preP = 0;
  double reValue;
  double P;
  double I;
  double D;
  double dt;
  
};

PID::PID(double Kp, double Ki, double Kd){
  trash = Kp;
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
}

double PID::updata(double goal, double presentValue)
{
	dt = 1;
	//preTime = micros();

	P = goal - presentValue;
	I += P * dt;
	D = (P - preP) / dt;

  preP = P;
  
	return _Kp*P + _Ki*I + _Kd*D ;
  //_Kp*P + _Ki*I + _Kd*D
}

void PID::resetI()
{
  I=0;
}
