/*-----( Import needed libraries )-----*/

/*-----( Declare Constants and Pin Numbers )-----*/
int led13 = 13;
int led12 = 12;
/*-----( Declare objects )-----*/

/*-----( Declare Variables )-----*/
const byte numChars = 64;
char receivedChars[numChars];
boolean message = false;
char startMarkerUsed= '.';

void setup() 
{
  pinMode(led13, OUTPUT);      // sets the digital pin as output
  pinMode(led12, OUTPUT);      // sets the digital pin as output
  Serial.begin(115200);  //set serial to 115200 baud rate
}
//~4, Here is a first string to parse^<234, 467, 4587, 125><1234, 9467, 4587, 6125>~3, Here is a second string to parse!^~4, Here is a third string to parse^<945, 7, 28, 1159>~3, Here is a fourth string to parse!^
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
                      
 recvData();
 
 switch(startMarkerUsed)
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
    DebugPrint("Default case: ", 1);
    break;
  
 }
	
}
void DebugPrint( char *debugMessage, int Var1)
{                          
      Serial.print (debugMessage);
      Serial.print (Var1,DEC); 
      Serial.println(); 
}   
void recvData() 
{
	static boolean recvInProgress = false;
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
			  if (rc == startMarker){ startMarkerUsed = rc; Serial.println(startMarkerUsed); }
			  else if (rc == startMarkerString){ startMarkerUsed = rc; Serial.println(startMarkerUsed); }
		      if (recvInProgress == true) 
		      {
             delay(1);
			 
			 //Serial.print(rc);
			 
			      if (rc != endMarker || rc != endMarkerString ) 
			      {              
             delay(1);
				      receivedChars[index] = rc;
				      index++;
				      if (index >= numChars)
				      {
					      index = numChars - 1;
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
		    else if (rc == startMarker || rc == startMarkerString) 
		    {             
			    startMarkerUsed = rc;
			    recvInProgress = true;
         delay(1);
		    }
	    }
}

void parseDoubleMessage() 
{
          char delimiter[]= ",";
          char* valPosition; 
          double doublearray[5];
          int dataType = 0;
          int item = 0;
          double CurrentValue = 0.0;
          double MaxValue = 0.0;
          int i=0;          
          
          Serial.println("Parsing Double Message:");         
          
	if (message == true) 
        {
			Serial.print("RecievedChars: ");
			Serial.println(receivedChars);
            valPosition = strtok(receivedChars, delimiter);
                         
                    while(valPosition != NULL)
                    {                    
                    doublearray[i] = atoi(valPosition);
                    valPosition = strtok(NULL, delimiter);
                    DebugPrint("Item Index: ", i);                                        
                    DebugPrint("Loop Value: ", doublearray[i]);
                    i++;                    
                    }
					doublearray[i] = '\0';
                    DebugPrint("Current Item1: ", doublearray[0]);
                    DebugPrint("Current Item2: ", doublearray[1]);
                    DebugPrint("Current Item3: ", doublearray[2]);
                    DebugPrint("Current Item4: ", doublearray[3]);
                    String serialDebug = "";
                    serialDebug = " Array of ";
                    serialDebug +=  i,DEC ;
                    serialDebug += " doubles created.";
                    Serial.println(serialDebug);                   

					dataType = (int)doublearray[0];                   
					item = (int)doublearray[1];            
					CurrentValue =  doublearray[2];                 
					MaxValue =  doublearray[3];
					//DebugPrint("DataType: ", dataType);
					//DebugPrint("item: ", item);
					//DebugPrint("CurrentValue: ", CurrentValue);
					//DebugPrint("MaxValue: ", MaxValue);                  
					message = false;
					
    //Message received:
                digitalWrite(led13, HIGH);   // turn the LED on (HIGH is the voltage level)
                delay(1000);               // wait for a second
                digitalWrite(led13, LOW);    // turn the LED off by making the voltage LOW
                delay(1000);               // wait for a second
	}
}
void parseStringMessage()
{
          char delimiter[]= ",";
          char* valPosition; 
          int ItemType = 0;
          char ItemText[64];
          int i=0;       
          
          Serial.println("Parsing String Message:");        
          
  if (message == true) 
        {
			Serial.print("RecievedChars: ");
			Serial.println(receivedChars);                
          valPosition = strtok(receivedChars, delimiter);
          ItemType = atoi(valPosition);
          valPosition = strtok(NULL, delimiter);  
          strcpy(ItemText, valPosition); 
		  
         }
		  
            DebugPrint("Item Type: ", ItemType);                    
            String serialDebug = "";
            serialDebug = "String received: ";
            serialDebug += String(ItemText);
            Serial.println(serialDebug);                  
            digitalWrite(led12, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(1000);               // wait for a second
            digitalWrite(led12, LOW);    // turn the LED off by making the voltage LOW
            delay(1000);               // wait for a second
			message = false;
			Serial.println("End of String Parsing");
}

