
/*
Project: Turbidity Sensor Lesson
Programmer: Shahrulnizam Mat Rejab
Board: Arduino Uno
Last Modified: 5 September 2018
Website: http://shahrulnizam.com
*/

#define SENSOR       A7

float voltage,turbidity;

void setup()
{
  Serial.begin(9600);
  pinMode(SENSOR,INPUT);
}

void loop()
{
  voltage=0.004888*analogRead(SENSOR);  //in V
  turbidity=-1120.4*voltage*voltage+5742.3*voltage-4352.9;  //in NTU
  if((voltage>=2.5)&(turbidity>=0))
  {
    Serial.println("Voltage="+String(voltage)+" V Turbidity="+String(turbidity)+" NTU");  
    delay(500);
  }
}
