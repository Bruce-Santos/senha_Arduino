#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

//Identificação do LCD
LiquidCrystal_I2C lcd(0x27,20,4);

//identificação de botões e declarando suas saidas
#define btn_up 2
#define btn_esc 3
#define btn_enter 4
#define btn_down 5

//Declaracao de variaveis
String pass = "1234";
String tryPass = "0000";
int selnum = 0,
    actpos = 0;
bool senhainserida = 0;

void setup() {
  pinMode(btn_up, INPUT_PULLUP);
  pinMode(btn_esc, INPUT_PULLUP);
  pinMode(btn_enter, INPUT_PULLUP);
  pinMode(btn_down, INPUT_PULLUP);
  lcd.init();                 // Inicializando o LCD
  lcd.backlight();            // Ligando o BackLight do LCD
  
}

void loop() {
  if(!senhainserida){
    lcd.setCursor(0,0);
    lcd.print("insira a senha");
    lcd.setCursor(actpos,2);
    lcd.print(selnum);
    if (digitalRead(btn_up) == LOW and selnum>0){ selnum--; delay (200);}
    else if (digitalRead(btn_down) == LOW and selnum<9){ selnum++; delay (200);}
    if(digitalRead(btn_enter) == LOW && actpos<4){
      tryPass[actpos] =  char(selnum + '0'); 
      actpos++;
      delay (200);
    }
    else if(digitalRead(btn_esc) == LOW && actpos>0){
      lcd.setCursor(actpos,2);
      lcd.print(" ");
      actpos--;
      delay(200);
    }
    if(actpos>3 and tryPass==pass){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("senha correta");
      senhainserida = 1;

    }
    if(actpos>3 and tryPass!=pass){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("senha incorreta");
      senhainserida = 1;

    }
  }
  else{
    delay(3000);
    tryPass = "0000";
    actpos = 0;
    senhainserida = 0;
  }

}
