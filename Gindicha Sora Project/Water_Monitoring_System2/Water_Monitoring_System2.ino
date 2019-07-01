#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buttonPin = 51;    // the number of the pushbutton pin
int redPin = 23;      // the number of the LED pin
int greenPin =25;
int bluePin =27;

// Variables will change:
int ledState = HIGH;        // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

#define SENSOR       A7 //Turbidity Sensor 
float voltage,turbidity;

#define SensorPin A0          //pH meter Analog output to Arduino Analog Input 0
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(SENSOR,INPUT); //Turbidity

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DETECT APPARATUS");
  lcd.setCursor(0,1);
  lcd.print("*Health Living*");
  delay(5000);
  lcd.clear();
}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  digitalWrite(greenPin, ledState);
  if (greenPin = HIGH){
    pHSensor();
  }else{
    turbid();
    }
  lastButtonState = reading;
}

/*
 ************************************************************
 *                                                          *
 **********************CUSTOM FUNCTIONS**********************
 *                                                          *
 ************************************************************
*/

  /*
 ************************************************************
 *----------------- TURBIDITY (PHYSICAL) -------------------*
 ************************************************************
*/

void turbid(){
  voltage=0.004888*analogRead(SENSOR);  //in V
  turbidity=-1120.4*voltage*voltage+5742.3*voltage-4352.9;  //in NTU
  if((voltage>=2.5)&(turbidity>=0))
  {
    Serial.println("Voltage="+String(voltage)+" V Turbidity="+String(turbidity)+" NTU");  
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
  lcd.print("DETECT APPARATUS");
  lcd.setCursor(0, 1);
  lcd.print("Turbid: "+String(turbidity));
  //delay(1000);
  }
}

/*
 ************************************************************
 *----------------- pH Sensor (CHEMICAL)  --------------------*
 ************************************************************
*/
void pHSensor(){
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.01*phValue;                      //convert the millivolt into pH value
  Serial.print("    pH:");  
  Serial.print(phValue,2);
  Serial.println(" ");
  }


