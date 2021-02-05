
#define PWM_A  3
#define PWM_B 11
#define DIR_A 12
#define DIR_B 13
#define BRK_A 9
#define BRK_B 8
#define DEADSPACE 30

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A2;  // Analog input pin that the potentiometer is attached to
const int analogMotorPin = 
const int analogOutPin = 3; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {


   Serial.begin(115200);
  // put your setup code here, to run once:
    pinMode(PWM_A, OUTPUT);
    pinMode(DIR_A, OUTPUT);
    pinMode(BRK_A, OUTPUT);

    pinMode(PWM_B, OUTPUT);
    pinMode(DIR_B, OUTPUT);
    pinMode(BRK_B, OUTPUT);
     
    analogWrite(PWM_A, 100);
    digitalWrite(DIR_A, 0);
    //digitalWrite(PWM_A, 1);
    digitalWrite(BRK_A, 0);

    digitalWrite(DIR_B, 0);
    digitalWrite(PWM_B, 0);
       digitalWrite(BRK_B, 1);
}

void loop() {
  // put your main code here, to run repeatedly:

 // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // read motor position
  motorValue = analogRead(analogInPin);
  
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, -255, 255);
  // change the analog out value:
  
  if(outputValue > 0){
      digitalWrite(DIR_A, 0);
  }else{
    digitalWrite(DIR_A, 1);
    outputValue *= -1;
  }
  if(outputValue <DEADSPACE && outputValue>-DEADSPACE){
    analogWrite(analogOutPin, 0);
  }else{
    analogWrite(analogOutPin, outputValue);
  }
  

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(200);
}
