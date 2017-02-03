//AUTOBOT
//un véhicule autonome basé sur NodeMCU + shield  avec sonar et 4 moteurs
//
//On définit l'angle de capture de distance
int DistLeft;
int DistMid;
int DistRight;

//on  insère la librairie newping
#include <NewPing.h>

//on définit les pins ECHO & TRIGGER du sonar
NewPing sonar(D6, D7, 100);

// on définit des action en attribuant des valeurs aux moteurs sur les PINS suivant
//moteur gauche D5 - sens de rotation sur D0 en HIGH ou LOW
//moteur gauche D4 - sens de rotation sur D2 en HIGH ou LOW
//PINS 4 & 5 en analogWrite de 0 à 1023
//PINS 0 & 2 en digitalWrite  à 0 ou 1
void stop(void)
{
  analogWrite(5, 0);
  analogWrite(4, 0);
}
void forward(void)
{
  analogWrite(5, 1023);
  analogWrite(4, 1023);
  digitalWrite(0, HIGH);
  digitalWrite(2, LOW);
}
void backward(void)
{
  analogWrite(5, 1023);
  analogWrite(4, 1023);
  digitalWrite(0, LOW);
  digitalWrite(2, HIGH);
}
void left(void)
{
  analogWrite(5, 1023);
  analogWrite(4, 1023);
  digitalWrite(0, LOW);
  digitalWrite(2, LOW);
}
void right(void)
{
  analogWrite(5, 1023);
  analogWrite(4, 1023);
  digitalWrite(0, HIGH);
  digitalWrite(2, HIGH);
}

//on définit les pins 0/2/4/5 pour les moteurs
void setup()
{
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
}

//on boucle sur les actions à faire
void loop()
{
  while (sonar.ping_cm() > 30) {
    forward();
    delay(200);
  }

  if (sonar.ping_cm() <= 30) {
    stop();
    delay(10);
    DistMid = sonar.ping_cm();
    left();
    delay(800);
    DistLeft = sonar.ping_cm();
  }

  if  (DistLeft > DistMid) {
    forward();
    delay(200);
  }
  else if (DistLeft <= DistMid) {
    right();
    delay(1200);
    DistRight = sonar.ping_cm();
    if (DistRight > DistMid) {
      forward();
      delay(200);
    }
  }
}
