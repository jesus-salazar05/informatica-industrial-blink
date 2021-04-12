#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#define btnIN A0 //Entrada analogica
#define LED 10   //Salida digital

char pulsacion;       // almacena la tecla pulsada
int  contador = 1;    // cuenta el nivel del menu en el que se esta
const byte ROWS = 4;  //Cuatro Filas
const byte COLS = 4;  //Cuatro Columnas 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9,8,7,6}; //Puntos de conexion del teclado al arduino FILAS
byte colPins[COLS] = {5,4,3,2}; //Puntos de conexion del teclado al arduino COLUMNAS
Keypad Teclado1 = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //Configura el teclado
LiquidCrystal_I2C lcd(0x27,16,2); // dependiendo del fabricante del I2C el codigo 0x27 cambiar a
                                  // 0x3F , 0x20 , 0x38 , 
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

void intro_0();
void menu_1();
void menu_2();
void menu_3();
void menu_4();
void accion_1();
void accion_2();
void accion_3();
void accion_4();
void intermitente();

void setup()
{
  pinMode(btnIN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  lcd.init();
  lcd.backlight();
  pinMode(12, OUTPUT);
  intro_0();             // muestra el intro de  bienvenida
}

void loop()
{
  
  func1(); //Button detection
  func2(); //Menu de seleccion
  funcDesva(10);
  

  pulsacion = Teclado1.getKey() ;  // Lee la tecla pulsada
  if (pulsacion != 0) {      
      lcd.clear();
      delay(100);
  } 
  if(contador == 4){ menu_4();accion_4();}
  if(contador == 3){ menu_3();accion_3();}
  if(contador == 2){ menu_2();accion_2();}
  if(contador == 1){ menu_1();accion_1();}
  
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
/////////////////////Intro_0 //////////////////////////////
void intro_0(){ 
 lcd.clear();  // Borra el  LCD
 lcd.setCursor(3,0);         // Se posiciona en la Columna 3, Fila 0
 lcd.print("BIENVENIDO ");
 lcd.setCursor(1,1);
 lcd.print("PRUEBA DE MENU");
 delay(4000);                // espera 4 segundos mostrando el intro
 lcd.clear();
}
/////////////////////Menu_1  //////////////////////////////////
void menu_1(){ 
   lcd.setCursor(0,0);
   lcd.print("ON    >1  ");
   lcd.setCursor(10,0);
   lcd.print("OFF >2");   
   lcd.setCursor(0,1);
   lcd.print("INTER >3  "); 
   lcd.setCursor(10,1);
   lcd.print("MAS >*");
}
/////////////////////Accion 1 //////////////////////////////
void accion_1(){ 
  if(pulsacion == '1') digitalWrite(12,HIGH);
  if(pulsacion == '2') digitalWrite(12,LOW);
  if(pulsacion == '3') intermitente();
  if(pulsacion == '*') contador=2;
}
/////////////////////Menu_2  //////////////////////////////////
void menu_2(){ 
   lcd.setCursor(0,0);
   lcd.print("LUZ  >1   ");
   lcd.setCursor(8,0);
   lcd.print("TIEMPO>2");
   lcd.setCursor(0,1);
   lcd.print("MENU >#          ");
}
/////////////////////accion_2  //////////////////////////////////
void accion_2(){ 
  if(pulsacion == '1') contador=3;
  if(pulsacion == '2') contador=4;
  if(pulsacion == '#') contador=1;
}
/////////////////////Menu_3  //////////////////////////////////
void menu_3(){ 
   lcd.setCursor(0,0);
   lcd.print("LUZ :           ");
   lcd.setCursor(5,0);
   lcd.print(analogRead(A0));  
   lcd.setCursor(0,1);
   lcd.print("MENU>#      <--0");
}
/////////////////////accion_3  //////////////////////////////////
void accion_3(){ 
  if(pulsacion == '#') contador=1;
  if(pulsacion == '0') contador=2;
}
/////////////////////Menu_4 //////////////////////////////////
void menu_4(){ 
   unsigned long tiempo1 = (millis()/1000);  
   lcd.setCursor(0,0);
   lcd.print("TIEMPO:            ");
   lcd.setCursor(8,0);
   lcd.print(tiempo1);  
   lcd.setCursor(0,1);
   lcd.print("MENU>#      <--0");
}
/////////////////////accion_4  //////////////////////////////////
void accion_4(){ 
  if(pulsacion == '#') contador=1;
  if(pulsacion == '0') contador=2;
}
/////////////////////intermitente  //////////////////////////////////
void intermitente(){ 
  digitalWrite(12,HIGH);
  delay(300);
  digitalWrite(12,LOW);
  delay(300);
  digitalWrite(12,HIGH);
  delay(300);
  digitalWrite(12,LOW);
  delay(300);
}
