#include <Wire.h>

#define ARDUINO_ADDRESS 8
const int leds[]={2,3,4,5,6};


void setup() 
{
  Wire.begin(ARDUINO_ADDRESS); // starting the communicaiton for slave

  Wire.onReceive(receiveEvent); // the data come from wire is read with receiveEvent function
  Wire.onRequest(sendEvent); // specifying the function that will run on the slave device when the Master device requests data from the Slave device.
 
  Serial.begin(9600);
  for(int i=0; i<5; i++)
  {
    pinMode(leds[i], OUTPUT);
  }
  
}

void loop() 
{
  
}

// read data from Raspberry Pi Pico
void receiveEvent(int numBytes)
{
  while (Wire.available()) // if there is incoming data
  {
    char receivedChar = Wire.read(); // receive data as a char
    //Serial.print("Received data: ");
    //Serial.println(receivedChar); 
    if (receivedChar == 'K') // when arduino receive K character, start knightrider function
    {
      knightrider();
    }

  }
}

// send data to Raspberry Pi Pico
void sendEvent() 
{
  Wire.write( "Pi!"); // send data to Raspberry Pi Pico
}

void knightrider()
{
    for(int i=0; i<5; i++)
    { /* turns all LEDs on and off sequentially for 5 seconds */
      Serial.println("forward"); 
      digitalWrite(leds[i],HIGH);      
      delay(5000);                           
      digitalWrite(leds[i],LOW);          
    }
 
    for(int j=4;j>-1; j--)
    { /* turns the LEDs on and off for 5 seconds in the reverse direction. */
      Serial.println("reverse"); 
      digitalWrite(leds[j],HIGH);     
      delay(5000);
      digitalWrite(leds[j], LOW);
    }
}
