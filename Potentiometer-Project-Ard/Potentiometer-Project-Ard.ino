int motor1_left=4;

int motor_1_left=5;

int motor2_right=6;

int motor_2_right=7;

int left_analog=3;

int right_analog=9;


void setup() 
{  
  
pinMode(motor1_left,OUTPUT);
  
pinMode(motor_1_left,OUTPUT);

pinMode(left_analog,OUTPUT);

 pinMode(right_analog,OUTPUT);

 pinMode(motor2_right,OUTPUT); 
 
 pinMode(motor_2_right,OUTPUT);

 Serial.begin(9600);

}


void forward()
{ 
analogWrite(right_analog,250);

analogWrite(left_analog,250);

 digitalWrite(motor1_left,LOW);
 
digitalWrite(motor2_right,LOW);
 
digitalWrite(motor_2_right,HIGH);

 digitalWrite(motor_1_left,HIGH); 
 
}

void backward()
{ 
analogWrite(right_analog,250);

analogWrite(left_analog,250);

 digitalWrite(motor1_left,HIGH);

 digitalWrite(motor2_right,HIGH);
 
digitalWrite(motor_2_right,LOW);

 digitalWrite(motor_1_left,LOW);  

}


void stop1()
{ 
analogWrite(9,0);

analogWrite(3,0);

 digitalWrite(motor1_left,LOW);
 
digitalWrite(motor2_right,LOW);
 
digitalWrite(motor_2_right,LOW);
 
digitalWrite(motor_1_left,LOW); 
 
}

void right()
{ 
analogWrite(9,150);

analogWrite(3,150);
 
digitalWrite(motor1_left,LOW);

 digitalWrite(motor2_right,LOW);
 
digitalWrite(motor_2_right,LOW);
 
digitalWrite(motor_1_left,HIGH);  

}

void left()
{ 
analogWrite(9,190);

analogWrite(3,190);
 
digitalWrite(motor1_left,LOW);
 
digitalWrite(motor2_right,LOW);
 
digitalWrite(motor_2_right,HIGH);
 
digitalWrite(motor_1_left,LOW);  

}




long duration,distance;
char ch;

void loop() {
  
  
 if (Serial.available() > 0)
{
    char ch = Serial.read();  // Read the command
    Serial.println(ch); 
 if (ch=='a')
     
      {     
 
        
        forward();
       

      } 
 
 if (ch=='e')
   
      {
        backward();
      }
    
 if (ch=='c')
   
      { 
         stop1();
      }
  
 if (ch=='b')
 
     {
         left();
     } 
 
 
if (ch=='d')

     {
         right();
     }

}   


}