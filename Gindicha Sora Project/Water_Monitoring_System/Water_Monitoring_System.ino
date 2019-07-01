#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// constants won't change. They're used here to set pin numbers:
const int buttonSelect = 51;    // the number of the pushbutton pin
const int buttonReset = 53;

int ledRed = 23;      // the number of the LED pin
int ledGreen = 25;
int ledBlue = 27;

int setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(ledRed, redValue);
  analogWrite(ledGreen, greenValue);
  analogWrite(ledBlue, blueValue);

// Variables will change:
//setColor(255, 255, 255); // White Color
int ledState = setColor(255, 255, 255);         // the current state of the output pin
int ledRedState = LOW;
int ledGreenState = LOW;
int ledBlueState = LOW;
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

#define SensorPin 0          //pH meter Analog output to Arduino Analog Input 0
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;

#define SENSOR       A7 //Turbidity Sensor 
float voltage,turbidity;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  pinMode(buttonSelect, INPUT);
  pinMode(buttonReset, INPUT);
  
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  
  pinMode(SENSOR,INPUT);

  // set initial LED state
  //digitalWrite(ledPin, ledState);

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("EUNAX DEVICE");
}

/*
 ************************************************************
 *                                                          *
 ***********************MAIN FUNCTIONS***********************
 *                                                          *
 ************************************************************
*/

void loop(){
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonSelect);
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
  digitalWrite(ledPin, ledState);
  
  lastButtonState = reading;
}

/*
 ************************************************************
 *                                                          *
 **********************CUSTOM FUNCTIONS**********************
 *                                                          *
 ************************************************************
*
------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------


/*
 ************************************************************
 *-----------------  ------------------*
 ************************************************************
*
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

  /*
 ************************************************************
 *-----------------  ------------------*
 ************************************************************
*

void turbid(){
  voltage=0.004888*analogRead(SENSOR);  //in V
  turbidity=-1120.4*voltage*voltage+5742.3*voltage-4352.9;  //in NTU
  if((voltage>=2.5)&(turbidity>=0))
  {
    Serial.println("Voltage="+String(voltage)+" V Turbidity="+String(turbidity)+" NTU");  
    delay(500);
  }
*/
