/*
 * Projet d'Afficheur Lumineux d'information.
 * Auteur : Dominique PAUL
 * Date : juin 2018
 * Modif texte du : mai 2022
 * + Ajout de la gestion de mémoire (reboot si mem trop basse, évite le blocage de l'afficheur).
 * 
 * Necessite les bibliothéques :
 * MD_Parola v3.6.1
 * MD_MAX72xx v3.3.0
 * SPI 
 * wdt ( WatchDog, intégré à Arduino).
 */

 
/* Chargement des librairies, Gestion affichage matrice */
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
/* Inclu la librairie SPI si besoin */
//#if USE_LIBRARY_SPI
//#include <SPI.h>
//#endif
/* Chargement du Watchdog */
#include <avr/wdt.h>

/* Parametrage matrice MAX7219 ( Pins Arduino ou sont connectées les broches de la matrice ) */
#define MAX_DEVICES 16  // Nombre de matrice MAX7219
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    9     // Pin de commande

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define MAX_DEVICES 4   // ( nombre de matrice )
//#define CLK_PIN   14    // D5
//#define DATA_PIN  13    // D7
//#define CS_PIN    15    // D8
 
// initialisation de la matrice
// HARDWARE SPI
//MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// SOFTWARE SPI
//MD_Parola P = MD_Parola(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

/* Déclaration des variables */
int cpt=0;
/* Déclaration des constantes */
const uint16_t vitesse=50;
const int temps_pause=2000;

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
  Serial.begin(115200);
  /* initialisation de l'affichage */
  P.begin();
  P.setSpeed(vitesse);
}
 
void loop() {
  /* Affichage des textes */
  if (P.displayAnimate())
  {
    /* Boucle de travail */
    if (cpt > 8) { 
      P.begin();
      P.displayReset();
      cpt=0; 
      Serial.println("Réinit case = " + String(cpt));
      
      /* A chaque boucle, on s'assure qu'il reste suffisament de mémoire */
      Serial.println("memoire libre = " + String(freeRam()));
      if (freeRam() < 500) { 
        /* Mémoire trop juste, on reboot le système via WatchDog */
        Serial.println("Trop peu de memoire : Reboot du sytem");
        reset_software();
      }
    }
   
    /* Affichage l'un après l'autre */
      switch(cpt)
      {
        case 0 :
          {
            Serial.println("Case = " + String(cpt));
            P.displayText("Bienvenue dans notre camion Gourmand", PA_LEFT, P.getSpeed(),0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
            ++cpt;
            break;
          }
        case 1 :
          {
            Serial.println("Case = " + String(cpt));
            P.displayText("Cr\x0EA\pes Maison \x0E2 emporter", PA_CENTER, P.getSpeed(), temps_pause, PA_SCROLL_LEFT, PA_SCROLL_DOWN);
            ++cpt;
            break;
          }
         case 2 :
          {
            Serial.println("Case = " + String(cpt));
            P.displayText("Cr\x0EA\pes natures", PA_CENTER, P.getSpeed(), temps_pause, PA_SCROLL_UP, PA_SCROLL_DOWN);
            ++cpt;
            break;
          }
        case 3 :
          {
            Serial.println("Case = " + String(cpt));
            P.displayText("Cr\x0EA\pes Nutella", PA_CENTER, P.getSpeed(), temps_pause, PA_SCROLL_UP, PA_SCROLL_DOWN);
            ++cpt;
            break;
          }
        case 4 :
          {
            Serial.println("Case = " + String(cpt));
            P.displayText("Boissons Chaudes ...", PA_CENTER, P.getSpeed(), temps_pause, PA_SCROLL_LEFT, PA_SCROLL_DOWN);
            ++cpt;
            break;
          }
        case 5 :
          {
            Serial.println("Case = " + String(cpt));
            P.displayText("Boissons Fra\x0EE\ches", PA_CENTER, P.getSpeed(), temps_pause, PA_SCROLL_UP, PA_SCROLL_DOWN);
            ++cpt;
            break;
          }
        case 6 :
          {
            /* P.displayText("Vente de Bonbons", PA_CENTER, P.getSpeed(), temps_pause, PA_SPRITE, PA_SPRITE);
            P.setSpriteData(rocket, W_ROCKET, F_ROCKET, rocket, W_ROCKET, F_ROCKET); */
            Serial.println("Case = " + String(cpt));
            P.displayText("Self service Confiserie", PA_CENTER, P.getSpeed(), temps_pause, PA_SCROLL_LEFT, PA_SCROLL_DOWN);
            ++cpt;
            break;
          }
        case 7 :
          {
            /* P.displayText("Vente de Bonbons", PA_CENTER, P.getSpeed(), temps_pause, PA_SPRITE, PA_SPRITE);
            P.setSpriteData(rocket, W_ROCKET, F_ROCKET, rocket, W_ROCKET, F_ROCKET); */
            Serial.println("Case = " + String(cpt));
            P.displayText("Bonbons sans sucre", PA_CENTER, P.getSpeed(), temps_pause, PA_SCROLL_UP, PA_SCROLL_DOWN);
            ++cpt;
            break;
          }
        case 8 :
          {
            Serial.println("Case = " + String(cpt));
            P.displayText("Guimauve au chocolat", PA_CENTER, P.getSpeed(), temps_pause, PA_SCROLL_UP, PA_SCROLL_DOWN);
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

/* Retourne la mémoire libre */
int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
