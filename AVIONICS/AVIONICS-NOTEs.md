# Avionics
For rocket MK-1 

# Objective 
To record all flight data for rocket MK-1 and store it for future simulation use 
All data such as Rotation in all three axes, acceleration in all three axes, Using a magnetometer additionall to find Direction (North Suoth East West)
then we will be using a GPS to track the lockation of the rocket and all the avaionics will communicate to the ground station via LoRa transciever<br>

**Specifications**
I will be using BMI270 as the three axis accelerometer and the 3 axis gyroscope sensor mainly the gyrospcoe part the accelerometer is seconart because i will be using a different more precise sensor for finding out the acceleration 

ADXL345 is the 3 axis high G accelerometer which can detect acceleration with a range of plus minus 200Gs for reference my rocket is going to pull max to max 12Gs of acceleration
After this i will be integrating a pressure sensor which will be used to calculate the altitude of the rocket and the also help to find the point it time when it will have reached the apogee
Then i will be using a DS3231 RTC module which will give me accurate time stamps which is needed to for proper data logging 
Then comes the sd card module whioch will be holding the SD card inside the connector firmly so it does not bulge during the launch also i will be using a Push-slot connector to ensure it cannot slop off accidnetally
Then i will be using a LoRa module to comminucate with the ground control station telementry LoRa as the name suggests stands for Long Range and it is ideal for my telementry because it will precisly send me the data though may be at lower speeds by it has a very long range which is amsolutely must for my rocket 
And how can we forget the GPS moudle We will be using the U-Block NEO GPS moule

# Telementry 
we will be recieveing all the flight data from the fl;ight live to our ground telementry via LoRa where the ground telementry station will send all the data to our laptop Via UART comminucation protocol and the laptop will be running python to display all the information in forms of graphs and Text 

We will be also having a comminucation unit at the launch pad There MAY be a umbibical connector from the rocket to the launch pad which will will help the gorund station to control the rocket via wired telementry for the begining and also help the computer in determinig if the rockt has lifted off 
because first of all if we try to determine liftoff from the accelerometer only then there might be a change of error so to imcrease the redudancy of the system we will be adding another success point 
because if we fail to determine if the rocket has lifed off from the rail or not we The program will not be able to initialize and the data loggin WILL NOT start

# Ground station assembly 
The ground station will be preferrably inisde a black suitcase 
It will consist of 5 buttons which will be for T-5 to T-0 
and a big red button for launch 
without all the 5 switched T-5 to T-0 bring switched to on position the rocket will not lift off even on pessing the red button 
T-5 through T-0 buttons also have purposes 
T-5 will let the launch station's base light go red 
T-4 will let the telementry on the laptop to begin 
T-3 will let the speakers inside the ground telementry start beeping as indication of close liftoff
T-2 will make the launch rail's arm's divert from the rocket 
T-1 will start the internal telemntry of the rocket 
T-0 will be paired with the big red button for Liftoff 

Anyways now from the cool part to the technical part
The ground station will have 2 modes of communication with the rocket 1St via the umbibilical cord connector (rocket+launchrail) 2nd Via the LoRa (only rocket)
The ground station will then have as i said flip switches
The ground station will have the rocket motor igniter connected via the umbibical cord connector 

**The ground station will also have a sound system**
okay this is a cool fun part which will make the worst case scenario appear dead seriouly cool 
let me explain, So like as in aeroplanes there is a warning syste for example "Whoop Whoop Pull Up" when the terrain is approaching and the airplane is rapidly descending 
and also like "Bank angle bank angle" when the airplane tries to turn at a greater angle that the angle of repose it posseses and iits starts to rapidly fall 

So basically if the rocket goes decellerating downwards at a much higher rate like with the parachute it will have a descend velocity of about 7.74 m/s and incase of a faliure in deployment of the parachute the rocket will go well above 40 to 50 to even 60 m/s descend velocity 
in this case the Avionics will flag this as a parachute depoyment failure which will cause alrma to goo off at the ground station!!! like "Whoop Whoop Pull Up Terrain Terrain"
Cool isn't it making a bad case become a test for another part of the rocket 

# Prototyping 
SO!! for the prototyping phase i will first of all set up sensors on a breadboard connect them to an esp32 and code them to initialization first once i've done this with each sensor i want to use then i make the mock ground station telementry 
After this is finished i will move on to the actual logic developement for the rocket 

First up,
I started by researching about the specs of different components in detail and then adding them one by one in my code 
Writing the code will not be tracked by lapse but rather hackatime so first i will be starting by searching how does the code work 

First of all i set up the DHT11 code to read the temperature of the air at a specific altitude it may not be very accurate but we shall still give it a shot so there are two main variables for this purpose first one is "t" which basically stores the temperature data reading in binary coming from the sensor and then we compute the temperature in celcius using the function dht>computeHeatIndex(); which converts the values of binary temperature signals into proper celcius units 
the final temp reading is stored inside the variable "T" 

after writing this bit of code i started to research about how to set up the U-BLOC-NEO-c GPS Module 
The code snipped for the GPS module uses the TinyGPS library it starts by adding the tinygps library and then initializing the pins for the RX and TX of the U-BLOX 6M GPS module s the module uss I2C comminucation protoco we initialize it in the void setup and define it's address after that inside the void loop we use various functions inside the TinyGPS library like gps.location.lat(); for latitude or gps.location.lng(); for the longitude gps.speed.kmph for speed of the Rocket in km/h etc etc 
we will not be using the values from this esnor to determine the speed of the rocket as this gps module has a much higher latency than the other ADXL module we're using to find the acceleration at a smaple speed of 100Hz we may use this for sensor fusion if the values from this GPS moudle turn out to be accurate but most probably this will only be used as a location determining system of the recovery part of the rocket.

Finally i wrote all the functions required to manipulate files inside a sd card module 
Then i added the code to read the values of pressure from the BMP280 
Then i finally connected each the LoRa module with the esp32 and then after wiring all of this up it looked like this 
<img width="247" height="142" alt="image" src="https://github.com/user-attachments/assets/b5043ece-0fee-4026-876a-ab7869f4eb3b" />
Moments like this remind me why pcbs are much better 
no-1 this board is too big to fix inside a cylendrical tube enclosure of 65mm by 50mm
no-2 one loose wire and game over
no-3 the compoenents can be easily be brought nearer to reduce EMF noise and also increase signal accuracy

Now if we talk about the code i tried to keep it very organized and clean and yes i used AI but not to a bigger extend but mainly to debug the code i wrote and to debug it mainly.
