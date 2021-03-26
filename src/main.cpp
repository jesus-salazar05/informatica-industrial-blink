#include <Arduino.h>
#define btnIN A0 //Entrada analogica
#define LED 10   //Salida digital

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
void setup()
{
  pinMode(btnIN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop()
{
  
  func1(); //Button detection
  func2(); //Menu de seleccion
  funcDesva(10);
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

  //Prueba de cambio para repositorio remoto
}
