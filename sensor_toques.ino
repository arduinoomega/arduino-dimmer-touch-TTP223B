#include <LiquidCrystal.h> // inclui a biblioteca LiquidCrystal
#define pwm 9 // define o pino 9 com o nome pwm
#define touch 8 // define o pino 8 com o nome touch
#define tempoMaximoDeUmToque  200 // milisegundos
#define tempoMaximoEntreToques 400 // milisegundos
int count; // cria a variavel count int
int contaToques = 0; // cria a variavel contaToques int
long tempoEspera = 0; // cria a variavel tempoEspera long
long tempoEsperaEntreToques = 0; // cria a variavel tempoEsperaEntreToques long
void executarAcao();
LiquidCrystal lcd ( 7, 6, 5, 4, 3, 2); // define os pinos para comunicação dodisplay lcd

void setup() {
  
  pinMode(pwm, OUTPUT); // define o pino pwm como saída
  pinMode(touch, INPUT); // define o pino touch como entrada 
  lcd.begin(16,2); // inicia a comunicação com o lcd 
  lcd.setCursor(0,0); lcd.print("  DIMMER TOUCH"); // escreve no lcd DIMMER TOUCH
}

void loop() {
  
  int sensortouch = digitalRead(touch); //verifica o estado do sensor touch

  if (sensortouch == HIGH) { //se o sensor detectou toques, executa o codigo abaixo

     //espera um tempo para nao detectar o mesmo toque mais de uma vez 
     if (tempoEspera == 0) {
        tempoEspera = tempoEsperaEntreToques = millis(); 
        contaToques++;} 
     else if ((millis() - tempoEspera) >= tempoMaximoDeUmToque) {
        tempoEspera = 0;}
  }

    //caso exceda o tempo maximo entre toques, zera o contador de toques
  if ( (contaToques != 0) && ((millis() - tempoEsperaEntreToques) > tempoMaximoEntreToques) ) {
     executarAcao();
     contaToques = 0;
     tempoEsperaEntreToques = millis(); }
     lcd.noBlink(); // desativa o blink no cursor do display

    // se o touch for mantido prescionado, executa o código abaixo
  if(sensortouch == HIGH ){  
     lcd.display(); // liga o display
     lcd.setCursor(0,1); lcd.print("                "); // limpa os caracteres do display
     analogWrite(pwm,count); // escreve no formato pwm a saída do pino 9
     count++; // contador para subir o nivel pwm até 250
     lcd.setCursor(0,1); lcd.print(count * 0.4); // converte o nivel pwm 250 para porcentagem %
     lcd.setCursor(4,1); lcd.print("%");
     lcd.setCursor(15,1);
     lcd.blink(); // ativa o blink no cursor do display
     delay(30); // delay
   if (count == 250){ // se pwm estiver em 250 ou 100% no display, zera o contador
     count = 0;
     lcd.setCursor(1,1); lcd.print("  "); // limpa caracteres no display
     }}
  }
void executarAcao() {
  
  switch (contaToques) { // verifica a variavel contaToques
    case 2: // caso 2 toques
       lcd.noBlink();
       digitalWrite(pwm, LOW);  // leva nivel baixo para saída 
       lcd.setCursor(0,1); lcd.print("LED OFF "); // escreve  LED OFF no display
       delay(2000); // delay
       lcd.noDisplay(); // desliga display
       break;
    case 3: // caso 3 toques
       lcd.noBlink();
       digitalWrite(pwm, HIGH); // leva nivel alto para saída
       lcd.setCursor(0,1); lcd.print("LED ON  "); // escreve  LED ON no display
       break;
       }
  }
