
#include <ArduinoQueue>

// Pinos do Display
const int rs = 8;
const int en = 9;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;
const int Botao = 2;

struct obstaculo {
  int x;
  int y;
};
ArduinoQueue<obstaculo> obstaculos(16);

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

enum estado_t { inicio, preparacao, corrida };
estado_t estado = preparacao;

// dino
byte dinoChar[8] = {
  0b00110,
  0b00111,
  0b01110,
  0b01111,
  0b01111,
  0b11110,
  0b01110,
  0b01010
};

byte obstaculoChar[8] = {
  0b10101,
  0b10101,
  0b11111,
  0b01110,
  0b01110,
  0b00100,
  0b00100,
  0b00100
};

void setup() {
  lcd.begin(16, 2); // LCD - 16 colunas por 2 linhas
  pinMode(Botao, INPUT);
  lcd.createChar(0, dinoChar);
  lcd.createChar(1, obstaculoChar);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  if (digitalRead(Botao) == HIGH) {
    if (estado == inicio) {
      estado = preparacao;
    } else if (estado == preparacao){
      estado = corrida;
    }
    delay(200); 
  }

  if (estado == inicio) {
    lcd.clear();
    lcd.write((uint8_t)0);
    lcd.print("  Dino Race   ");
    lcd.write((uint8_t)0);
    lcd.setCursor(3, 1);
    lcd.print("CC - UFFS");
    delay(1000);
  } else if (estado == preparacao) {
    lcd.clear();
    for(int i = 0; i < 6; i++){
      obstaculo obs = {random(0, 16), random(0,2)};
      if(obs.y == 1) obs.y = 2;
      obstaculos.en
      lcd.setCursor(obs.x, obs.y);
      lcd.write(byte(1));
      }
      delay(1000);
  } else if (estado == corrida) {
      lcd.clear();
      for(int i = 0; i < 6; i++){
        obs.y--;
        lcd.setCursor(obs.x, obs.y);
        lcd.write(byte(1));
      }
      delay(500);
  }
}