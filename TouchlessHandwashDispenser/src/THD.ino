#include <Stepper.h>
#include <TM1637Display.h>
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
// Define number of steps per rotation:
const int stepsPerRevolution = 1024;
// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

//define echo pins
const int trigpin=5;
const int echopin=6;
float dist;
long durat;

//4 digit display
#define CLK 2
#define DIO 3

// Create display object of type TM1637Display:
TM1637Display display = TM1637Display(CLK, DIO);
// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
// You can set the individual segments per digit to spell words or create other symbols:
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

void setup() {
pinMode(trigpin,OUTPUT);
pinMode(echopin,INPUT);
myStepper.setSpeed(15);
Serial.begin(9600);
display.setSegments(blank);
}

void loop() {
digitalWrite(trigpin,LOW);
delay(2);
digitalWrite(trigpin,HIGH);
delay(10);
digitalWrite(trigpin,LOW);
durat=pulseIn(echopin,HIGH);
dist=durat*0.0342/2;
Serial.print("Distance=");
Serial.println(dist);

//Find object
if((dist <= 6) && (dist >= 1))
{
  // Stepper rotation
  myStepper.step(stepsPerRevolution);
  delay(200);
  myStepper.step(-stepsPerRevolution);

  // 20 sec wash time count down
   // Set the brightness:
  display.setBrightness(7);
  // All segments on:
  display.setSegments(data);
  delay(1000);
  display.clear();
  delay(1000);
  // Show counter:
  
  for (int k = 20; k > 0; k--) {
    display.showNumberDec(k);
    delay(1000);
    display.clear();
  }
  display.setSegments(done);
  delay(3000);
  display.clear();
 
}
else
{
  }
 
}
