<?php
class dht11{ //Объект с названием dht11
 public $link='';  //Это надо, увы не смогу пояснить за это, наверное для связи между функциями
 function __construct($temperature, $humidity){ //функция с двумя переменными как параметры
  $this->connect();   //Пойнтер на функцию нужную для соединения
  $this->storeInDB($temperature, $humidity); //Пойнтер на функцию для сохранения тех переменных
 }
 
 function connect(){ //Функция для соединения 
  $this->link = mysqli_connect('*****','*****','*****') or die('Cannot connect to the DB'); //Здесь указываем хост, имя пользователя и пароль нашей БД(Такто мы просто соединяемся)
  mysqli_select_db($this->link,'*****') or die('Cannot select the DB'); //Здесь указываем название БД к которой надо соединиться 
 }
 
 function storeInDB($temperature, $humidity){ //Функция для сохранения данных с переменных
  $query = "insert into sensortable set humidity='".$humidity."', temperature='".$temperature."'"; //SQL запрос связанный с нашими переменными, также здесь указываем название таблицы и ее элементов
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query); //В новой переменной храним результат запроса ну и выполняем этот самый запрос
 }
 
}
//А теперь перейдем к основному коду
if($_GET['temperature'] != '' and  $_GET['humidity'] != ''){ //Если значения в запросе не пустые 
 $dht11=new dht11($_GET['temperature'],$_GET['humidity']); //Создаем наш объект беря данные с запроса
}


?>
