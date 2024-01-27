#include <Wire.h>

#include <BleKeyboard.h>
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

BleKeyboard bleKeyboard;
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Cambia a -1 si no se usa un pin de reset
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <Keypad.h>
// define numero de filas
const uint8_t ROWS = 3;
// define numero de columnas
const uint8_t COLS = 6;
// define la distribucion de teclas
char keys[ROWS][COLS] = {
  { '1', '2', '3', '4' ,'5'},
  { '6', '7', '8', '9','10' }
};

// pines correspondientes a las filas
uint8_t colPins[COLS] = { 2, 15,19, 18, 5 };
// pines correspondientes a las columnas
uint8_t rowPins[ROWS] = { 16, 4 };
// crea objeto con los prametros creados previamente
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);



void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    Serial.println(F("Error al iniciar la pantalla OLED"));
    while (1);
  }
  
  // Configura el tamaño del texto y el color
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
}

void loop() {
 
  if(bleKeyboard.isConnected()) {
 

     char key = keypad.getKey();
  // comprueba que se haya presionado una tecla
  if (key) {
    // envia a monitor serial la tecla presionada
    Serial.println(key);
  }
  switch(key){

    case '1':
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    pantalla("Pausa");
    break;


    case '2':
    bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
    pantalla("Siguiente canción --->");
    break;


    case '3':
    bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
    pantalla("<--- Canción anterior ");
    break;


    case '4':
    pantalla("Trabajo");
    bleKeyboard.write(KEY_MEDIA_WWW_HOME);
    delay(500);
    bleKeyboard.print("make.powerapps.com");
    bleKeyboard.write(KEY_NUM_ENTER);
    delay(500);
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.print("t");
     delay(500);
     bleKeyboard.releaseAll();
     bleKeyboard.print("www.figma.com");
    bleKeyboard.write(KEY_NUM_ENTER);
    delay(500);
     bleKeyboard.press(KEY_LEFT_CTRL);
     bleKeyboard.print("t");
     delay(500);
     bleKeyboard.releaseAll();
     bleKeyboard.print("loop.microsoft.com");
     bleKeyboard.write(KEY_NUM_ENTER);
    delay(500);
      bleKeyboard.write(KEY_LEFT_GUI);
      delay(500);
      bleKeyboard.print("spotify");
      delay(1000);
      bleKeyboard.press(KEY_NUM_ENTER);
      delay(1000);
     bleKeyboard.releaseAll();
      bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
     
    break;

    case '5':
      pantalla("WhatsApp");
      bleKeyboard.write(KEY_LEFT_GUI);
      delay(500);
      bleKeyboard.print("whatsapp");
      delay(500);
      bleKeyboard.press(KEY_NUM_ENTER);
      delay(500);
     bleKeyboard.releaseAll();
      break;

    case'6':
      pantalla("Discord");
      bleKeyboard.write(KEY_LEFT_GUI);
      delay(500);
      bleKeyboard.print("discord");
      delay(500);
      bleKeyboard.press(KEY_NUM_ENTER);
      delay(500);
     bleKeyboard.releaseAll();
      break;


    case'7':
      pantalla("Spotify");
      bleKeyboard.write(KEY_LEFT_GUI);
      delay(500);
      bleKeyboard.print("spotify");
      delay(500);
      bleKeyboard.press(KEY_NUM_ENTER);
      delay(500);
      bleKeyboard.releaseAll();
      bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
      break;



  }
  
    // Serial.println("Sending 'Hello world'...");
    // bleKeyboard.print("Hello world");

     delay(100);

    // Serial.println("Sending Enter key...");
    // bleKeyboard.write(KEY_RETURN);

    // delay(1000);

    // Serial.println("Sending Play/Pause media key...");
    // bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);

    // delay(1000);
    
   //
   // Below is an example of pressing multiple keyboard modifiers 
   // which by default is commented out. 
   // 
   /* Serial.println("Sending Ctrl+Alt+Delete...");
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_DELETE);
    delay(100);
    bleKeyboard.releaseAll();
    */
  }else{
     pantalla("Conectando ...");
  }

}

  void pantalla(String texto){
    display.clearDisplay();
  display.setCursor(0,0);
  display.println(texto);
  display.display();
  }