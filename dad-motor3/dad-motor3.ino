#define KP 2000
#define KI  5
#define KD   100  

#define MOTORMAX 255

#define motorlim(a) (  abs(a) > MOTORMAX) ? ( (a > 0)?MOTORMAX:-MOTORMAX) : (a)


#define PWM_A  3
#define PWM_B 11
#define DIR_A 12
#define DIR_B 13
#define BRK_A 9
#define BRK_B 8
#define DEADSPACE 30
#define MOTIONRANGE 245

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A2;  // Analog input pin that the potentiometer is attached to
const int analogMotorPin = A3;
const int analogOutPin = 3; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

int motorValue = 0;
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
  
  outputValue = CreateOutput();




  // get direction
  if(outputValue > 0){
      digitalWrite(DIR_A, 0);
  }else{
      digitalWrite(DIR_A, 1);
    outputValue *= -1;
  }

 
  if(outputValue < DEADSPACE && outputValue > -DEADSPACE) outputValue = 0;
  
  analogWrite(analogOutPin, outputValue);


  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(1);
  
}

int CreateOutput() {




long int motor =0;
static long int  intg = 0;
static int  perr;
int der;

  
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // read motor position
  motorValue = analogRead(analogMotorPin);


 long int err = motorValue - sensorValue;


    intg += err;
    der =  err - perr;
    perr = err;


    if(intg > 10000) intg = 10000;  if(intg < 10000) intg = -10000; 

  // map it to the range of the analog out:
 // motor = map(sensorValue, 0, 1023, -255, 255);

   motor = (err * KP + intg * KI   + (der * KD) )/1000;


  // print the results to the Serial Monitor:
 // Serial.print("s , ");
  Serial.print(sensorValue);
//  Serial.print(", m ,");
Serial.print(" , ");
  Serial.print(motorValue);
//  Serial.print(", e ,");
Serial.print(" , ");
  Serial.print(err);
  //  Serial.print(", i ,");
  Serial.print(" , ");
  Serial.print(intg);
 // Serial.print(", d ,");
 Serial.print(" , ");
  Serial.print(der);
//  Serial.print(", m ,");
Serial.print(" , ");
  Serial.println(motor);


 
      return motorlim(motor);  
  
}
