#include <Arduino.h>
#include <LiquidCrystal.h>


#define btnIN A0 //Entrada analogica
#define LED 7   //Salida digital


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int upButton = 10;
int downButton = 9;
int selectButton = 8;
int menu = 1;


enum funMode
{
  OFF,
  BLINK1,
  BLINK2,
  BLINK3,
  BLINK4,
  NBSTATE
};

int L_STD = LOW;
unsigned long pre_Millis, pas_Millis;
unsigned long lastDeTime = 0;       //Ultimo tiempo definido como 0 o inicio (rebote)
int LstBSTD = HIGH;                 //Ultimo estado pre-definido es Alto
int btnSTD = 0;                     //Estado presente
int funcSTD = 0;                    //Estados para de la funcion de seleccion de Menu
int BP1 = 50, BP2 = 100, BP3 = 200; //Blink intermidiate time
int interB = 100;                  //Blink intermidiate time general

void func1();
void func2();
void funcB1(int);
void funcB2(int);
void funcB3(int);
void funcB4(int);
void funcDesva(int);

void action1();
void action2();
void action3();
void action4();

void intermitente();
void updateMenu();
void execute();

void setup()
{
  lcd.begin(16, 2);

  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  updateMenu();
  pinMode(btnIN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  
}

void loop()
{
  if (!digitalRead(downButton)) {
    menu++;
    updateMenu();
    delay(100);
  }

  if (!digitalRead(upButton)) {
    menu--;
    updateMenu();
    delay(100);
    
  }

  if (!digitalRead(selectButton)) {
    execute();
    updateMenu();
    delay(100);
    
  }	
  

}
/////////////////////////////////////////////
void func1()
{
  int reading = digitalRead(btnIN);
  if (reading != LstBSTD)
  {                        //Ultima estado definido del buton
    lastDeTime = millis(); //lastDeubonceTime
    if ((millis() - lastDeTime) > 100)
    {
      if (reading != btnSTD)
      {
        btnSTD = reading;
      }
      if (btnSTD == HIGH)
      {
        funcSTD += 1;
      }
    }
  }
  LstBSTD = reading;
  funcSTD = funcSTD % NBSTATE;
}
/////////////////////////////////////
void func2()
{
  switch (funcSTD)
  {
  case OFF:
    //FuncionOFF - LED
    digitalWrite(LED, LOW);
    break;
  case BLINK1:
    //FuncionBlink1 - LED
    funcB1(BP1);
    break;
  case BLINK2:
    //FuncionBlink2 - LED
    funcB2(BP2);
    break;
  case BLINK3:
  //FuncionBlink3 - LED
    funcB3(BP3);
    break;
  //FuncionBlink4 - LED
  case BLINK4:
    funcB4(interB);
    break;
  }
}
void funcB1(int BP1)
{
  delay(BP1);
  digitalWrite(LED, LOW);
  delay(BP1);
  digitalWrite(LED, HIGH);
}
void funcB2(int BP2)
{
  delay(BP2);
  digitalWrite(LED, LOW);
  delay(BP2);
  digitalWrite(LED, HIGH);
}
void funcB3(int BP3)
{
  delay(BP3);
  digitalWrite(LED, LOW);
  delay(BP3);
  digitalWrite(LED, HIGH);
}
void funcB4(int interB) {
  pre_Millis = millis();
  if ((pre_Millis - pas_Millis) >= interB) {
    pas_Millis = pre_Millis;
    if(L_STD = LOW) {
      L_STD = HIGH;
    } else {
      L_STD = LOW;
    }
  }

}

// ####################################
// ############# Updating #############
// ####################################

void updateMenu() {
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">LED ON");
      lcd.setCursor(0, 1);
      lcd.print(" LED OFF");
      break;
    case 2:
      lcd.clear();
      lcd.print(" LED ON");
      lcd.setCursor(0, 1);
      lcd.print(">LED OFF");
      break;
    case 3:
      lcd.clear();
      lcd.print(">Desvanecido");
      lcd.setCursor(0, 1);
      lcd.print(" Intermitente");
      break;
    case 4:
      lcd.clear();
      lcd.print(" Desvanecido");
      lcd.setCursor(0, 1);
      lcd.print(">Intermitente");
      break;
    case 5:
      menu = 4;
      break;
  }
}


// ####################################
// ############ Executing #############
// ####################################

void execute() {
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
     case 4:
      action4();
      break;
  }
}


// ####################################
// ############## Actions #############
// ####################################

void action1() {
  lcd.clear();
  lcd.print(">LED ON");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  
  digitalWrite(LED, HIGH);
  
  delay(500);
}

void action2() {
  lcd.clear();
  lcd.print(">LED OFF");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  
  digitalWrite(LED, LOW);
  
  delay(500);
}

void action3() {
  lcd.clear();
  lcd.print(">Desavecido");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  funcDesva(2);
  delay(1500);
  
}

  void action4() {
  lcd.clear();
  lcd.print(">Intermitente");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  delay(150);
  lcd.print(".");
  intermitente();
  delay(1500);
}


void funcDesva(int temp){//la funcion recibe un entero el cual varia la velocidad de desvanecido
  int periodo = temp;//periodo toma el valor que de temp
  //Se declaran dos tiempos los cuales se usarn para la espera o el delay
  unsigned long tiempo1 = 0;
  unsigned long tiempo2 = 0;
  int brillo;
  for(brillo = 0; brillo <= 255; brillo++){//por medio de un for se va aumentando el brillo del led
    analogWrite(LED,brillo);
    tiempo1 = millis();//se le asigna al tiempo 1 el valor de millis
    //el while nos ayuda a sustituir el delay
    while (millis() < tiempo1 + periodo){
      //Espera 
    }
  }
  for(brillo = 255; brillo >= 0; brillo-- ){//este for ahora nos sirve para disminuirel brillo del led
    analogWrite(LED,brillo);
    tiempo2 = millis();
    while (millis() < tiempo2 + periodo){
      /* ESPERA */
    }

  }

  
}

void intermitente(){
  digitalWrite(LED,HIGH);
  delay(300);
  digitalWrite(LED,LOW);
  delay(300);
  digitalWrite(LED,HIGH);
  delay(300);
  digitalWrite(LED,LOW);
  delay(300);
}

