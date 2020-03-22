/*
 * Jardin Autonome - Projet STI2D
 * Algorithme du code : 
 * - Se connecter en Serial au Raspberry Pi
 * [Toutes les 30 minutes] :
 *  - Récupérer les données des capteurs
 *  - Les envoyer au Raspberry Pi
 *  - Debug sur écran LCD si possible
 */

// INCLUDES
#include <LiquidCrystal.h>

// GLOBALS
// Capteurs, à modifier.
int CAPTEUR_CUVE1 = 0;
int CAPTEUR_CUVE2 = 0;
int CAPTEUR_CUVE3 = 0;
int CAPTEUR_CUVE4 = 0;
int CAPTEUR_HUMIDITE = 0;

char program_version[] = "0.0.0";
LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);

// CUSTOM FUNCTIONS
void blink_led(int blink_count) {
  for (int i=0; i<= blink_count; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100); 
  }
}

// SETUP
void setup() {
  bool got_ip_address = false;

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  blink_led(3);
  
  lcd.begin(16, 2);
  Serial.begin(9600);

  lcd.setCursor(0,0);
  lcd.write("Projet-Arduino");
  lcd.setCursor(0,1);
  lcd.write("Version ");
  lcd.write(program_version);
  delay(5000);
  lcd.clear();

  while (!Serial.available()) {
    lcd.setCursor(0,0);
    lcd.print("Projet");
    
    lcd.setCursor(0,1);
    lcd.print("Jardin Autonome");
    
    delay(3000);
    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print("Connexion au");
    
    lcd.setCursor(0,1);
    lcd.print("Raspberry Pi...");
    
    delay(3000);
    lcd.clear();
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connexion");
  lcd.setCursor(0,1);
  lcd.write("etablie!");
  blink_led(10);
  delay(3000);
  lcd.clear();

  // On check si on a des données à recevoir
  while (got_ip_address == false) {
    if (Serial.available() > 0) {
      // Si oui...
      char incomingChar = Serial.read();
  
      // On regarde si c'est une adresse IP (format *I*192.168.X.X*P*)
      if (incomingChar == 'I') {
        // Si c'est une adresse IP...
        lcd.setCursor(0,0);
        lcd.print("Adresse IP :");
        lcd.setCursor(0,1);
  
        // On affiche sur l'écran jusqu'à ce qu'on rencontre la lettre 'P'
        while (true) {
          while (!Serial.available()) {}
          
          incomingChar = Serial.read();
          
          if (incomingChar == 'P') {
            got_ip_address = true;
            break;  
          
          } else {
            lcd.write(incomingChar);
          }
        }
      }
    }
  }
}

void loop() {
  /*
  int cuve1 = digitalRead(CAPTEUR_CUVE1);
  int cuve2 = digitalRead(CAPTEUR_CUVE2);
  int cuve3 = digitalRead(CAPTEUR_CUVE3);
  int cuve4 = digitalRead(CAPTEUR_CUVE4);
  int humidite = digitalRead(CAPTEUR_HUMIDITE);
  */

  // Vu qu'on a pas les capteurs, on génère des nombres aléatoires
  randomSeed(analogRead(0));

  int cuve1 = random(0, 2);
  int cuve2 = random(0, 2);
  int cuve3 = random(0, 2);
  int cuve4 = random(0, 2);
  float humidite = (random(0, 101)) / 100.00f;
  
  Serial.print("CUVE1=");
  Serial.print(cuve1);
  Serial.print(",");
  
  Serial.print("CUVE2=");
  Serial.print(cuve2);
  Serial.print(",");
  
  Serial.print("CUVE3=");
  Serial.print(cuve3);
  Serial.print(",");
  
  Serial.print("CUVE4=");
  Serial.print(cuve4);  
  Serial.print(",");
  
  Serial.print("HUMIDITE=");
  Serial.print(humidite);
  Serial.println(";"); // à changer en print

  // Pause de 1 minute
  delay(60*1000);
  }
