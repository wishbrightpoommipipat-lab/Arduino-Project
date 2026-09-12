#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int relay = 12;
int button_1 = 11;
int button_state1 = 0;

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
int position = 0;  //ประกาศตัวเเปรบอกตำแหน่ง
String pass1, pass2, pass3, pass4, password;
char pass[4], cancel[1];
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char key;
int i;

//=============================================================================================================================


void setup() {
  pinMode(relay, OUTPUT);
  pinMode(button_1, INPUT);
  digitalWrite(relay, LOW);
  Serial.begin(9600);
  lcd.begin();
  //lcd.backlight();
}




void loop() {
  char key ;
  lcd.clear();
  position = 0;
  lcd.setCursor(3, 0);
  lcd.print("Key  Pass");
  while (position < 4) {
    lcd.setCursor(position, 1);
    key = keypad.getKey();
    if (key != NO_KEY) {
        pass[position] = key;
        lcd.setCursor(6+position,1);
        lcd.print(key);
        position++;
      
    }else{
      //การปลดล็อคด้วยปุ่ม
      button_state1 = digitalRead(button_1);
      Serial.println(button_state1);
      if(button_state1 == 1){
        digitalWrite(relay, HIGH);
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("Unlock");
        delay(10000);
        lcd.clear();
        
        
      }else{
        lcd.setCursor(3, 0);
        lcd.print("Key  Pass");
        digitalWrite(relay, LOW);
        
   
      }
    }
  }
  int i = 0;
  while (i < 4) {
    if (i == 0) {
      pass1 = pass[i];
    } else if (i == 1) {
      pass2 = pass[i];
    } else if (i == 2) {
      pass3 = pass[i];
    } else if (i == 3) {
      pass4 = pass[i];
    }
    i++;
  }
  password = pass1 + pass2 + pass3 + pass4;
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print(password);
  Serial.print(password);
  keypass();
  lcd.clear();
  
  
}



void keypass(){
   //การล็อคแบบตั้งเวลา
  if (password == "1234") {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Unlock");
    digitalWrite(relay, HIGH);
    delay(10000);
    password = "0000";
    delay(10);

  //ปลดล็อคค้างกด "#" เพื่อล็อค
  } else if (password == "1111") {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Unlock");
    digitalWrite(relay, HIGH);
    delay(1000);
      lcd.clear();
      position = 0;
      lcd.setCursor(1, 0);
      lcd.print("Key # for Lock");
      while (position < 1) {
        lcd.setCursor(position, 1);
        key = keypad.getKey();
        if (key != NO_KEY) {
          pass[position] = key;
          lcd.print(key);
          position++;
        }else if(pass == "#"){
          password = "0000";
        }
      
    }
    password = "0000";
    delay(10);


    //ถ้าใส่รหัสผิดกลอนจะไม่ปลดล็อก
  } else {
    digitalWrite(relay, LOW);
    lcd.setCursor(3, 0);
    lcd.print("Pass Wrong");
    delay(500);
    lcd.clear();
    delay(500);
    lcd.setCursor(3, 0);
    lcd.print("Pass Wrong");
    delay(500);
    lcd.clear();
    delay(500);
  }

  claer_pass();
}



void claer_pass() {
  if (password == "0000") {
    digitalWrite(relay, LOW);
    delay(100);
  }
}
