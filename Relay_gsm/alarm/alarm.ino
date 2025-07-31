#include <SoftwareSerial.h>

//sender phone number with country code
const String PHONE = "+8801720182677";

//GSM Module RX pin to Arduino 3
//GSM Module TX pin to Arduino 2
#define rxPin 10
#define txPin 11
SoftwareSerial mySerial(rxPin,txPin);

#define RELAY_1 2
#define RELAY_2 8

String smsStatus,senderNumber,receivedDate,ReceivedText,inputString;
char incomingByte;
boolean isReply = false;

void setup() {
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  delay(500);
  
  Serial.begin(9600);
  Serial.println("Arduino serial initialize");
  
  mySerial.begin(9600);
  Serial.println("SIM800L software serial initialize");

  while(!mySerial.available()){
  mySerial.println("AT");
      delay(1000); 
      Serial.println("Connecting...");
  }

  Serial.println("Connected!");  
  mySerial.println("AT+CMGF=1");
  delay(1000);  
  mySerial.println("AT+CNMI=1,2,0,0,0"); 
  delay(1000);
  mySerial.println("AT+CMGL=\"REC UNREAD\"");


  pinMode(RELAY_1, OUTPUT); //Relay 1
  pinMode(RELAY_2, OUTPUT); //Relay 2

  smsStatus = "";
  senderNumber="";
  receivedDate="";
  ReceivedText="";

  delay(1000);
}

void loop() {
receiveSMS();

}






//************************************************************


void receiveSMS()
{ 

    smsStatus = "";
  senderNumber="";
  receivedDate="";
  ReceivedText="";
  


  inputString = ""; 
  if(mySerial.available()){
    while(mySerial.available()){
      delay(1);
      incomingByte = mySerial.read();
      inputString.concat(incomingByte); 
    }
    delay(100);  
    Serial.print("input : ");Serial.print(inputString);Serial.println("   end");
  }
  
 if (inputString.indexOf("CMT:")>=0){
  
  
  senderNumber  = inputString;
  //get number
  int t1 = senderNumber.indexOf('"');
  senderNumber.remove(0,t1 + 1);
  t1 = senderNumber.indexOf('"');
  senderNumber.remove(t1);
   

  ReceivedText = inputString;
  t1 = ReceivedText.indexOf('"');
  ReceivedText.remove(0,t1 + 1);
  t1 = ReceivedText.indexOf('"');
  ReceivedText.remove(0,t1 + 1);
  t1 = ReceivedText.indexOf('"');
  ReceivedText.remove(0,t1 + 1);
  t1 = ReceivedText.indexOf('"');
  ReceivedText.remove(0,t1 + 1);
  t1 = ReceivedText.indexOf('"');
  ReceivedText.remove(0,t1 + 1);
  t1 = ReceivedText.indexOf('"');
  ReceivedText.remove(0,t1 + 1);
  ReceivedText.remove(0,1);
  ReceivedText.trim();
  
  Serial.print("An SMS is received from ");
  Serial.println(senderNumber);
  Serial.print("SMS: "); Serial.println(ReceivedText);
  Serial.println();
 }

 //Serial.println(ReceivedText.indexOf("Drr: stob_horn_on"));
if(ReceivedText == "Drr: stob_horn_on" ){  
    digitalWrite(RELAY_1, LOW);
    //Reply("Alarm has been ON");
  }
  else if(ReceivedText == "Drr: stob_horn_off" ){
    digitalWrite(RELAY_1, HIGH);
    //Reply("Alarm 1 has been OFF");
  }
 
}

void Reply(String text)
{
    mySerial.print("AT+CMGF=1\r");
    delay(1000);
    mySerial.print("AT+CMGS=\""+senderNumber+"\"\r");
    delay(1000);
    mySerial.print(text);
    delay(100);
    mySerial.write(0x1A); //ascii code for ctrl-26 //sim800.println((char)26); //ascii code for ctrl-26
    delay(1000);
    Serial.println("SMS Sent Successfully.");
}
