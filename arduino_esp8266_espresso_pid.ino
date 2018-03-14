//espresso pid esp8266,arduino uno

#include "DHT.h"

#include <PID_v1.h>


#define DHTPIN            2         // Pin which is connected to the DHT sensor.
#define DHTTYPE   DHT11     // DHT 11 

#define PIN_INPUT 0
#define PIN_OUTPUT 3

//Define Variables we'll be connecting to
double Setpoint, Input, Output;


//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

DHT DHTPID(DHTPIN, DHTTYPE);

float temp;

//int WindowSize = 5000;
int WindowSize = 1;
unsigned long windowStartTime;

void setup() {
  Serial.begin(9600);
  DHTPID.begin();

  //Input = analogRead(PIN_INPUT);
  temp = DHTPID.readTemperature();
  Input = temp;
 Setpoint = 25;

  //turn the PID on
  
  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, WindowSize);
  //myPID.SetMode(MANUAL); //for manual regulation, not usable
  myPID.SetMode(AUTOMATIC);

}

void loop() {
  delay(2000);
  temp = DHTPID.readTemperature();
  if (isnan(temp)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(DHTPID.readTemperature());
    Serial.println(" *C");
  }
  
  //Input = analogRead(PIN_INPUT);
  //Input = DHTPID.readTemperature();
  Input = temp;
  myPID.Compute();
  Serial.print("My pid compute:");
  Serial.println(myPID.Compute());
  Serial.println("Input,Ouput,Setpoint");
  Serial.println(Input);
  Serial.println(Output);
  Serial.println(Setpoint);
  double getkp = myPID.GetKp();
  double getki = myPID.GetKi();
  double getkd = myPID.GetKd();
  Serial.println("Kp,Ki,Kd");
  Serial.println(getkp);
  Serial.println(getki);
  Serial.println(getkd);
  analogWrite(PIN_OUTPUT, Output);
  
}
