
#include <SoftwareSerial.h>
#include <EEPROM.h>

#define smokeSensor_Pin A0 
#define temperatureSensor_pin A1
#define reset_pin A2
#define trigger_pin 4
#define buzzer_pin 6

int smokeSensorValue = 0;
int temperatureSensorValue =0;
int reset_status = 0;
int trigger_status = 0;
int Msg_Status = 0;
int switch_status = 0;
int SmokeThresholod = 500;
int temperatureThreshold = 80;
int errorCounter = 0;

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

SoftwareSerial mySerial(10, 11);

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

  
  
  
  pinMode(buzzer_pin, OUTPUT);
  pinMode(smokeSensor_Pin,INPUT);
  pinMode(temperatureSensor_pin, INPUT);
  pinMode(reset_pin,INPUT);
  pinMode(trigger_pin, INPUT);

  digitalWrite(buzzer_pin,LOW);

  
}

void loop()
{
  //sendSMS()
  //registration();
  readSeonsorValues(); // Reads Smoke sensor 
  receiveSMS();  // Receive a sms whenever arrive and act according to modes;
 // debugSensors();
  //retrievedStringroot = readStringFromEEPROM(200);
  //Serial.println(readStringFromEEPROM(200));
  if (ReceivedText == activationText || smokeSensorValue > SmokeThresholod || temperatureSensorValue > temperatureThreshold || ( switch_status == 0 && trigger_status == 1 ) )
  {
    //Buzzer will be turned on 
    digitalWrite(buzzer_pin,HIGH);
    Serial.println("Buzzer: ON ");

    if((Msg_Status == 0 && trigger_status == 1) || (smokeSensorValue > SmokeThresholod && temperatureSensorValue > temperatureThreshold) ){
       
     registration();// This function assigns registered information to variables
     delay(500);
     String cat;
     cat = readStringFromEEPROM(200);// The text message you want to send to 5 people
     //retrievedStringroot.remove(0,1);
//     msg = "";
//
//     for(int i=2;i<cat.length(); i++){
//      //Serial.println(retrievedStringroot.charAt(i));
//      msg.concat(cat.charAt(i));
//      //Serial.println(msg);
//      }
     
     //Serial.println(msg);
     // sends sms
    //Serial.print("Message : ");Serial.println(msg);
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
       // Serial.println();
      }


      if (reset_status == 1){
        // if someone press reset switch , first sms will be sent to authority then the alarm will reduce
        switch_status = 1;
        Serial.print("Reset: ON ");
      sendSMS(Phoneno1, "RESET button has been pressed. Please check the issue.");
      sendSMS(Phoneno2, "RESET button has been pressed. Please check the issue.");
      sendSMS(Phoneno3, "RESET button has been pressed. Please check the issue.");
      sendSMS(Phoneno4, "RESET button has been pressed. Please check the issue.");
      sendSMS(Phoneno5, "RESET button has been pressed. Please check the issue.");
        }

  }

  else if (trigger_status == 1 && switch_status == 1) {
    errorAlarm(); // a reduced version of allarm
    //updateSerial();
    }

    else if (trigger_status == 0 || (smokeSensorValue < SmokeThresholod || temperatureSensorValue < temperatureThreshold) ){
      Msg_Status = 0;
      switch_status = 0;
      digitalWrite(buzzer_pin,LOW);
      //updateSerial();
      }
    else{
      digitalWrite(buzzer_pin,LOW);
      switch_status = 0;
      //updateSerial();
      
      }
  
}


void sendSMS(String number, String msg){
  //digitalWrite(buzzer_pin,LOW);
  
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




void readSeonsorValues(){
  //debugSensors();
  smokeSensorValue = analogRead(smokeSensor_Pin) ;
  temperatureSensorValue = analogRead(temperatureSensor_pin) ;
  reset_status = digitalRead(reset_pin) ;
  trigger_status = digitalRead(trigger_pin) ;
  
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
    delay(100);  
    //Serial.print("input : ");Serial.print(inputString);Serial.println("   end");
  }
  
 if (inputString.indexOf("CMT:")>=0){
  
  Serial.println(inputString);
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

void errorAlarm(){
  errorCounter++;
  
  Serial.print("ITS an error!");
  if (errorCounter>30 && errorCounter <45){
    digitalWrite(buzzer_pin,HIGH);
    }else if(errorCounter >45){
      errorCounter =0;
      }else{
        digitalWrite(buzzer_pin,LOW);
        }
  }


void debugSensors(){
  Serial.print("Smoke Sensor: ");
  Serial.print(smokeSensorValue);
  Serial.print("  Temperature Sensor: ");
  Serial.print(temperatureSensorValue);
  Serial.print("  Reset Switch: ");
  Serial.print(reset_status);
  Serial.print("  Fire Switch: ");
  Serial.println(trigger_status);    
  
  }
