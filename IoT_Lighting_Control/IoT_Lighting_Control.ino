#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "Wokwi-GUEST"; // Define o nome da rede Wi-Fi.
const char* password = "";        // Define a senha da rede Wi-Fi.

const char* host = "api.thingspeak.com";      // Define o host da API para troca e dados.
const char* APIkeyWrite = "YIAQZAZ9G7LX6IZA"; // Define a chave individual da API.

#define ch1 18
#define led 19

#define led_1 32
#define led_2 33
#define led_3 25
#define led_4 26

const int analogInPin = 35; // Pino analógico que o sensor está conectado.
const int digitalPin = 12;  // Pino digital que o sensor está conectado.

int sensorValue = 0; // valor que será lido do sensor

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Grupo 11:");
  lcd.setCursor(1,1);
  lcd.print("Projeto de IoT.");
  pinMode(ch1, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  Serial.begin(9600); // inicializa a comunicação serial com a taxa de 9600 bps
  pinMode(digitalPin, OUTPUT);

  WiFi.begin(ssid, password);  // rede e senha do WiFi
  Serial.print("Conectando-se ao WiFi");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(100);
    Serial.print(".");
  }

    Serial.println("Conectado a Rede! Seu IP é = ");
    Serial.println(WiFi.localIP());
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Conectou no WIFI");
    delay(1000);
    lcd.clear();

    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
    digitalWrite(led_4, LOW);
}

void loop() {

  WiFiClient client; 
  const int httpPort = 80; 
      
  if (!client.connect(host, httpPort))
  {
    return; 
  }

  sensorValue = analogRead(analogInPin); // Faz a leitura do pino analógico
  
  Serial.print("sensor = " );            // Imprime o resultado no monitor serial
  Serial.println(sensorValue);      

  if (sensorValue <= 1000 && sensorValue > 800)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Claridade: ");
    digitalWrite(digitalPin, LOW);
    lcd.setCursor(11,0);
    lcd.print(sensorValue);
    lcd.setCursor(0,1);
    lcd.print("Ambiente claro.");
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
    digitalWrite(led_4, LOW);
  }
    else if (sensorValue <= 800 && sensorValue > 600)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Claridade: ");
    digitalWrite(digitalPin, LOW);
    lcd.setCursor(11,0);
    lcd.print(sensorValue);
    lcd.setCursor(0,1);
    lcd.print("Ambiente claro.");
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
    digitalWrite(led_4, LOW);
  }
    else if (sensorValue <= 600 && sensorValue > 400 )
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Claridade: ");
    digitalWrite(digitalPin, LOW);
    lcd.setCursor(11,0);
    lcd.print(sensorValue);
    lcd.setCursor(0,1);
    lcd.print("Ambiente claro.");
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, LOW);
    digitalWrite(led_4, LOW);
  }
      else if (sensorValue <= 400 && sensorValue > 200)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Claridade: ");
    digitalWrite(digitalPin, HIGH);
    lcd.setCursor(11,0);
    lcd.print(sensorValue);
    lcd.setCursor(0,1);
    lcd.print("Ambiente escuro.");
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, HIGH);
    digitalWrite(led_4, LOW);
  }
      else if (sensorValue <= 200)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Claridade: ");
    digitalWrite(digitalPin, HIGH);
    lcd.setCursor(11,0);
    lcd.print(sensorValue);
    lcd.setCursor(0,1);
    lcd.print("Ambiente escuro.");
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, HIGH);
    digitalWrite(led_4, HIGH);
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Claridade: ");
    digitalWrite(digitalPin, LOW);
    lcd.setCursor(11,0);
    lcd.print(sensorValue);
    lcd.setCursor(0,1);
    lcd.print("Ambiente claro.");
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
    digitalWrite(led_4, LOW);
  }

  delay(500); // Aguarda 500 milisegundos para estabilizar o conversor ADC

  if (!client.connect(host, httpPort))
    {
      return; 
    }
    String url = "/update?api_key="; 
    url += APIkeyWrite; 
    url += "&field1="; 
    url += String(sensorValue); 
    url += "\r\n"; 
    String endereco = String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"; 
    client.print(endereco); 
    delay(500);   
                      
}
