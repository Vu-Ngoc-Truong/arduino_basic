#include <EEPROM.h>

byte Arr[10] = {1,2,3,4,5,6,7,8,9,10};
byte dataArr[10];

void setup() 
{
  Serial.begin(9600);
  byte temp = EEPROM.read(0);
  if ( temp ==0 )
  {
    EEPROM.put(0,Arr );
    Serial.println("Da ghi vao EEPROM!!!");
  }
  

}

void loop() {
  EEPROM.get(0,dataArr);
  for ( int i =0 ; i<10; i++)
  {
    Serial.print(dataArr[i]);
    Serial.print("\t");
  }
  Serial.println();
  Serial.println("Doc xong!!!");
  delay(1500);

}
