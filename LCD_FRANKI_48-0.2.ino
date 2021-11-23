
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27,20,4);  // LCD 20X4
LiquidCrystal_I2C lcd(0x27,16,2);  // LCD 16X2
#include <avr/io.h>
#include <avr/interrupt.h>


const int
VOL_PIN = A0,  // LECTURA DE BATERIA
VOLAC_PIN = A3, // LECTURA DE AC
pin = 13;

int buzzer = 9 ;// Pin 9 SONIDO
 
void setup()
{

  pinMode(buzzer, OUTPUT) ;
  pinMode(pin, OUTPUT);
  lcd.begin();                      // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("ENFOQUE SOLAR"); 

  digitalWrite (buzzer, HIGH) ;// send voice
  delay (200) ;// Delay 1ms
  digitalWrite (buzzer, LOW) ;// do not send voice
  delay (80) ;// delay ms
  delay (200) ;// Delay 1ms
  digitalWrite (buzzer, HIGH) ;// send voice
  delay (200) ;// Delay 1ms
  digitalWrite (buzzer, LOW) ;// do not send voice
  delay (80) ;// delay ms
  delay (200) ;// Delay 1ms
  digitalWrite (buzzer, HIGH) ;// send voice
  delay (200) ;// Delay 1ms
  digitalWrite (buzzer, LOW) ;// do not send voice
  delay (80) ;// delay ms
  delay (200) ;// Delay 1ms

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("VOLT- AMP- WATTS"); 
  
}

 
void loop()
{
 // dot(); dot(); dot(); 
 // dash(); dash(); dash();
 // temp_();

  voltaje_dc();


}
 
void dot()
{
  digitalWrite(pin, HIGH);
  delay(250);
  digitalWrite(pin, LOW);
  delay(250);
}
 
void dash()
{
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  delay(250);
}

void voltaje_dc()
{
  int value;
  float volt;
  value = analogRead( VOL_PIN );
  volt = value;
  static int contador_de_display; //variable display
  
  
  
  
  lcd.setCursor(0,1);
 // lcd.print("Vdc: ");               // prints the voltage value in the LCD display  
 // lcd.print(volt/11.518,1);
 // lcd.print(volt,1);

if (contador_de_display >= 1000) {        // actuzaliza cada 500 ciclos
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("VOLT- AMP-WATTS"); 
    lcd.setCursor(0, 1);
    lcd.print(volt, 1);
    contador_de_display = 0;
    }
    contador_de_display++;

  if (volt <= 457) indicador_alarma(5);                             // low batt @ 10.5V --> (2k7/12.7k x 10.5) / 5 x 1023 = 457


}

void temp_()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TEMP Most-Transf"); 

}



void indicador_alarma(int alarma) {
  int value;
  float volt;
  value = analogRead( VOL_PIN );
  volt = value;
  
  TCCR1A = 0;  // shutdown SPWM output
  TIMSK1 = 0;
  PORTB &= 0b11100001;

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("ADVERTENCIA!");
  lcd.setCursor(0, 1);
  if (alarma == 2) lcd.print(" UNDER VOLTAGE");
  if (alarma == 3) lcd.print("  OVER VOLTAGE");
  if (alarma == 4) lcd.print("OVER TEMPERATURE");
  if (alarma == 5) {lcd.print("BATERIA AL 0%"); delay(2000); lcd.setCursor(0, 1); lcd.print("RECARGE BATERIA"); delay(3000);  lcd.setCursor(0, 1); lcd.print("REINICIANDO....."); delay(4000); lcd.clear(); lcd.setCursor(0, 1); lcd.print(volt); delay(4000);}
}
