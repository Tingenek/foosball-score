/*
 * Foosball Line Scorer
 * MLawson @tingenek 2016
 * For llamas everywhere
 */

#include <SPI.h>
#include <glcd.h>
#include <fonts/allFonts.h>

#define LCD_POWER             (40u)
#define LCD_BACKLIGHT         (35u)
#define SRF_SLEEP             (61u)
#define SRF_AT_COMMAND        (43u)
#define PIEZO                 (66u)
#define PIEZO_PWM             (111u)
#define RADIO_SERIAL Serial
#define RADIO_SERIAL_BAUD 115200
#define SENSORPIN1 9
#define SENSORPIN2 8
int sensorState1 = 0, lastState1=0; 
int sensorState2 = 0, lastState2=0; 
uint8_t counter;
byte rx_byte = 0;
uint8_t homescore = 0;
uint8_t awayscore = 0;
  
void setup() {
  randomSeed(analogRead(0));
  //Sensors
  pinMode(SENSORPIN1, INPUT);     
  digitalWrite(SENSORPIN1, HIGH); // turn on the pullup
  pinMode(SENSORPIN2, INPUT);     
  digitalWrite(SENSORPIN2, HIGH); // turn on the pullup
  //Radio on
  RADIO_SERIAL.begin(RADIO_SERIAL_BAUD);
  // Setup radio pins
  pinMode(SRF_AT_COMMAND, OUTPUT);
  pinMode(SRF_SLEEP, OUTPUT);
  // Radio On
  digitalWrite(SRF_SLEEP, LOW);
  //Turn LCD On :-)
  pinMode(LCD_POWER, OUTPUT);
  digitalWrite(LCD_POWER, LOW);
  //Turn Backlight On
  pinMode(LCD_BACKLIGHT, OUTPUT);
  digitalWrite(LCD_BACKLIGHT, HIGH);
  //Init LCD
  GLCD.Init(NON_INVERTED); 
  GLCD.SelectFont(System5x7);
  GLCD.print("Foosball Goal Line v1");
  GLCD.CursorTo(0, 2);
  GLCD.print("Home          Away");
  GLCD.SelectFont(fixednums15x31);
  GLCD.display();
  
  counter = 0;
  RADIO_SERIAL.println("---NEWGAME---");
}

void loop() {
  //Read the sensors
   sensorState1 = digitalRead(SENSORPIN1);
   sensorState2 = digitalRead(SENSORPIN2);  
  
 //We have a winner!
  if (!sensorState1 && lastState1) {
    RADIO_SERIAL.println("SCORE!:HOME");
    homescore ++;
    radio_event();
    delay(200);  
  }

if (!sensorState2 && lastState2) {
    RADIO_SERIAL.println("SCORE!:AWAY");
    awayscore ++;
    radio_event();
    delay(200);  
  }

  //Update states
   lastState1 = sensorState1;
   lastState2 = sensorState2;
  //Show scores 
   display_scores();

}

//Current scores to SRF
void radio_event() { 
  char buffer[15];
  sprintf( buffer, "HOME:%02d-AWAY:%02d",homescore,awayscore);
  RADIO_SERIAL.println(buffer); 
  }

//Current Scores to LCD
void display_scores() { 
  char buffer[15];
  sprintf( buffer, "%02d-:-%02d",homescore,awayscore);
  GLCD.CursorTo(0, 1);
  GLCD.print(buffer);
  GLCD.display();  
  }


