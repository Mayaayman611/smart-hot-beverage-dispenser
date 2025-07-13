#include <Arduino.h> // Include Arduino core library

// Function prototypes
void displayErrorMessage(String message);
void rotate(int dirPin, int stepPin);
void operatePump();
void operateValve();



//const int stepsPerRevolution = 400;  // change this to fit the number of steps per revolution

bool coffee=false;
bool nescafe=false;
bool tea=false;
bool cocoa=false;
bool teamilk=false;


//MOTORS SETUP
#define DIR_PIN_COFFEE 9 // Direction pin connected to DRV8825
#define STEP_PIN_COFFEE 8
#define DIR_PIN_SUGAR 7 // Direction pin connected to DRV8825
#define STEP_PIN_SUGAR 6
#define DIR_PIN_MILK 5 // Direction pin connected to DRV8825
#define STEP_PIN_MILK 4
#define DIR_PIN_COCOA 13 // Direction pin connected to DRV8825
#define STEP_PIN_COCOA 12
#define DIR_PIN_TEA 11 // Direction pin connected to DRV8825
#define STEP_PIN_TEA 10
#define DIR_PIN_BISCUIT 3// Direction pin connected to DRV8825
#define STEP_PIN_BISCUIT 2
#define STEPS_PER_REVOLUTION 400

//SENSORS SETUP
#define CUP_SENSOR A11
#define BISCUT_SENSOR A12
#define COFFEE_SENSOR A13
#define MILK_SENSOR A14
#define SUGAR_SENSOR A15
#define COCOA_SENSOR A8
#define TEA_SENSOR A7
//#define WATER_SENSOR A8
//#define TEMP_SENSOR A7

#define PUMP_PIN 27
#define INLET_VALVE_PIN 26
#define OUTLET_VALVE_PIN 25

void sendData(String data_from_display); // Function prototype

void setup() {
  // Initialize serial communication
    
 
  Serial.println("hello world");

  // SET SENSORS INPUTS
  pinMode(CUP_SENSOR, INPUT);
  pinMode(BISCUT_SENSOR, INPUT);
  pinMode(COFFEE_SENSOR, INPUT);
  pinMode(MILK_SENSOR, INPUT);
  pinMode(SUGAR_SENSOR, INPUT);
  pinMode(COCOA_SENSOR, INPUT);
pinMode(TEA_SENSOR, INPUT);
  //SET MOTOR OUTPUTS
pinMode(DIR_PIN_COFFEE,OUTPUT);
pinMode(STEP_PIN_COFFEE,OUTPUT);
pinMode(DIR_PIN_MILK,OUTPUT);
pinMode(STEP_PIN_MILK,OUTPUT);
pinMode(DIR_PIN_SUGAR,OUTPUT);
pinMode(STEP_PIN_SUGAR,OUTPUT);
pinMode(DIR_PIN_TEA,OUTPUT);
pinMode(STEP_PIN_TEA,OUTPUT);
pinMode(DIR_PIN_COCOA,OUTPUT);
pinMode(STEP_PIN_COCOA,OUTPUT);
pinMode(DIR_PIN_BISCUIT,OUTPUT);
pinMode(STEP_PIN_BISCUIT,OUTPUT);


//VALVES AND PUMP
pinMode(INLET_VALVE_PIN,OUTPUT);
pinMode(OUTLET_VALVE_PIN,OUTPUT);
pinMode(PUMP_PIN,OUTPUT);

  // initialize the serial port:
   Serial.begin(9600);
}

void loop() {

 //  DISPLAY ERROR MESSAGES
 
 if (digitalRead(CUP_SENSOR) == LOW) {
    // Send Nextion commands to go to page 5 and display error message for cup sensor
    displayErrorMessage1("PLEASE PLACE YOUR CUP");
  }
  /*
   if (digitalRead(BISCUT_SENSOR) == LOW) {
    // Send Nextion commands to go to page 5 and display error message for biscuit sensor
    displayErrorMessage2("NO BISCUITS AVAILABLE");
  }
   if (digitalRead(COFFEE_SENSOR) == LOW) {
    // Send Nextion commands to go to page 5 and display error message for coffee sensor
    displayErrorMessage3("PLEASE REFILL THE COFFEE");
  }
   if (digitalRead(MILK_SENSOR) == LOW) {
    // Send Nextion commands to go to page 5 and display error message for milk sensor
    displayErrorMessage4("PLEASE REFILL THE MILK POWDER");
  }
   if (digitalRead(SUGAR_SENSOR) == LOW) {
    // Send Nextion commands to go to page 5 and display error message for sugar sensor
    displayErrorMessage5("PLEASE REFILL THE SUGAR");
  }
//   if (digitalRead(COCOA_SENSOR) == LOW) {
    // Send Nextion commands to go to page 5 and display error message for cocoa sensor
  //  displayErrorMessage6("PLEASE REFILL THE COCOA");
 // }
   if (digitalRead(TEA_SENSOR) == LOW) {
    // Send Nextion commands to go to page 5 and display error message for tea sensor
    displayErrorMessage7("PLEASE REFILL THE TEA");
  }
 
*/

digitalWrite(INLET_VALVE_PIN,HIGH);

  // Check for incoming data from Serial
  if (Serial.available()) {
    // Read the incoming data from Serial
    String data_from_display="";
    delay(30);
    while(Serial.available()){ 
data_from_display+=char(Serial.read());
    }
     // Echo back the received data

    // Call sendData function with the received data
    Serial.println(data_from_display);
    sendData(data_from_display);
  }
}



void sendData(String data_from_display) {
  // Check if the received data matches the expected command
  if (data_from_display == "eat") {
    // If the command is "eat", set pin 2 HIGH
     Serial.println("clockwise");
  rotate2(STEP_PIN_BISCUIT,DIR_PIN_BISCUIT);

  // Delay to ensure the motor completes the revolution:
  delay(500);
  }
  
    
     if(data_from_display == "coffee"){
      
       coffee=true;

    
  }

 if(data_from_display == "tea"){
      
tea=true;
     
    
  }


 if(data_from_display == "teamilk"){
      
teamilk=true;
     
    
  }
  
 if(data_from_display == "cocoa"){
      
cocoa=true;
     
    
  }

 if(data_from_display == "nescafe"){
      
nescafe=true;
     
    
  }
  
 if(data_from_display == "one"){
      
if(tea==true){
  
  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

  rotate(STEP_PIN_TEA,DIR_PIN_TEA);
  // Delay to ensure the motor completes the revolution:
  delay(500);


 operateValve();
} 
else if(coffee==true){

rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

 rotate(STEP_PIN_COFFEE,DIR_PIN_COFFEE);
  // Delay to ensure the motor completes the revolution:
  delay(500);
operateValve();

}
else if(nescafe==true){

rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

 rotate(STEP_PIN_COFFEE,DIR_PIN_COFFEE);
  // Delay to ensure the motor completes the revolution:
  delay(500);

rotate(STEP_PIN_MILK,DIR_PIN_MILK);
  // Delay to ensure the motor completes the revolution:
  delay(500);
operateValve();
}
else if(teamilk==true){

 rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

  

  rotate(STEP_PIN_TEA,DIR_PIN_TEA);
  // Delay to ensure the motor completes the revolution:
  delay(500);

rotate(STEP_PIN_MILK,DIR_PIN_MILK);
  // Delay to ensure the motor completes the revolution:
  delay(500);
operateValve();
}
else if(cocoa==true){


  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);
  rotate(STEP_PIN_COCOA,DIR_PIN_COCOA);
  // Delay to ensure the motor completes the revolution:
  delay(500);

rotate(STEP_PIN_MILK,DIR_PIN_MILK);
  // Delay to ensure the motor completes the revolution:
  delay(500);
operateValve();

}

  }

if(data_from_display == "two"){

if(tea==true){
  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);
  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

  rotate(STEP_PIN_TEA,DIR_PIN_TEA);
  // Delay to ensure the motor completes the revolution:
  delay(500);

operateValve();
   
} 
else if(coffee==true){

 rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

 rotate(STEP_PIN_COFFEE,DIR_PIN_COFFEE);
  // Delay to ensure the motor completes the revolution:
  delay(500);

operateValve();
}
else if(nescafe==true){

 rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

 rotate(STEP_PIN_COFFEE,DIR_PIN_COFFEE);
  // Delay to ensure the motor completes the revolution:
  delay(500);

rotate(STEP_PIN_MILK,DIR_PIN_MILK);
  // Delay to ensure the motor completes the revolution:
  delay(500);
  operateValve();

}
else if(teamilk==true){

 rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

  rotate(STEP_PIN_TEA,DIR_PIN_TEA);
  // Delay to ensure the motor completes the revolution:
  delay(500);

rotate(STEP_PIN_MILK,DIR_PIN_MILK);
  // Delay to ensure the motor completes the revolution:
  delay(500);

operateValve();

}

else if(cocoa==true){

rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);
  
  rotate(STEP_PIN_COCOA,DIR_PIN_COCOA);
  // Delay to ensure the motor completes the revolution:
  delay(500);

rotate(STEP_PIN_MILK,DIR_PIN_MILK);
  // Delay to ensure the motor completes the revolution:
  delay(500);
operateValve();

}
}
if(data_from_display == "three"){

if(tea==true){
  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);
  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

  rotate(STEP_PIN_TEA,DIR_PIN_TEA);
  // Delay to ensure the motor completes the revolution:
  delay(500);

operateValve();

  
} 
else if(coffee==true){

rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);
  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

 rotate(STEP_PIN_COFFEE,DIR_PIN_COFFEE);
  // Delay to ensure the motor completes the revolution:
  delay(500);

operateValve();
}
else if(nescafe==true){

rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);
  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

 rotate(STEP_PIN_COFFEE,DIR_PIN_COFFEE);
  // Delay to ensure the motor completes the revolution:
  delay(500);

rotate(STEP_PIN_MILK,DIR_PIN_MILK);
  // Delay to ensure the motor completes the revolution:
  delay(500);
operateValve();
}
else if(teamilk==true){

rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);
  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);
  rotate(STEP_PIN_TEA,DIR_PIN_TEA);
  // Delay to ensure the motor completes the revolution:
  delay(500);

rotate(STEP_PIN_MILK,DIR_PIN_MILK);
  // Delay to ensure the motor completes the revolution:
  delay(500);
operateValve();

}

else if(cocoa==true){

rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);

  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);
  rotate(STEP_PIN_SUGAR,DIR_PIN_SUGAR);
  // Delay to ensure the motor completes the revolution:
  delay(500);
  rotate(STEP_PIN_COCOA,DIR_PIN_COCOA);
  // Delay to ensure the motor completes the revolution:
  delay(500);

rotate(STEP_PIN_MILK,DIR_PIN_MILK);
  // Delay to ensure the motor completes the revolution:
  delay(500);
operateValve();

}



}



}

void displayErrorMessage1(String sensorName) {
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.print("page 5");
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.print("t0.txt=\"Error: " + sensorName);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
}
void displayErrorMessage2(String sensorName) {
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.print("page 5");
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.print("t1.txt=\"Error: " + sensorName);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
}
void displayErrorMessage3(String sensorName) {
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.print("page 5");
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.print("t2.txt=\"Error: " + sensorName);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
}
void displayErrorMessage4(String sensorName) {
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.print("page 5");
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.print("t3.txt=\"Error: " + sensorName);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
}
void displayErrorMessage5(String sensorName) {
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.print("page 5");
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.print("t4.txt=\"Error: " + sensorName);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
}
void displayErrorMessage6(String sensorName) {
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.print("page 5");
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.print("t5.txt=\"Error: " + sensorName);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
}
void displayErrorMessage7(String sensorName) {
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.print("page 5");
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.print("t6.txt=\"Error: " + sensorName);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
}

void rotate(int STEP_PIN, int DIR_PIN){

digitalWrite(DIR_PIN, HIGH);
  
  // Rotate stepper motor counterclockwise for one revolution
  for (int i = 0; i < STEPS_PER_REVOLUTION; i++) {
    digitalWrite(STEP_PIN, HIGH); // Step pulse rising edge
    delayMicroseconds(500); // Adjust this delay to control step rate (adjust as needed)
    digitalWrite(STEP_PIN, LOW); // Step pulse falling edge
    delayMicroseconds(500); // Adjust this delay to control step rate (adjust as needed)
  }


}

void rotate2(int STEP_PIN, int DIR_PIN){

digitalWrite(DIR_PIN, LOW);
  
  // Rotate stepper motor counterclockwise for one revolution
  for (int i = 0; i < STEPS_PER_REVOLUTION; i++) {
    digitalWrite(STEP_PIN, HIGH); // Step pulse rising edge
    delayMicroseconds(500); // Adjust this delay to control step rate (adjust as needed)
    digitalWrite(STEP_PIN, LOW); // Step pulse falling edge
    delayMicroseconds(500); // Adjust this delay to control step rate (adjust as needed)
  }


}
 /*
void operatePump() {
  // Open the inlet valve
  digitalWrite(INLET_VALVE_PIN, HIGH);
  
  // Operate the pump until the water sensor pin goes high
  while (digitalRead(WATER_SENSOR) == LOW) {
    digitalWrite(PUMP_PIN, HIGH); // Turn on the pump
    delay(3000); // Adjust delay as needed for pump operation
  }
  
  // Stop the pump
  digitalWrite(PUMP_PIN, LOW);
}
*/
void operateValve(){
  digitalWrite(OUTLET_VALVE_PIN,HIGH);
  delay(10000);

digitalWrite(OUTLET_VALVE_PIN,LOW);
tea=false;
coffee=false;
nescafe=false;
teamilk=false;
cocoa=false;
}




