<?php
//PAGINA WEB BACKEND --> http://localhost/PHP_TO_MYSQL/index.php?temp=20&temp2=30&hum=70

//Variables utilizadas
$Change_Temp = 0;

$Initial_Area = 400;
$coefficient_of_expansion = 0.000024;

$Change_Area = 0;
$Final_Area = 0;

//Obtencion de los datos del sensor
$Initial_Temp = $_GET['temp'];
$Final_Temp = $_GET['temp2'];
$humidity = $_GET['hum'];



//Conexion con el servidor
echo "La temperatura inicial es: ".$Initial_Temp." <br>La temperatura final es: ".$Final_Temp." <br>La humedad es: ".$humidity;

$user = "root";
$password = "";
$server = "localhost";
$database = "ESP8266_DATABASE";

$conexion = mysqli_connect( $server, $user, "" ) or die ("No se ha podido conectar al server de Base de datos");

$db = mysqli_select_db( $conexion, $database ) or die ( "No se ha podido seleccionar la base de datos" );



//Operaciones refenrentes a la dilatacion superficial

//ΔT = Af - Ai
$Change_Temp = $Final_Temp - $Initial_Temp;

//Af  = Ai .(1 + β . ΔT)
$Final_Area = $Initial_Area * (1 + 2 * $coefficient_of_expansion * $Change_Temp); 

//ΔA = Af - Ai
$Change_Area = $Final_Area - $Initial_Area;



//Insercion de datos en mysql mediante phpmyadmin 

$consulta = "INSERT INTO temperature (Initial_Temp,Final_Temp,Change_Temp) VALUES (".$Initial_Temp.", ".$Final_Temp.", ".$Change_Temp.")";
$resultado = mysqli_query( $conexion, $consulta );

$consulta = "INSERT INTO area (Change_Area,Final_Area) VALUES (".$Change_Area.", ".$Final_Area.")";
$resultado = mysqli_query( $conexion, $consulta );

$consulta = "INSERT INTO humidity (Humidity) VALUES (".$humidity.")";
$resultado = mysqli_query( $conexion, $consulta );

?>