/*-----( Import needed libraries )-----*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <avr/dtostrf.h>  Uncomment for Arduino Due
#include "SELogo.h"
#include "Oxygen.h"
#include "Suit_Energy.h"

/*-----( Declare Constants and Pin Numbers )-----*/
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
//int led13 = 13;
//int led12 = 12;

/*-----( Declare objects )-----*/
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


/*-----( Declare Variables )-----*/
const byte numChars = 128;
char receivedChars[numChars];
boolean message = false;
char startMarkerUsed = '.';

void setup()
{
  //pinMode(led13, OUTPUT);      // sets the digital pin as output
  //pinMode(led12, OUTPUT);      // sets the digital pin as output
  Serial.begin(115200);  //set serial to 115200 baud rate
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  display.drawBitmap(0, 0, Logo, 128, 64, 1);
  display.display();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  display.drawBitmap(0, 0, Logo, 128, 64, 1);
  display.display();

  delay(3000);
  Serial.println();
  Serial.println("setup complete");
  Serial.print("Free RAM at setup: ");
  Serial.println(freeRam());

}
//~4, Here is a first string to parse^<234, 467, 4587, 125><1234, 9467, 4587, 6125>~3, Here is a second string to parse!^~4, Here is a third string to parse^<945, 7, 28, 1159>~3, Here is a fourth string to parse!^
// <1,3,0021,100>

void loop()
{
  //Serial Double Format (StartBit)(DataType,Item,CurrentValue,MaxValue)(StopBit)
  //StartBit = "\x02"
  //DataType = Double value starting from 1. Indicates if values are Int, Float, Bool, etc.
  //Item = Double begining with 1. Indicates what the message content is i.e. Health, speed, dampers.
  //CurrentValue = Send as a double (4 byte limit) send coordinates as strings
  //MaxValue = Send as a double (4 byte limit) send coordinates as strings
  //StopBit = "\x03"

  //Serial String Format (StartBit)(Item,StringValue)(StopBit)
  //StartBit = "\x04"
  //Item = Int begining with 1. Indicates what the message content is i.e. 1 =X coordinate, 2=Y Coordinate, 3=Z coordinate
  //StringValue = Send as a double (4 byte limit) send coordinates as strings
  //StopBit = "\x05"

  static boolean recvInProgress = true;
  static byte index = 0;
  //char startMarker = 0x2;
  //char endMarker = 0x3;
  char startMarker = '<';
  char endMarker = '>';
  char startMarkerString = '~';
  char endMarkerString = '^';
  char rc;

  //Serial.println("Grabbing message to parse:");
  while (Serial.available() > 0 && message == false)
  {
    rc = Serial.read();
    if (rc == startMarker) {
      startMarkerUsed = rc;
      Serial.println(startMarkerUsed);
      recvInProgress = true;
    }
    if (rc == startMarkerString) {
      startMarkerUsed = rc;
      Serial.println(startMarkerUsed);
      recvInProgress = true;
    }
    if (recvInProgress == true)
    {
      delay(1);

      Serial.print(rc);

      if (rc != endMarker && rc != endMarkerString )
      {
        delay(1);
        receivedChars[index] = rc;
        index++;
        if (index >= numChars)
        {
          index = numChars -1 ;
        }
      }

      else
      {
        delay(1);
        Serial.println();
        Serial.println("Terminating read");
        receivedChars[index] = '\0'; // terminate the string
        recvInProgress = false;
        index = 0;
        message = true;
        Serial.print("All Characters reveived: ");
        Serial.println(String(receivedChars));
        Serial.println();

      }
    }

  }   
  //Serial.println("End of message");   
  //delay(1000); 
  //Serial.println("End of Serial available");
  //delay(10000);

  switch (startMarkerUsed)
  {
    case '<':
      //message = true;
      startMarkerUsed = '.';
      parseDoubleMessage();
      break;

    case '~':
      //message = true;
      startMarkerUsed = '.';
      parseStringMessage();
      break;

    case '.':
      //do nothing
      break;

    default:
      //DebugPrint("Default case: ", 1);
      break;

  }
    //Serial.print("RAM after Execution: ");
    //Serial.println(freeRam());
    //delay(5000);
}
void DebugPrint( char *debugMessage, int Var1)
{
  Serial.print (debugMessage);
  Serial.print (Var1, DEC);
  Serial.println();
}
void parseDoubleMessage()
{
  char delimiter[] = ",";
  char* valPosition;
  double doublearray[5];
  int dataType = 0;
  int item = 0;
  double CurrentValue = 0.0;
  double MaxValue = 0.0;
  int i = 0;

  //Serial.println("Parsing Double Message:");

  if (message == true)
  {
    //Serial.print("RecievedChars: ");
    //Serial.println(receivedChars);
    valPosition = strtok(receivedChars, delimiter);

    while (valPosition != NULL)
    {
      doublearray[i] = atoi(valPosition);
      valPosition = strtok(NULL, delimiter);
      //DebugPrint("Item Index: ", i);
      //DebugPrint("Loop Value: ", doublearray[i]);
      i++;
    }
    
    //DebugPrint("Current Item1: ", doublearray[0]);
    //DebugPrint("Current Item2: ", doublearray[1]);
    // DebugPrint("Current Item3: ", doublearray[2]);
    //DebugPrint("Current Item4: ", doublearray[3]);
    //String serialDebug = "";
    //serialDebug = " Array of ";
    //serialDebug +=  i,DEC ;
    //serialDebug += " doubles created.";
    //Serial.println(serialDebug);

    dataType = (int)doublearray[0];
    item = (int)doublearray[1];
    CurrentValue =  doublearray[2];
    MaxValue =  doublearray[3];
    doublearray[4] = '\0';
    //DebugPrint("DataType: ", dataType);
    //DebugPrint("item: ", item);
    DebugPrint("CurrentValue: ", CurrentValue);
    //DebugPrint("MaxValue: ", MaxValue);
    message = false;



    //Message received:
    //digitalWrite(led13, HIGH);   // turn the LED on (HIGH is the voltage level)
    //delay(1000);               // wait for a second
    //digitalWrite(led13, LOW);    // turn the LED off by making the voltage LOW
    //delay(1000);               // wait for a second

      
  }
      switch (item)
    {
      case 1:
        //DisplayHealth();
        break;

      case 2:
        DisplayEnergy(CurrentValue);
        break;

      case 3:
        DisplayOxygen(CurrentValue);
        break;

      default:
        //DebugPrint("Default case: ", 1);
        break;

    }
    //delay(5000);
    Serial.println("Double Parsing Completed.");
    delay(2000);
}
void parseStringMessage()
{
  char delimiter[] = ",";
  char* valPosition;
  int ItemType = 0;
  char ItemText[64];
  int i = 0;

  //Serial.println("Parsing String Message:");

  if (message == true)
  {
    //Serial.print("RecievedChars: ");
    //Serial.println(receivedChars);
    valPosition = strtok(receivedChars, delimiter);
    ItemType = atoi(valPosition);
    valPosition = strtok(NULL, delimiter);
    strcpy(ItemText, valPosition);
  }

  //         DebugPrint("Item Type: ", ItemType);
  //         String serialDebug = "";
  //         serialDebug = "String received: ";
  //         serialDebug += String(ItemText);
  //         Serial.println(serialDebug);
  //         digitalWrite(led12, HIGH);   // turn the LED on (HIGH is the voltage level)
  //         delay(1000);               // wait for a second
  //         digitalWrite(led12, LOW);    // turn the LED off by making the voltage LOW
  //         delay(1000);               // wait for a second
  //message = false;
  //Serial.println("End of String Parsing");
}
void DisplayEnergy(double CurrentValue)
{
  char TempString[7];
  dtostrf(CurrentValue / 100, 2, 2, TempString);
  String displayVal = String(TempString);  // cast it to string from char
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  display.display();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.drawBitmap(0, 0, Suit_Energy, 128, 64, 1);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(34, 36);
  display.println(displayVal + '%');
  display.display();
  Serial.println("Energy displayed.");
  //delay(2000);
}
void DisplayOxygen(double CurrentValue)
{
  char TempString[7];
  dtostrf(CurrentValue / 100, 2, 2, TempString);
  String displayVal = String(TempString);  // cast it to string from char
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  display.display();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.drawBitmap(0, 0, Oxygen, 128, 64, 1);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(34, 36);
  display.println(displayVal + '%');
  display.display();
  Serial.println("O2 displayed.");
  //delay(2000);
}
 int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

