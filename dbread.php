<?php



    $host = "*****";	//Указываем хост
    $dbname = "*****";              // Название БД
    $username = "*****";		// Пользователя БД
    $password = "*****";	        // Пароль БД


// Establish connection to MySQL database
$conn = new mysqli($host, $username, $password, $dbname);


// Check if connection established successfully
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}


// Select values from MySQL database table

$sql = "SELECT temperature FROM sensortable ORDER BY id DESC LIMIT 1";  // Меняете название таблицы и поля тут

$result = $conn->query($sql);   //Делаем наш sql запрос в новой переменной



if ($result->num_rows > 0) { //Идем до конца результата запроса (А по запросу мы берем именно последнюю строку)

	if($row = $result->fetch_assoc()){  //Если в строке есть результат
    		echo  "sensor:\n" .$row["temperature"];  //То отправить слово "sensor:" потом новый абзац и отправить ячейку"temperature"
	}
}
 else {
    echo "0 results";
}

$conn->close(); //Закрываем соединение



?>
