/*
Color Sensor      Arduino
-----------      --------
 VCC               5V
 GND               GND
 s0                8
 s1                9
 s2                12
 s3                11
 OUT               10
 OE                GND
*/
const int s0 = 8;  
const int s1 = 9;  
const int s2 = 12;  
const int s3 = 11;  
const int out = 10;   
// LED pins connected to Arduino
// Variables  
int data = 0;  

    
void setup()   
{  
  Serial.begin(9600); 
   pinMode(s0,OUTPUT);   
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT); 
  digitalWrite(s0, HIGH);  // 100% scaling
  digitalWrite(s1, HIGH);  
}  
    
void loop() 
{  
  digitalWrite(s2,LOW);        //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
   digitalWrite(s3,LOW);
   Serial.print("Red= "); 
   data=pulseIn(out,LOW);  //here we wait until "out" go LOW, we start measuring the duration      and stops when "out" is HIGH again
   Serial.print(data);//map(data,60,15,0,100));        
   Serial.print("\t");          
   delay(20);
                      
   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   Serial.print("Blue= ");
   data=pulseIn(out,LOW);  //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
   Serial.print(data);//map(data,80,11,0,100));          
   Serial.print("\t");          
   delay(20);

   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   Serial.print("Green= ");
   data=pulseIn(out,LOW);  //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
   Serial.print(data);//map(data,80,20,0,100));          
   Serial.print("\t");          
   delay(20);

   Serial.println();

   delay(200);

}
    

   
