#include <ESP8266WiFi.h>

const char* ssid     = "FNN-GUEST"; //Здесь меняете по названию ВайФая
const char* password = "gmZvyckY";  //Здесь пароль Вайфая

const char* host = "test.boshon.kz"; // Указывать хост по URI то есть без протокола. К примеру, google.com НЕ https://google.com



void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // на esp8266 встроенный ЛЕД работает наоборот из-за стягивающихся резисторов
  Serial.begin(115200);
  delay(3000);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);                //Это все формальности

  WiFi.begin(ssid, password);  // Инициализация вайфая

  while (WiFi.status() != WL_CONNECTED) {   //Ждать пока соединение не будет установлено
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
  float val=0; //В этой переменной будем хранить данные с БД
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

  // We now create a URI for the request
  String url = "/testcode/dbread.php";  //Создаем string в котором будет путь до нашего PHP скрипта в файловом системе сервера


  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server  Делаем запрос по url в нашем string-е 
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
               
  Serial.println("Sensor data:");
  
  while (client.available()) { //Пока объект вайфая доступен
    
    String line = client.readStringUntil('\n'); //Читаем каждую линию и перезаписываем переменную
    
    if (line.startsWith("sensor:")) { //Если линия начинается на нужное нам слово
      
      String line = client.readStringUntil('\n'); //То читаем следующую линию и сохраняем ее
      
      Serial.println(line);
      val=line.toFloat(); //Данные этой линии переводим в нужный тип данных(float) и сохраняем в переменную для данных с БД
    }
  }
  
  if (val>=30){ //Условность которую можете менять как хотите я ее использовал для тестировки получения и обработки данных
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (val<30){
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
