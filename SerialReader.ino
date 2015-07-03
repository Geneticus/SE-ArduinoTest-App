/*-----( Import needed libraries )-----*/

/*-----( Declare Constants and Pin Numbers )-----*/
int led = 13;

/*-----( Declare objects )-----*/

/*-----( Declare Variables )-----*/
const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;


void setup() 
{
  pinMode(led, OUTPUT);      // sets the digital pin as output
  Serial.begin(115200);  //set serial to 115200 baud rate
  Serial.println(" Type in Box above, . ");
}

void loop() 
{  
                      //Serial String Format (StartBit)(Priority,Item,CurrentValue,MaxValue,DataType)(StopBit)
                      //StartBit = "\x02"
                      //Priority = 2 digit number starting from 00
                      //Item = 2 digit number starting from 00
                      //CurrentValue = string number
                      //MaxValue = string number
                      //DataType = 2 Digit Alpha srating from AA
                      //StopBit = "\x03"
	recvWithStartEndMarkers();
	showNewData();
}

void recvWithStartEndMarkers() 
{
	static boolean recvInProgress = false;
	static byte ndx = 0;
	char startMarker = 0x2;
	char endMarker = 0x3;
	char rc;
	
	// if (Serial.available() > 0) {
        while (Serial.available() > 0 && newData == false) {
		rc = Serial.read();

		if (recvInProgress == true) {
			if (rc != endMarker) {
				receivedChars[ndx] = rc;
				ndx++;
				if (ndx >= numChars) {
					ndx = numChars - 1;
				}
			}
			else {
				receivedChars[ndx] = '\0'; // terminate the string
				recvInProgress = false;
				ndx = 0;
				newData = true;
			}
		}

		else if (rc == startMarker) {
			recvInProgress = true;
		}
	}
}

void showNewData() {
	if (newData == true) 
        {
                digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
                delay(1000);               // wait for a second
                digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
                delay(1000);               // wait for a second
		//Serial.print("This just in ... ");
		//Serial.println(receivedChars);
		newData = false;
	}
}
