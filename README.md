# BE C++ : Two robotic arms 

The project consists of two robotic arms. When one of them is manually moved, the other will replicate the same movements.

### How to compile and execute
The project uses two ESP8266's, and has therefore two main functions to execute.
One of the microcontrollers is the client, and its folder is called Main_Client. Its main file is called Main_Client.ino. 
The other microcontrollers is the server, and its folder is called Main_Server. Its main file is called Main_Server.ino.
The other files in the folders are the modules, with the classes, attributes and methods needed for the system to work.
There are two zip files in the Main_Client folder, and are libraries needed for an ADC converter. 

So we have two seperate Arduino IDE windows (one for each folder), connect to the different microcontrollers. Then build, compile and execute the main files for the microcontroller to be up and running.

### How to interact with the program
The system consists of two seperate robotic arms, one is the client and one is the server.
If the clients arm is moved, the server arm will replicate the movements. 
The client is connected to three potentiometers which measures the angles of their movements.
The client sends these angles to the server via UDP. 
The server is connected to three servo motors, and will command the motors to replicate the angles it has received from the client.
To configure the network of the client it is only necessary to change the parameters of the constructor of Client-Class in Main_Client.ino.
The I2C is configured to work in the pins D1-CLC and D2-SDA.
To configure the network of the server it is only necessary to change the parameters of the constructor of Server-Class in Main_Server.ino.
To change the pins to control the servo motor it is necessary to change the #define pin_servo in Server.cpp.
