-- ESP8266_DATABASE --

-- DILATACION SUPERFICIAL --

CREATE TABLE `Temperature` (
    idTemperature INT AUTO_INCREMENT PRIMARY KEY,
    `Initial_Temp` DOUBLE NOT NULL,
    `Final_Temp` DOUBLE NOT NULL,
    `Change_Temp` DOUBLE NOT NULL
);

CREATE TABLE `Area` (
  idArea INT AUTO_INCREMENT PRIMARY KEY,
  `Change_Area` DOUBLE NOT NULL,
  `Final_Area` DOUBLE NOT NULL,

    -- Se relaciona la tabla de temperatura con area: Area es el Padre --
    id_Area INT,
    foreign key (id_Area) references Temperature(idTemperature)
);

CREATE TABLE `Humidity` (
  idHumidity INT AUTO_INCREMENT PRIMARY KEY,
  `Humidity` DOUBLE NOT NULL
);

