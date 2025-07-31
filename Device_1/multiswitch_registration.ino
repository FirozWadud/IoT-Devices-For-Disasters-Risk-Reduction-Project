
#include <SoftwareSerial.h>
#include <EEPROM.h>

#define pushButton0 A0
#define pushButton1 A1
#define pushButton2 A2
#define pushButton3 A3
#define pushButton4 A4
int Msg_Status = 0;


char incomingByte;
String inputString;
String senderNumber;
String ReceivedText;
String msg;
String retrievedString;
String retrievedStringroot;
String mode;
String Address;
String Phoneno1;
String Phoneno2;
String Phoneno3;
String Phoneno4;
String Phoneno5;
String test;


String activationText = "activate"; //can be activated from authority through sms passcode

SoftwareSerial mySerial(10, 9);

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);

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

  pinMode(pushButton0, INPUT);
  pinMode(pushButton1, INPUT);
  pinMode(pushButton2, INPUT);
  pinMode(pushButton3, INPUT);
  pinMode(pushButton4, INPUT);

  
}

void loop()
{

  int buttonState0 = digitalRead(pushButton0);
  int buttonState1 = digitalRead(pushButton1);
  int buttonState2 = digitalRead(pushButton2);
  int buttonState3 = digitalRead(pushButton3);
  int buttonState4 = digitalRead(pushButton4);


  Serial.print(buttonState0);
  Serial.print("    ");
  Serial.print(buttonState1);
  Serial.print("    ");
  Serial.print(buttonState2);
  Serial.print("    ");
  Serial.print(buttonState3);
  Serial.print("    ");
  Serial.print(buttonState4);
  Serial.println("    ");
  receiveSMS();  // Receive a sms whenever arrive and act according to modes;
  if (buttonState0 == 0 || buttonState1 == 0 || buttonState2 == 0 || buttonState3 == 0 || buttonState4 == 0)
  {
    //Serial.println("Entered if");

    if((Msg_Status  == 0) ){
      //Serial.println("Entered loop");
       
     registration();// This function assigns registered information to variables
     delay(500);
     String cat;
     //cat = readStringFromEEPROM(200);// The text message you want to send to 5 people
     cat = "Drr:switch_pressed";
      sendSMS(Phoneno1, cat);
      sendSMS(Phoneno2, cat);
      sendSMS(Phoneno2, cat);
      sendSMS(Phoneno3, cat);
      sendSMS(Phoneno3, cat);
      sendSMS(Phoneno4, cat);
      sendSMS(Phoneno4, cat);
      sendSMS(Phoneno5, cat);
      sendSMS(Phoneno5, cat);
      Msg_Status = 1; 
      
      }
  }else{
    Msg_Status = 0;
    }
  
}


void sendSMS(String number, String msg){
  //msg = "Drr:switch_pressed";
  while(!mySerial.available()){
  mySerial.println("AT");
      delay(500); 
      Serial.println("Connecting...");
  }

  Serial.println("Connected!");  
  mySerial.println("AT+CMGF=1");
  delay(500);  
  mySerial.println("AT+CNMI=1,2,0,0,0"); 
  delay(500);
  mySerial.println("AT+CMGL=\"REC UNREAD\"");
  
mySerial.print("AT+CMGS=\"");mySerial.print(number);mySerial.println("\"\r\n"); //AT+CMGS=”Mobile Number” <ENTER> - Assigning recipient’s mobile number
delay(500);
mySerial.println(msg); // Message contents
delay(500);
mySerial.write(byte(26)); //Ctrl+Z  send message command (26 in decimal).
delay(500);
Serial.print(msg);
Serial.print(" SMS sent to:");
Serial.println(number);
}

void writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  //Serial.println("Writing start eeprom");
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);

  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
}

String readStringFromEEPROM(int addrOffset)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
 // Serial.println(newStrLen);

  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
    //Serial.print(data[i]);
  }
  data[newStrLen] = '\0'; 
  return String(data);
}


void registration(){
  String Str;
   retrievedString = "";
   Str = readStringFromEEPROM(0);
   Serial.println("I recieved it");
   Serial.println(Str);
   Address = "";
   Phoneno1 = "";
   Phoneno2 = "";
   Phoneno3 = "";
   Phoneno4 = "";
   Phoneno5 = "";

  int spaceCounter = 0;
  //Serial.println(retrievedString);
  
  int len = Str.length();
  //Serial.println(len);
  for (int i = 1; i < len; i++)
  { 
    if(Str.charAt(i) == ' '){
      i++;
      
      spaceCounter++;
      }
    if(spaceCounter == 1){Address.concat(Str.charAt(i));}
    else if(spaceCounter == 2){Phoneno1.concat(Str.charAt(i));}
    else if(spaceCounter == 3){Phoneno2.concat(Str.charAt(i));}
    else if(spaceCounter == 4){Phoneno3.concat(Str.charAt(i));}
    else if(spaceCounter == 5){Phoneno4.concat(Str.charAt(i));}
    else if(spaceCounter == 6){Phoneno5.concat(Str.charAt(i));}
    
       
}
}


void receiveSMS()
{ 
  inputString = ""; 
  if(mySerial.available()){
    while(mySerial.available()){
      delay(1);
      incomingByte = mySerial.read();
      inputString.concat(incomingByte); 
    }
    delay(500);  
    //Serial.print("input : ");Serial.print(inputString);Serial.println("   end");
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
  //Serial.print("Number:"); Serial.println(senderNumber);
  //Serial.print("SMS:"); Serial.println(ReceivedText);

  if (ReceivedText.charAt(0) == '1'){
   
   Serial.println("Saving to eeprom... ");
   writeStringToEEPROM(0,ReceivedText);
   writeStringToEEPROM(0,ReceivedText);
//   retrievedStringroot = readStringFromEEPROM(0);
//   retrievedString =  retrievedStringroot;
   registration();
  Serial.println("Registration information :");
  Serial.print("Address : ");Serial.println(Address);
  Serial.print("Phone #1 : ");Serial.println(Phoneno1);
  Serial.print("Phone #2 : ");Serial.println(Phoneno2);
  Serial.print("Phone #3 : ");Serial.println(Phoneno3);
  Serial.print("Phone #4 : ");Serial.println(Phoneno4);
  Serial.print("Phone #5 : ");Serial.println(Phoneno5);
  //Serial.print("Message : ");Serial.println(msg);

  String message = "Registered Numbers:"+Phoneno1+" "+Phoneno2+" "+Phoneno2+" "+Phoneno4+" "+Phoneno5;
  sendSMS(senderNumber, message);
  Serial.println(message);
  Serial.println("Registration Done...");
  }

  if(ReceivedText.charAt(0) == '0'){
    retrievedStringroot = "";
    writeStringToEEPROM(200,ReceivedText);
    
    }
   
  }   
}
