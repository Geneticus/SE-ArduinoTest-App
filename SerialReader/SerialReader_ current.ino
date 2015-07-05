/*-----( Import needed libraries )-----*/

/*-----( Declare Constants and Pin Numbers )-----*/
int led = 13;

/*-----( Declare objects )-----*/

/*-----( Declare Variables )-----*/
const byte numChars = 32;
char receivedChars[numChars];
boolean message = false;


void setup() 
{
  pinMode(led, OUTPUT);      // sets the digital pin as output
  Serial.begin(115200);  //set serial to 115200 baud rate
}

void loop() 
{  
                      //Serial String Format (StartBit)(DataType,Item,CurrentValue,MaxValue)(StopBit)
                      //StartBit = "\x02"
                      //DataType = Integer value starting from 1. Indicates if values are Int, Float, Bool, etc.                      
                      //Item = Number begining with 1. Indicates what the value is i.e. Health, speed, dampers.
                      //CurrentValue = can be any type as indicated by DataType
                      //MaxValue = can be any numeric as indicated by DataType
                      //StopBit = "\x03"
	recvData();
	processMessage();
}

void recvData() 
{
	static boolean recvInProgress = false;
	static byte ndx = 0;
	//char startMarker = 0x2;
	//char endMarker = 0x3;
        char startMarker = '<';
	char endMarker = '>';
	char rc;
	
	// if (Serial.available() > 0) {
        while (Serial.available() > 0 && message == false) {
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
				message = true;
			}
		}

		else if (rc == startMarker) {
			recvInProgress = true;
		}
	}
}

void processMessage() 
{
          char delimiter[]= ",";
          char* valPosition; 
          int integerarray[] = {0};
          int dataType = 0;
          int i=0;
          String serialDebug = "";
          
	if (message == true) 
        {
		            Serial.println(receivedChars);
                //This initializes strtok with our string to tokenize
                valPosition = strtok(receivedChars, delimiter);
                 //if(valPosition == 1)
                 //{
                 // dataType = atoi(valPosition);
//**********************************************************************here is where I'm stuck
                 //}
                 while(valPosition != NULL)
                    {                    
                    integerarray[i] = atoi(valPosition);
                    valPosition = strtok(NULL, delimiter);
                    i++;                    
                    }
                    //serialDebug = " Array of ";
                    //serialDebug +=  i,DEC ;
                    //serialDebug += " integers created.";
                    //Serial.println(serialDebug);                   

                
		message = false;
    //Message received:
                digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
                delay(1000);               // wait for a second
                digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
                delay(1000);               // wait for a second
	}
}
