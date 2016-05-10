# RGB_Temperature_Sensor
Script that uses an Arduino board to collect temperature data and show the changes on an RGB LED.

// install the required stuff 
sudo apt-get install picocom 
sudo apt-get install python-pip 
pip install ino 

// create a template project 
mkdir beep 
cd beep 
ino init -t blink 

// edit the code 
vim src/sketch.ino 

// compile 
ino build 

// send to arduino 
ino upload
