#include <ESP8266WiFi.h>

const char* ssid     = "FNN-GUEST"; //Здесь меняете по названию ВайФая
const char* password = "gmZvyckY";  //Здесь пароль Вайфая

const char* host = "test.boshon.kz"; // Указывать хост по URI то есть без протокола. К примеру, google.com НЕ https://google.com

float sensor = 0; //Переменная для хранения данных с датчика


void setup() {
  
  Serial.begin(115200);

  Serial.println();               //Очередные формальности для наблюдения
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);   // Инициализация вайфая

  while (WiFi.status() != WL_CONNECTED) {  //Ждать пока соединение не будет установлено
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(5000);

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClientSecure client; //Объявляем объект ВайФай клиента для безопасной работы
  const int httpPort = 443; // 80 is for HTTP / 443 is for HTTPS! Специфицируем протокол
  
  client.setInsecure(); // this is the magical line that makes everything work
  // Это просто надо
  
  if (!client.connect(host, httpPort)) { //Проверка соединения 
    Serial.println("connection failed");
    return;
  }
  
  sensor = analogRead(A0)/4; //Читаем данные с датчика
  
  // We now create a URI for the request
  String url = "/testcode/dht.php"; //Создаем string в котором будет путь до нашего PHP скрипта в файловом системе сервера
  url += "?temperature=" + String(sensor) + "&humidity=80"; //а также указываем знаечния переменных которые фигурируют в скрипте в этом случае одна из них равна значению с датчика


  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server     Делаем запрос по url в нашем string-е 
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

  Serial.println();
  Serial.println("closing connection");
  delay(5000);
}
