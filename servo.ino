/*
  Serial Call and Response
 Language: Wiring/Arduino
 
 This program sends an ASCII A (byte of value 65) on startup
 and repeats that until it gets some data in.
 Then it waits for a byte in the serial port, and 
 sends three sensor values whenever it gets a byte in.
 
 Thanks to Greg Shakar and Scott Fitzgerald for the improvements
 
   The circuit:
 * potentiometers attached to analog inputs 0 and 1 
 * pushbutton attached to digital I/O 2
 
 Created 26 Sept. 2005
 by Tom Igoe
 modified 24 April 2012
 by Tom Igoe and Scott Fitzgerald

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialCallResponse

 */
 #include <Servo.h>
 
 

void setup()
{
  Serial.begin(9600);
}

int command = -1;
int pin = 0;
int value = 0;
int cmd_step = 0;

void loop()
{
  
  // if we get a valid byte, read analog ins:
  while (Serial.available() > 0) {
          
    int inByte = Serial.read();
    if (inByte == ',') {
      cmd_step ++;
      break;
    }
    
    
    // First, get command
    if (cmd_step == 0) {
      switch(inByte) {
       case 'W':
         command = 1; 
         break;
       case 'R':
         command = 2; 
         break;
       case 'A':
         command = 3; 
         break;
        default:
         command = -1;
      }
    } else { // If command is filled, wait for pin and values
      if (cmd_step == 1) {

        if (pin > 0) {
          pin = pin * 10;
        }
        pin += int(inByte) - 48;
        
      } else if (cmd_step == 2) {
        Serial.println("Valor:" + String(inByte - '0'));
        value = inByte - '0';
      }
    }
    // get incoming byte:
    
    if (inByte == 'E') { // Execute
      switch(command) {
        case 1:
          writePin(pin, value);
          
      }
      // Clear data
      command = pin = value = 0;
      cmd_step = 0;
    }
    
  }
  delay(100);
}

int writePin(int pin, int valor) {
  Serial.println("Valor pin: " + String(pin) + " = " + String(valor));
  digitalWrite(pin, valor);
}


