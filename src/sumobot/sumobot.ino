//m1 right motor

#define ultrasonic_t 10
#define ultrasonic_e 9
#define pin_m1d1 5
#define pin_m1d2 4
#define pin_m1pwm 3
#define pin_m2d1 8
#define pin_m2d2 7
#define pin_m2pwm 6
#define pin_IRleft 11
#define pin_IRright 12
#define pin_button 2

bool IRL = false;
bool IRR = false;

bool m1d1 = false;
bool m1d2 = false;
int m1pwm = 0;
bool m2d1 = false;
bool m2d2 = false;
int m2pwm = 0;

bool button = 0;
long duration = 0;
float distance = 10000;
int state = 0;
int backtime = 0;

unsigned long timer = 0;

void setup() {

pinMode(ultrasonic_t,OUTPUT);
pinMode(ultrasonic_e,INPUT);
pinMode(pin_m1d1,OUTPUT);
pinMode(pin_m1d2,OUTPUT);
pinMode(pin_m1pwm,OUTPUT);
pinMode(pin_m2d1,OUTPUT);
pinMode(pin_m2d2,OUTPUT);
pinMode(pin_m2pwm,OUTPUT);
pinMode(pin_IRleft,INPUT);
pinMode(pin_IRright,INPUT);
pinMode(pin_button,INPUT);
Serial.begin(9600);

waitforbutton();

}

void loop() {

readsens();
detectenemy();
statemachine();
inbattlefield();
actuation();

}

void waitforbutton(){

while(true){
button=digitalRead(pin_button);
if(button==true){
break;
}
}

digitalWrite(13,HIGH);
delay(4500);
digitalWrite(13,LOW);

}

void readsens(){

backtime=0;

if(millis()-timer>50){

IRL = digitalRead(pin_IRleft);
IRR = digitalRead(pin_IRright);
//Serial.print(IRL);
//Serial.print("   ");
//Serial.println(IRR);

digitalWrite(ultrasonic_t, LOW);
delayMicroseconds(2);
digitalWrite(ultrasonic_t, HIGH);
delayMicroseconds(10);
digitalWrite(ultrasonic_t, LOW);
duration = pulseIn(ultrasonic_e, HIGH);
distance = 1.0*duration / 29 / 2;
button = digitalRead(pin_button);
//Serial.println(distance);

if(button==HIGH){
delay(10000);
}

timer=millis();

}
}

void statemachine(){

  switch(state){
    case 0:{
    searching();
    break;
    }
    case 1:{
    tackle();
    break;
    }
    default:{
    break;
    }

  }


}

void actuation(){

digitalWrite(pin_m1d1,m1d1);
digitalWrite(pin_m1d2,m1d2);
analogWrite(pin_m1pwm,m1pwm);
digitalWrite(pin_m2d1,m2d1);
digitalWrite(pin_m2d2,m2d2);
analogWrite(pin_m2pwm,m2pwm);
delay(backtime);

}

void inbattlefield(){

if(IRL==true){

m1d1=0;
m1d2=1;
m1pwm=255;
m2d1=0;
m2d2=0;
m2pwm=0;
backtime=1000;

}

else if(IRR==true){

m1d1=0;
m1d2=0;
m1pwm=0;
m2d1=0;
m2d2=1;
m2pwm=255;
backtime=1000;

}

else if(IRR==true and IRL==true){

m1d1=1;
m1d2=0;
m1pwm=255;
m2d1=1;
m2d2=0;
m2pwm=255;
backtime=2000;

}

}

void detectenemy(){

if(distance<30){

state=1;

}
else{

state=0;

}

}

void tackle(){

m1d1=1;
m1d2=0;
m1pwm=200;
m2d1=1;
m2d2=0;
m2pwm=200;

}

void searching(){

m1d1=0;
m1d2=1;
m1pwm=90;
m2d1=1;
m2d2=0;
m2pwm=90;

}