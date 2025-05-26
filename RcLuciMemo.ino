#include <EEPROM.h>

int counter = 0;
int currentState = 0;
int previousState = 0;

int CH1;
int CH1min;
int CH1max;

int CH2;
int CH2min;
int CH2max;

int CH3;
int CH3min;
int CH3max;

int CHdefault = 1500;

#define Memory A0
#define Freccia_Dx 2
#define Freccia_Sx 4

#define Posizione_Ant 3
#define Abbaglianti 7

#define Posizione_Pos 6
#define Stop 8

#define Marmitta 5
#define Retro 12

#define RX1 9
#define RX2 10
#define RX3 11

int Duty = 120;
int val = 0;
int Contatore = 0;
int StatoCorrente = 0;
int StatoPrecedente = 0;
int Emergenza = 0;

int Fade = 1;
int Lumen = 0;



void setup() {
  pinMode(Memory, INPUT);
  pinMode(Freccia_Dx, OUTPUT);
  pinMode(Freccia_Sx, OUTPUT);
  pinMode(Posizione_Ant, OUTPUT);
  pinMode(Abbaglianti, OUTPUT);
  pinMode(Posizione_Pos, OUTPUT);
  pinMode(Stop, OUTPUT);
  pinMode(Marmitta, OUTPUT);
  pinMode(Retro, OUTPUT);

  CH1min = (EEPROM.read(0) * 256) + EEPROM.read(5);
  CH1max = (EEPROM.read(10) * 256) + EEPROM.read(15);

  CH2min = (EEPROM.read(20) * 256) + EEPROM.read(25);
  CH2max = (EEPROM.read(30) * 256) + EEPROM.read(35);

  CH3min = (EEPROM.read(40) * 256) + EEPROM.read(45);
  CH3max = (EEPROM.read(50) * 256) + EEPROM.read(55);

  test();
  counter = 0;

  delay(1000);
}

void loop() {

  if (digitalRead(Memory) == HIGH) {
    CH1min = CHdefault;
    CH1max = CHdefault;
    CH2min = CHdefault;
    CH2max = CHdefault;
    CH3min = CHdefault;
    CH3max = CHdefault;
    currentState = 1;

  } else {

    currentState = 0;
  }
  if (currentState != previousState) {
    if (currentState == 1) {
      counter = counter + 1;
    }
  }
  previousState = currentState;

  if (counter >= 2) {
    counter = 0;
  }

  if (counter == 0) {
    programma();
  }

  else {
    memo();
  }
}

void memo() {

  digitalWrite(Freccia_Dx, HIGH);
  digitalWrite(Freccia_Sx, HIGH);

  CH1 = pulseIn(RX1, HIGH);
  CH2 = pulseIn(RX2, HIGH);
  CH3 = pulseIn(RX3, HIGH);

  int CH1minHigh;
  int CH1minLow;
  int CH1maxHigh;
  int CH1maxLow;

  int CH2minHigh;
  int CH2minLow;
  int CH2maxHigh;
  int CH2maxLow;

  int CH3minHigh;
  int CH3minLow;
  int CH3maxHigh;
  int CH3maxLow;


  if (CH1 < CH1min) {
    CH1min = CH1;
    for (int i = 0; i < 255; i++) {
      CH1minHigh = highByte(CH1min);
      CH1minLow = lowByte(CH1min);
      EEPROM.update(0, CH1minHigh);
      EEPROM.update(5, CH1minLow);
    }
  }

  if (CH1 > CH1max) {
    CH1max = CH1;
    for (int i = 0; i < 255; i++) {
      CH1maxHigh = highByte(CH1max);
      CH1maxLow = lowByte(CH1max);
      EEPROM.update(10, CH1maxHigh);
      EEPROM.update(15, CH1maxLow);
    }
  }


  if (CH2 < CH2min) {
    CH2min = CH2;
    for (int i = 0; i < 255; i++) {
      CH2minHigh = highByte(CH2min);
      CH2minLow = lowByte(CH2min);
      EEPROM.update(20, CH2minHigh);
      EEPROM.update(25, CH2minLow);
    }
  }

  if (CH2 > CH2max) {
    CH2max = CH2;
    for (int i = 0; i < 255; i++) {
      CH2maxHigh = highByte(CH2max);
      CH2maxLow = lowByte(CH2max);
      EEPROM.update(30, CH2maxHigh);
      EEPROM.update(35, CH2maxLow);
    }
  }



  if (CH3 < CH3min) {
    CH3min = CH3;
    for (int i = 0; i < 255; i++) {
      CH3minHigh = highByte(CH3min);
      CH3minLow = lowByte(CH3min);
      EEPROM.update(40, CH3minHigh);
      EEPROM.update(45, CH3minLow);
    }
  }

  if (CH3 > CH3max) {
    CH3max = CH3;
    for (int i = 0; i < 255; i++) {
      CH3maxHigh = highByte(CH3max);
      CH3maxLow = lowByte(CH3max);
      EEPROM.update(50, CH3maxHigh);
      EEPROM.update(55, CH3maxLow);
    }
  }
  
  if (digitalRead(Memory) == HIGH) {
    setup();
  }
}


void test() {

  digitalWrite(Freccia_Sx, HIGH);
  digitalWrite(Freccia_Dx, HIGH);
  delay(500);
  digitalWrite(Posizione_Ant, HIGH);
  digitalWrite(Posizione_Pos, HIGH);
  delay(500);
  digitalWrite(Abbaglianti, HIGH);
  digitalWrite(Stop, HIGH);
  delay(500);
  digitalWrite(Marmitta, HIGH);
  digitalWrite(Retro, HIGH);
  delay(1000);
  spento();
}

void programma() {
  CH1 = map(pulseIn(RX1, HIGH), CH1min, CH1max, -100, 100);
  CH2 = map(pulseIn(RX2, HIGH), CH2min, CH2max, -100, 100);
  CH3 = map(pulseIn(RX3, HIGH), CH3min, CH3max, -100, 100);


  if (CH3 < -75) {
    spento();
  } else if (CH3 > -75 && CH3 < -50) {
    reale();
  } else if (CH3 > -50 && CH3 < 0) {
    polizia();
  } else if (CH3 > 0 && CH3 < 25) {
    fade();
  } else if (CH3 > 25) {
    devil();
  }
}

void spento() {
  digitalWrite(Freccia_Sx, LOW);
  digitalWrite(Freccia_Dx, LOW);
  digitalWrite(Posizione_Ant, LOW);
  digitalWrite(Posizione_Pos, LOW);
  digitalWrite(Abbaglianti, LOW);
  digitalWrite(Stop, LOW);
  digitalWrite(Marmitta, LOW);
  digitalWrite(Retro, LOW);
}

void reale() {
  analogWrite(Posizione_Ant, Duty);
  analogWrite(Posizione_Pos, Duty);
  luci();
  freniretro();
  freccie();
}

void luci() {
  if (CH2 > 90) {
    marmitta();
    digitalWrite(Abbaglianti, HIGH);
    delay(100);
    digitalWrite(Abbaglianti, LOW);
    delay(100);
  }
}

void freniretro() {

  if (CH2 < -25) {
    StatoCorrente = 1;
    digitalWrite(Stop, HIGH);

  } else {
    StatoCorrente = 0;
    digitalWrite(Stop, LOW);
  }

  if (StatoCorrente != StatoPrecedente) {
    if (StatoCorrente == 1) {
      Contatore = Contatore + 1;
    }
  }
  StatoPrecedente = StatoCorrente;

  if (CH2 > 5) {
    Contatore = 0;
  }

  if (Contatore >= 2) {
    digitalWrite(Retro, HIGH);
    digitalWrite(Stop, LOW);
  } else {
    digitalWrite(Retro, LOW);
  }
}

void marmitta() {
  int PotenzaFiamma = random(10, 255);
  int TempoFiamma = random(100, 250);

  analogWrite(Marmitta, PotenzaFiamma);
  delay(TempoFiamma);
  analogWrite(Marmitta, 0);
  delay(TempoFiamma);
}

void ManovraFrecce(bool sx, bool dx) {
  digitalWrite(Freccia_Sx, sx);
  digitalWrite(Freccia_Dx, dx);
}

void freccie() {

  while (CH1 <= 10 && CH1 >= -10) {
    Emergenza++;
    ManovraFrecce(0, 0);
    if (Emergenza > 10000) {
      ManovraFrecce(1, 1);
      delay(500);
      ManovraFrecce(0, 0);
      delay(500);
    }
    break;
  }

  if (CH1 < -25) {
    Emergenza = 0;
    digitalWrite(Freccia_Sx, HIGH);
    delay(500);
    digitalWrite(Freccia_Sx, LOW);
    delay(500);
  } else if (CH1 > 25) {
    Emergenza = 0;
    digitalWrite(Freccia_Dx, HIGH);
    delay(500);
    digitalWrite(Freccia_Dx, LOW);
    delay(500);
  }
}

void polizia() {
  int modo = random(2);

  analogWrite(Posizione_Ant, Duty);
  analogWrite(Posizione_Pos, Duty);


  switch (modo) {
    case 0:
      analogWrite(Posizione_Ant, 255);
      digitalWrite(Stop, HIGH);
      ManovraFrecce(1, 1);
      delay(150);
      analogWrite(Posizione_Ant, 100);
      digitalWrite(Stop, LOW);
      ManovraFrecce(0, 0);
      delay(150);
      analogWrite(Posizione_Ant, 255);
      digitalWrite(Stop, HIGH);
      ManovraFrecce(1, 1);
      delay(150);
      analogWrite(Posizione_Ant, 100);
      digitalWrite(Stop, LOW);
      ManovraFrecce(0, 0);
      delay(250);

      analogWrite(Posizione_Pos, 255);
      digitalWrite(Abbaglianti, HIGH);
      delay(150);
      analogWrite(Posizione_Pos, 100);
      digitalWrite(Abbaglianti, LOW);
      delay(150);
      analogWrite(Posizione_Pos, 255);
      digitalWrite(Abbaglianti, HIGH);
      delay(150);
      analogWrite(Posizione_Pos, 100);
      digitalWrite(Abbaglianti, LOW);
      delay(250);
      break;

    case 1:
      analogWrite(Posizione_Pos, 100);
      analogWrite(Posizione_Ant, 100);
      ManovraFrecce(1, 1);
      digitalWrite(Abbaglianti, HIGH);
      delay(1000);

      analogWrite(Posizione_Pos, 255);
      analogWrite(Posizione_Ant, 255);
      ManovraFrecce(0, 0);
      digitalWrite(Abbaglianti, LOW);
      delay(1000);
      break;
  }
}

void fade() {

  analogWrite(Posizione_Ant, Lumen);
  analogWrite(Posizione_Pos, Lumen);
  Lumen = Lumen + Fade;

  if (Lumen <= 0 || Lumen >= 255) {
    Fade = -Fade;
  }

  delay(30);
}

void devil() {
  int Sterzo = abs(map(CH1, -100, 100, -255, 255));
  int Gas = abs(map(CH2, -100, 100, -255, 255));

  analogWrite(Freccia_Sx, 0);
  analogWrite(Freccia_Dx, 0);
  analogWrite(Posizione_Ant, 0);
  analogWrite(Posizione_Pos, 0);

  if (CH1 < -10) {
    analogWrite(Freccia_Sx, Sterzo);
  }

  if (CH1 > 10) {
    analogWrite(Freccia_Dx, Sterzo);
  }

  if (CH2 < -10) {
    analogWrite(Posizione_Pos, Gas);
  }

  if (CH2 > 10) {
    analogWrite(Posizione_Ant, Gas);
  }

  if (CH2 > 80) {
    marmitta();
  }
}