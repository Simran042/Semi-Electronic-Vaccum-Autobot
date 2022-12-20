// defining the pins
/*A0 Anode
A1 red
A2 blue
A3 green*/
const int trigPin1 = 3;//left
const int echoPin1 = 5;
const int trigPin2 = 6;//mid
const int echoPin2 = 9;
const int trigPin3 = 10;//Right
const int echoPin3 = 12;
const int in1 = 13;
const int in2 = 8;
const int in3 = 4;
const int in4 = 7;
const int mindis = 20;
const int speed1 = 11;

int irpin =2;
// defining variables
long duration1;
long duration2;
long duration3;
int distanceleft;
int distancefront;
int distanceright;
int a=0;
void setup() {

  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(trigPin3, OUTPUT);// Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(irpin, INPUT);
  pinMode(in4, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(speed1, OUTPUT);
  Serial.begin(9600);

  analogWrite(speed1,80);

}

int distance(int trig,int echo)
{
      int distance;
      long duration;
      digitalWrite(trig, LOW);
      delayMicroseconds(2);
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);
      duration = pulseIn(echo, HIGH);
      distance = duration * 0.034 / 2;

      return distance;
}

void green()
{
  digitalWrite(A3,LOW);
  digitalWrite(A2,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A0,HIGH);
}

void blue()
{
  digitalWrite(A3,HIGH);
  digitalWrite(A2,LOW);
  digitalWrite(A1,HIGH);
  digitalWrite(A0,HIGH);
}

void red()
{
  digitalWrite(A3,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A1,LOW);
  digitalWrite(A0,HIGH);
}

void blink_g()
{
  green();
  delay(70);
  off();
  // delay(70);
  // green();
  // delay(70);
  // off();
  // delay(400);
  
}

void blink_r()
{
  red();
  delay(70);
  off();
  // delay(70);
  // red();
  // delay(70);
  // off();
  // delay(400);
  
}

void blink_b()
{
  blue();
  delay(70);
  off();
  // delay(70);
  // blue();
  // delay(70);
  // off();
  // delay(400);
  
}


void stop(void)
{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
}

void gofront(void)
{
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    blink_g();
}

void goleft(void)
{
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    blink_b();
}

void goright(void)
{
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    blink_b();
}

void goback(void)
{
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    blink_r();

}

void off()
{
   digitalWrite(A3,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A0,HIGH);
}


void loop() {

distanceleft = distance(trigPin1,echoPin1);
distancefront = distance(trigPin2,echoPin2);
distanceright = distance(trigPin3,echoPin3);

Serial.print("Distance1: ");
Serial.println(distanceleft);

Serial.print("Distance2: ");
Serial.println(distancefront);

Serial.print("Distance3: ");
Serial.println(distanceright);



  int s = digitalRead(irpin);



  if(s==LOW)//floor is there
  {
    if(distancefront>=mindis)
    {
        if((distanceleft<5))
        goright();
        else if((distanceright<5))
        goleft();
        else 
        gofront();

    }
    else
    {
        if((distanceleft<mindis)&&(distanceright>=mindis))
            goright();

        else if((distanceleft>=mindis)&&(distanceright<mindis))
            goleft();

        else if((distanceleft>=mindis)&&(distanceright>=mindis))
            {
              if(distanceright>distanceleft)
                goright();
              else 
                goleft();
            }
        else if(((distanceleft<mindis)&&(distanceright<mindis)))
        {   
            goback();
            delay(500);
        }
    }
  }
  else//floor is not there
  {
    goback();
    delay(1000);
    goright();
    delay(400);

  }

delay(10);
}