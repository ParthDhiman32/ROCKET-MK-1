# PCB DEVLOG
Here i will start writing everythgin related to the creation of my Avionic's pcb 
So i will be having a hybrid approach for my PCB
Which means i will use some modules in their pcb form like i just slide the connectes ontu the pcb 
For some other parts i will be desoldering and stripping away the main IC from the board and then soldering it again ontu my pcb 
for faster communication and better stability and so it can survivie the very high acceleration of the rocket 

I will have the components in this format 
ESP32 S3 WROOM-1 module - this will be a bare IC 
LORA RA-02 will be a Module stripped from the header board 
BMP280 - Bare IC stripped from the module 
MPU9250 - will be a fully intact header board mounted on the PCB 
GPS module - Fully intach module mounted very closely to the board 
DHT11 - this module will not be used as it is extremely show speed of 1Hz and will provide no useful data
SD Card module will be in Bare form 
RTC Module - will be used as it is soldered closelt to the board

All these modules will soldered onti to PCB and also I will use M2 and M3 screws to tighten them down whereever needed 

The pcb will be a size of aprox 35mm by 100mm 
It will be mounted on a 3D printed PCB Sled 

## Powering the pcb 
To Power the pcb i will be using a 500Mah batter with a ME6211C33 IC which is a linear dropout voltage regulator which will fix the output to 3.3Volts when the bettery will be fully charge 

