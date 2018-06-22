/*
 * Projet d'Afficheur Lumineux d'information.
 * Auteur : Dominique PAUL
 * Date : juin 2018
 */

 
/* Chargement des librairies, Gestion affichage matrice */
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
/* Chargement du Watchdog */
#include <avr/wdt.h>
 
/* Parametrage matrice MAX7219 ( Pins Arduino ou sont connectées les broches de la matrice ) */
#define MAX_DEVICES 16  // Nombre de matrice MAX7219
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    9     // Pin de commande
 
// initialisation de la matrice
// HARDWARE SPI
//MD_Parola P = MD_Parola(CS_PIN, MAX_DEVICES);
// SOFTWARE SPI
MD_Parola P = MD_Parola(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

/* Déclaration des variables */
int cpt=0;
uint16_t vitesse=50;
int temps_pause=2000;

// Sprite Definition
/* const uint8_t F_ROCKET = 2;
const uint8_t W_ROCKET = 11;
static const uint8_t PROGMEM rocket[F_ROCKET * W_ROCKET] =  // rocket
{
  0x18, 0x24, 0x42, 0x81, 0x99, 0x18, 0x99, 0x18, 0xa5, 0x5a, 0x81,
  0x18, 0x24, 0x42, 0x81, 0x18, 0x99, 0x18, 0x99, 0x24, 0x42, 0x99,
};
*/

void setup() {
  /* Initialise le port série */
  Serial.begin(57600);
  /* initialisation de l'affichage */
  P.begin();
  P.setSpeed(vitesse);
}
 
void loop() {
  
  
  /* Affichage des textes */
  if (P.displayAnimate())
  {
    /* Boucle de travail */
    if (cpt > 4) { 
      P.begin();
      P.displayReset();
      cpt=0; 
      Serial.println("Réinit case = " + String(cpt));
    }
  
    /* Affichage l'un après l'autre */
      switch(cpt)
      {
        case 0 :
          {
            Serial.println("Case = 0");
            P.displayText("Bienvenue dans notre camion Gourmand", PA_LEFT, P.getSpeed(),0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
            ++cpt;
            break;
          }
        case 1 :
          {
            /* P.displayText("Vente de Bonbons", PA_CENTER, P.getSpeed(), temps_pause, PA_SPRITE, PA_SPRITE);
            P.setSpriteData(rocket, W_ROCKET, F_ROCKET, rocket, W_ROCKET, F_ROCKET); */
            Serial.println("Case = 1");
            P.displayText("Vente de Bonbons", PA_CENTER, P.getSpeed(), temps_pause, PA_SCROLL_LEFT, PA_SCROLL_DOWN);
            ++cpt;
            break;
          }
        case 2 :
          {
            Serial.println("Case = 2");
            P.displayText("Avec ou Sans Sucre", PA_CENTER, P.getSpeed(), temps_pause, PA_SCROLL_UP, PA_SCROLL_DOWN);
            ++cpt;
            break;
          }
        case 3 :
          {
            Serial.println("Case = 3");
            //P.displayText("Boissons Fraiches", PA_CENTER, P.getSpeed(), temps_pause, PA_SCROLL_LEFT, PA_SCAN_VERT);
            P.displayText("Boissons Fraiches", PA_CENTER, P.getSpeed(), temps_pause, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
            ++cpt;
            break;
          }
        case 4 :
          {
            Serial.println("Case = 4");
            //P.displayText("et Cr\x088pes Maison", PA_CENTER, P.getSpeed(), temps_pause, PA_SCAN_VERT, PA_SCROLL_LEFT);
            P.displayText("et Cr\x088pes Maison", PA_CENTER, P.getSpeed(), temps_pause, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
            ++cpt;
            break;
          }
      Serial.println("Valeur de Case = " + cpt);
      }
  }
}

/* Permet d'effectuer un Hardreset via Watchdog  */
void reset_software(void) {
  wdt_enable(WDTO_15MS);
  for(;;);
}
