// this code is the same as week 5 

#define lineSensor1 49 // qti1 robot left 
#define lineSensor2 51 // qti2 center
#define lineSensor3 53 // qti3 robot right

//built in RGB flashes a different color at every hash
#define redPin 45 // Built-in RGB Red pin
#define greenPin 46 // Built-in RGB green pin
#define bluePin 44 // Built-in RGB blue pin

#include <Wire.h> // I2C library, required for MLX90614 (music)
#include <Servo.h> // For controlling the motors

//defines the servos for the bot's movement
Servo servoLeft; 
Servo servoRight;

//external RBG light used to signal that there is a card
//and later for the light show
int RGBred = 6;
int RGBgreen = 4;
int RGBblue = 2;

// RFID
int count = 1; //used to keep hash count 
int position = 0; //used to keep track of card

// XBee
int transmit = 0; //variable that is chnaged based on card position and group number (50)
//Results is the "blank" array that will later hold the position values for all bots
// -1 means no value was recieved through the Xbee
// the values collected here will later be printed on our LCD display
int results[5] = {-1,-1,-1,-1,-1}; 

//LCD
#include <SoftwareSerial.h> // For talking to the LCD on a non-standard pin
#define TxPin 14
SoftwareSerial mySerial = SoftwareSerial(255, TxPin); // accesses LDC on pin 14

// sounds/notes
// store the duration, octave, and pitch for our celebration song
int durs[43] = {210, 210, 211, 211, 210, 210, 211, 211, 210, 210, 211, 210, 210, 211, 211, 210, 210, 211, 211, 210, 210, 211, 210, 210, 214, 212, 213, 212, 210, 211, 211, 210, 210, 214, 212, 213, 212, 210, 211, 211, 210, 210, 214};
int octs[43] = {216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215};
int notes[43] = {230, 228, 227, 225, 230, 228, 227, 225, 230, 228, 227, 230, 228, 227, 225, 230, 228, 227, 225, 230, 228, 227, 222, 222, 227, 232, 228, 222, 232, 222, 222, 222, 222, 227, 232, 228, 222, 232, 222, 222, 222, 222, 227};

void setup() {
  //set up for built-in led light
  pinMode(redPin,OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  setRGB(255, 255,255);
  
  //set up for led light that we added in
  pinMode(RGBred,OUTPUT);
  pinMode(RGBgreen,OUTPUT);
  pinMode(RGBblue,OUTPUT);
  
  //assign servos
  servoLeft.attach(12);
  servoRight.attach(11);
  servoLeft.writeMicroseconds(1500); // zeros it
  servoRight.writeMicroseconds(1500); // zeros it
  delay(50);
  Serial.begin(9600); // Connection to our computers (USB) -- start the serial monitor so we can view the output
  Serial1.begin(9600); // Connection to the RFID reader -- connect to the serial port for the RFID reader
  Serial2.begin(9600); // Connection to the XBee

  //LCD communication innitiation
  mySerial.begin(9600);
  delay(100);
  mySerial.write(12); // clear
  delay(10);
  mySerial.write(22); // no cursor no blink
  delay(10);
  //mySerial.write(17); // backlight -- commented out because it wasnt needed, so we are saving battery

  // External LED 
  // low or 0 = on
  // this ensures the extrernal RBG starts in the OFF state
  digitalWrite(RGBred, HIGH);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBblue, HIGH);

  //music
  Wire.begin(); //initializes the Wire library and joins the I2C bus as a controller
}

void loop() {
  int qti1 = rcTime(lineSensor1); 
  int qti2 = rcTime(lineSensor2); 
  int qti3 = rcTime(lineSensor3); 

  int state = convertToBinary(qti1, qti2, qti3);
  
  switch (state){
    //reaches a hashark
    case 0:
      stop(1000);
      switch(count){
        //cases 1-5 are for the first few hashmarks
        //flash light, move forward, and check for RFID tag
        case 1:
          stop(100);
          setRGB(0,255,0,500);
          setRGB(255,255,255);
          delay(1000);
          if (Serial1.available() >0){
            position = 1;
            Serial.println("test1");
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen,LOW);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);

            while (Serial1.available()>0){
               Serial1.read();
             }
          } else if (Serial1.available() >0){
            position = 1;
            Serial.println("test1");
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen,LOW);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);

            while (Serial1.available()>0){
               Serial1.read();
             }
          }else {
            Serial.println("test2");
            digitalWrite(RGBred, LOW);
            digitalWrite(RGBgreen,HIGH);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);
          }
          moveForward(200);
          break;
        case 2:
          stop(100);
          setRGB(255,0,255,500);
          setRGB(255,255,255);
          delay(200);
          if (Serial1.available() >0){
            position = 2;
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen,LOW);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);
            while (Serial1.available()>0){
              Serial1.read();
            }
          } else if (Serial1.available() >0){
            position = 2;
            Serial.println("test1");
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen,LOW);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);
            while (Serial1.available()>0){
               Serial1.read();
             }
          } else {
            digitalWrite(RGBred, LOW);
            digitalWrite(RGBgreen,HIGH);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);
          }
          moveForward(200);
          break;
        case 3:
          stop(100);
          setRGB(255,255,0,500);
          setRGB(255,255,255);
          delay(200);
          if (Serial1.available() >0){
            position = 3;
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen,LOW);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);
            while (Serial1.available()>0){
              Serial1.read();
            }
          } else if (Serial1.available() >0){
            position = 3;
            Serial.println("test1");
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen,LOW);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);

            while (Serial1.available()>0){
               Serial1.read();
             }
          }else {
            digitalWrite(RGBred, LOW);
            digitalWrite(RGBgreen,HIGH);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);
          }
          moveForward(200);
          break;
        case 4:
          stop(100);
          setRGB(0,255,255,500);
          setRGB(255,255,255);
          delay(200);
          if (Serial1.available() >0){
            position = 4;
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen,LOW);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);
            while (Serial1.available()>0){
              Serial1.read();
            }
          } else if (Serial1.available() >0){
            position = 4;
            Serial.println("test1");
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen,LOW);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);

            while (Serial1.available()>0){
               Serial1.read();
             }
          }else {
            digitalWrite(RGBred, LOW);
            digitalWrite(RGBgreen,HIGH);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);
          }
          moveForward(200);
          break;
        case 5:
          stop(100);
          setRGB(0,0,0,500);
          setRGB(255,255,255);
          delay(200);
          if (Serial1.available() >0){
            position = 5;
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen,LOW);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);
            while (Serial1.available()>0){
              Serial1.read();
            }
          } else if (Serial1.available() >0){
            position = 5;
            Serial.println("test1");
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen,LOW);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);

            while (Serial1.available()>0){
               Serial1.read();
             }
          }else {
            digitalWrite(RGBred, LOW);
            digitalWrite(RGBgreen,HIGH);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);
          }
          delay(35000);
          moveForward(200);
          break;
        //the first few hash marks have been passed
        //cross over white space and enter the "circle"
        case 6:
          moveForward(100);
          servoLeft.writeMicroseconds(1700);
          servoRight.writeMicroseconds(1650);
          delay(500);
          break;
        //reaches our RFID stop (last hashmark) and stops
        // sends RFID count
        case 7:
          servoLeft.detach();
          servoRight.detach();
          delay(1000);
          if (Serial1.available() >0){
            transmit = position + 50;
            results[0] = position;
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen,LOW);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);
            while (Serial1.available()>0){
              Serial1.read();
            } 
          }else {
            transmit = 50;
            results[0] = 0;
            digitalWrite(RGBred, LOW);
            digitalWrite(RGBgreen,HIGH);
            digitalWrite(RGBblue, HIGH);
            delay(200);
            digitalWrite(RGBred, HIGH);
            digitalWrite(RGBgreen, HIGH);
            digitalWrite(RGBblue, HIGH);
          }
          //Serial2.print(position * lastHash + 50);
          receive_data();
          break;
      }
      moveForward(200);
      count ++;
      break;
    //all other cases for corrections in case it moves off course
    //or for turning while it is on the semi-circle
    case 1:
      slightTurnLeft();
      break;
    case 3:
      slightTurnLeft();
      break;
    case 4:
      slightTurnRight();
      break;
    case 5:
      moveForward(50);
      break;
    case 6:
      slightTurnRight();
      break;
    case 7:
      if (count == 5){
        moveForward(50);
        break;
      } 
      break;
  }
}

//Defines funtion 'rcTime' to read value from QTI sensor
// From Ch. 6 Activity 2 of Robotics with the BOE Shield for Arduino
long rcTime(int pin){
  pinMode(pin, OUTPUT);    // Sets pin as OUTPUT
  digitalWrite(pin, HIGH); // Pin HIGH
  delay(1);                // Waits for 1 millisecond
  pinMode(pin, INPUT);     // Sets pin as INPUT
  digitalWrite(pin, LOW);  // Pin LOW
  long time = micros();    // Tracks starting time
  while(digitalRead(pin)); // Loops while voltage is high
  time = micros() - time;  // Calculate decay time
  return time;             // Return decay time
}

//funciton converts the sensor readings into binary so that we can create our states
int convertToBinary(int qti1, int qti2, int qti3){
  int state = 4*(qti1 < 400) + 2*(qti2 < 400) + (qti3 < 400);
  return state;
}

//following functions defie the different movements the bot can make
//they are called within the switch cases based on states
//servos are mounted as mirror images of eachother, so clockwise (forward) for one side would be counterclockwise (backwards) for the other
void moveForward(int time){
  servoLeft.writeMicroseconds(1700); //1700 is clockwise for the left servo
  servoRight.writeMicroseconds(1300); //1300 is clockwise for the right servo
  //so the bot moves forward at full speed
  delay(time);
}

void moveBackward(int time){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
  delay(time);
}

void stop(int time){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(time);
}

void slightTurnRight(){ 
  servoLeft.writeMicroseconds(1525); //moves cloclwise 
  servoRight.writeMicroseconds(1525); //moves counterclockwise
}
void slightTurnLeft(){ 
  servoLeft.writeMicroseconds(1475); //moves counterclockwise
  servoRight.writeMicroseconds(1475); //moves cloclwise 
}
//our RGB funcitons that are called within switch to flash light 
//of different colors at each hashmark
void setRGB(int r, int g, int b, int time){
  analogWrite(redPin, r);
  analogWrite(greenPin,g);
  analogWrite(bluePin, b);
  delay(time);
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
}
void setRGB(int r, int g, int b){
  analogWrite(redPin, r);
  analogWrite(greenPin,g);
  analogWrite(bluePin, b);
}

void transmit_func(int value){
  digitalWrite(RGBred, HIGH);
  digitalWrite(RGBgreen,HIGH);
  digitalWrite(RGBblue, LOW);
  delay(250);
  digitalWrite(RGBred, HIGH);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBblue, HIGH);
  char out = value;
  Serial2.print(out);
}

void display(int results[]){
  String text = "";
  int sum = 0;
  for (int i =0; i < 5; i++){ //goes though each value in results and adds it to the text string
    text += results[i];
    text+= ",";
    sum += results[i];
  }
  //you can then print the string on the LDC display, showing the values for each bot and the sum of the values!
  text += sum;
  mySerial.write(12);
  delay(10);
  mySerial.write(22);
  delay(10);
  mySerial.print(text);
}

//goes through each value in results to check if they are still -1, meaning the list is 
//incomplete and some bots havent sent/we havent read thier values
bool check_array(){
  for (int i =0; i < 5; i++){
    if (results[i] <0){
      return false;
    }
  }
  return true;
}

/*
It receives data from the other bots.
It displays the entries of the results array, which is updated in the while lopp of this function.
The results array represents each received signal from the other bots.
*/
void receive_data(){
  display(results);
  int loop = 0;
  while (1){
    int incoming = Serial2.read(); //reads from what others send
    
    //if the value sent is 37 or 36 it will trigger the celebration
    if(incoming==37){ 
      light_show();
      //delay(1000);
    }
    if(incoming==36){ 
      play_song();
      //delay(1000);
    }

    //it will check the results list bc it mught be a signal from another bot, not the celebration!
    if (!check_array()){ //if the list of results is not completely filled out (aka -1's)
      int group_num = incoming/10 - 5; //group number, so we would be 0
      if (group_num < 5 && group_num > -1){ //if its a value goup number 
        digitalWrite(RGBred, LOW);
        digitalWrite(RGBgreen, LOW);
        digitalWrite(RGBblue, LOW);
        delay(50);
        digitalWrite(RGBred, HIGH);
        digitalWrite(RGBgreen, HIGH);
        digitalWrite(RGBblue, HIGH);
        int score = incoming % 10; //the position of the card/trigger for each bot
        results[group_num] = score; //here we are going to the index of each group, to set it to their new value, replacing -1
        display(results); //take new results list, makes it into a string to print on LCD display
      }
      
      if (loop % 100 == 0){ //it makes the while loop run 100 times before sending our data to others
        transmit_func(transmit);
      }
      delay(10);
      loop ++;
    }
  }
}

//This function controls both your on-board LED and external LED 
//O = on board led, E = external led 
void light_show(){
  //O purple, E green
  setRGB(0, 255, 0);
  digitalWrite(RGBblue, HIGH); //replace with digitalWrite() if needed
  digitalWrite(RGBgreen, LOW);
  digitalWrite(RGBred, HIGH);
  delay(500);

  //O white, E red
  setRGB(0, 128, 128);
  digitalWrite(RGBblue, HIGH);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBred, LOW);
  delay(500);

  //O blue, E purple
  setRGB(255, 255, 0);
  digitalWrite(RGBblue, LOW);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBred, LOW);
  delay(500);

  // O cyan, E blue
  setRGB(255, 0, 0);
  digitalWrite(RGBblue, LOW);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBred, HIGH);
  delay(500);

  //O cyan, E purple
  setRGB(255, 128, 128);
  digitalWrite(RGBblue, LOW);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBred, LOW);
  delay(500);

  // O purple, E cyan - cyan is blue and green on, red off
  setRGB(128, 255, 64);
  digitalWrite(RGBblue, LOW);
  digitalWrite(RGBgreen, LOW);
  digitalWrite(RGBred, HIGH);
  delay(500);

  //Both blue
  setRGB(255, 255, 0);
  digitalWrite(RGBblue, LOW);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBred, HIGH);
  delay(500);

  // O cyan, external blue
  setRGB(255, 128, 128);
  digitalWrite(RGBblue, LOW);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBred, HIGH);
  delay(500);

  //O white (slighly blue-ish), E green
  setRGB(200, 128, 0);
  digitalWrite(RGBblue, HIGH);
  digitalWrite(RGBgreen, LOW);
  digitalWrite(RGBred, HIGH);
  delay(500);

  //O white, E yellow
  setRGB(0, 64, 0);
  digitalWrite(RGBblue, HIGH);
  digitalWrite(RGBgreen, LOW);
  digitalWrite(RGBred, LOW);
  delay(500);

  // O purple, E blue
  setRGB(64, 255, 64);
  digitalWrite(RGBblue, LOW);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBred, HIGH);
  delay(500);

  //O purple, E red
  setRGB(128, 255, 0);
  digitalWrite(RGBblue, HIGH);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBred, LOW);
  delay(500);

  setRGB(255, 255, 255);
  digitalWrite(RGBblue, HIGH);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBred, HIGH);

  //O pink (purple), external green
  setRGB(0, 255, 128);
  digitalWrite(RGBblue, HIGH);
  digitalWrite(RGBgreen, LOW);
  digitalWrite(RGBred, HIGH);
  delay(500);
  
  //O green, external yellow
  setRGB(255, 128, 255);
  digitalWrite(RGBblue, HIGH);
  digitalWrite(RGBgreen, LOW);
  digitalWrite(RGBred, LOW);
  delay(500);

  //O cyan, external purple
  setRGB(255, 0, 0);
  digitalWrite(RGBblue, LOW);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBred, LOW);
  delay(500);

  //0 mint-white, E green
  setRGB(128, 0, 200);
  digitalWrite(RGBblue, HIGH);
  digitalWrite(RGBgreen, LOW);
  digitalWrite(RGBred, HIGH);
  delay(500);

  //O blue, E green
  setRGB(200, 255, 64);
  digitalWrite(RGBblue, HIGH);
  digitalWrite(RGBgreen, LOW);
  digitalWrite(RGBred, HIGH);
  delay(500);

  //O yellow, E blue (light blue)
  setRGB(128, 0, 255);
  digitalWrite(RGBblue, LOW);
  digitalWrite(RGBgreen, LOW);
  digitalWrite(RGBred, HIGH);
  delay(500);

  //O cyan, E green
  setRGB(255, 0, 0);
  digitalWrite(RGBblue, HIGH);
  digitalWrite(RGBgreen, LOW);
  digitalWrite(RGBred, HIGH);
  delay(500);

  //O cyan, E green
  setRGB(255, 128, 0);
  digitalWrite(RGBblue, HIGH);
  digitalWrite(RGBgreen, LOW);
  digitalWrite(RGBred, HIGH);
  delay(500);

  //O blue-ish white, E is off
  setRGB(200, 128, 0);
  digitalWrite(RGBblue, HIGH);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBred, HIGH);
  delay(500);

  // O white, E yellow
  setRGB(0, 64, 128);
  digitalWrite(RGBblue, HIGH);
  digitalWrite(RGBgreen, LOW);
  digitalWrite(RGBred, LOW);
  delay(500);

  //O white, E purple
  setRGB(64, 0, 64);
  digitalWrite(RGBblue, LOW);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBred, LOW);
  delay(500);

  // O white-ish, E cyan
  setRGB(128, 64, 0);
  digitalWrite(RGBblue, LOW);
  digitalWrite(RGBgreen, LOW);
  digitalWrite(RGBred, HIGH);
  delay(500);

  //Turn off both
  setRGB(255, 255, 255);
  digitalWrite(RGBblue, HIGH);
  digitalWrite(RGBgreen, HIGH);
  digitalWrite(RGBred, HIGH);
}

//Plays the song
void play_song() { 
 for(long k=0; k<43; k++){
    mySerial.write(durs[k]); mySerial.write(octs[k]); mySerial.write(notes[k]);
    int len = 214 - durs[k];
    float del = 2000 / pow(2, len);
    delay(int(del*1.1));
  }
}