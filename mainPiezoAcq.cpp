#include "Arduino.h"

const int piezoPin = A0;         // Pin d'entrée pour le capteur piézoélectrique
const int ledPins[] = {3, 4, 5}; // Pins de sortie pour les 3 LEDs
//Explication : ledPins[0] = 3 --> greenLed
//Explication : ledPins[1] = 4 --> yellowLed
//Explication : ledPins[2] = 5 --> redLed

const int motorPin = 6;          // Pin de sortie pour le moteur de vibration

//Définition de la valeur du coup faible
const int coupFaible = 50;

//Définition des valeurs des coups forts associées à trois intensités différentes
const int coupFort1 = 150;
const int coupFort2 = 280;

//Déclaration de 3 variables booléenes permettant d'identifier l'intensité spécifique détectée
boolean intensite1= false;
boolean intensite2= false;
boolean intensite3= false;

void activateComponents();
void deactivateComponents();

void setup()
{
    Serial.begin(9600);

    // Initialiser les LEDs et le moteur en sortie
    for (int i = 0; i < 3; i++)
    {
        pinMode(ledPins[i], OUTPUT);
    }
    pinMode(motorPin, OUTPUT);
}

void loop()
{
    int intensiteCoup = analogRead(piezoPin);
    if (verifierCoup(intensiteCoup) == true){
        activateComponents();
        delay(1500); // Délai pour stabiliser la lecture
    }
    else
    {
        deactivateComponents();
    }
}

boolean verifierCoup(int intensite)
{
    if (intensite > coupFaible && intensite < coupFort1)
    {
        Serial.print("Coup VALIDE, d'intensite ");
        Serial.println(intensite);
        intensite1= true;

        intensite2= false;
        intensite3= false;

        return true;
    }
    else if (intensite > coupFort1 && intensite < coupFort2)
    {
        Serial.print("Coup VALIDE, d'intensite ");
        Serial.println(intensite);
        intensite2= true;

        intensite1= false;
        intensite3= false;

        return true;
    }
    else if (intensite > coupFort2)
    {
        Serial.print("Coup VALIDE, d'intensite ");
        Serial.println(intensite);
        intensite3= true;

        intensite1= false;
        intensite2= false;

        return true;
    }
    else
    {
        Serial.print("Coup INVALIDE, d'intensite ");
        Serial.println(intensite);
        return false;
    }
}

void activateComponents()
{
    if(intensite1 == true){
      // Allumer la LED verte
      digitalWrite(ledPins[0], HIGH);
      // Activer le moteur de vibration
      digitalWrite(motorPin, HIGH);

      //S'assurer que les autres composants ne se déclenchent pas
      digitalWrite(ledPins[1], LOW);
      digitalWrite(ledPins[2], LOW);

    }
    else if(intensite2 == true){
      // Allumer la LED verte
      digitalWrite(ledPins[1], HIGH);
      // Activer le moteur de vibration
      digitalWrite(motorPin, HIGH);
      
      //S'assurer que les autres composants ne se déclenchent pas
      digitalWrite(ledPins[0], LOW);
      digitalWrite(ledPins[2], LOW);
    }
    else if(intensite3 == true){
      // Allumer la LED verte
      digitalWrite(ledPins[2], HIGH);
      // Activer le moteur de vibration
      digitalWrite(motorPin, HIGH);

      //S'assurer que les autres composants ne se déclenchent pas      
      digitalWrite(ledPins[0], LOW);
      digitalWrite(ledPins[1], LOW);
    }
}

void deactivateComponents()
{
    // Éteindre les LEDs
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(ledPins[i], LOW);
    }
    // Désactiver le moteur de vibration
    digitalWrite(motorPin, LOW);

    delay(500); 

}