#include<Servo.h>
Servo ser1;
const int s0 = 8;  
const int s1 = 9;  
const int s2 = 12;  
const int s3 = 11;  
const int out = 10;   

// Variables  
int red = 0;  
int green = 0;  
int blue = 0;  
int g=80;
void setup()   
{  
  Serial.begin(115200); 
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);   
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH);  
  ser1.attach(13,650,2400);  

 ser1.write(70);
  delay(1000);
  ser1.write(105);
  delay(2000);
  ser1.write(70);
  delay(1000);
}  
    
void loop() 
{  
  color(); 
  
  Serial.print("   red: ");
  Serial.print(red);
  Serial.print("   green: ");
  Serial.print(green);
  Serial.print("   blue: ");
  Serial.print(blue);
   if (red>=170 && green>=200)
  {  
     Serial.print("  BLACK  ");
    up();   
  }else if (red<=120 && green <=120)   
  {  
     Serial.print("  WHITE  "); 
     down();
  }else if (red>=65 && red <=130 && green>=200 )  
  {  
     Serial.print("  MAGENTA  ");    
  }else{
  Serial.print("  ----  ");  
  }
  Serial.println(g);
  delay(300);      
 }  
    
void color()  
{    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);    
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);    
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);    
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}
void up(){
  // put your main code here, to run repeatedly:
  ser1.write(g);
  if(g<105)  g=g+1;  
}
void down(){
  // put your main code here, to run repeatedly:
  ser1.write(g); 
  if(g>69)  g=g-1;     
}
