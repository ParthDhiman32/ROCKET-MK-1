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

# Debugging 
So we ave written our prototype code tro check the sensors fully
What we need to do is check if each and every sensor works or not
Firstly this is the sample code 

"
#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <SD.h>
#include <DHT.h>
#include <TinyGPS++.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define RXD2 16 
#define TXD2 17 
#define GPS_BAUD 9600 
#define DHTPIN 4 
#define DHTTYPE DHT11  
#define BMP280_ADDRESS 0x76 

#define SD_CS_PIN 15
#define ss 5
#define rst 14
#define dio0 2

int counter = 0;

Adafruit_BMP280 bmp;
Adafruit_MPU6050 mpu;
TinyGPSPlus gps;
HardwareSerial gpsSerial(2);
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastLogTime = 0;
const unsigned long LOG_INTERVAL = 1000; 
const char* logFile = "/flight_log.csv";

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
  dht.begin();

  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    delay(500);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("Avionics to Ground Telemetry Connection Established");
  
  if (!bmp.begin(BMP280_ADDRESS)) {
    Serial.println("BMP280 Initialization Failed!");
  }

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050!");
  } else {
    mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
    mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
  }

  if (SD.begin(SD_CS_PIN)) {
    File file = SD.open(logFile, FILE_WRITE);
    if (file) {
      file.println("PacketID,UTC,Lat,Lng,Alt_GPS,Speed,Sats,Temp_DHT,Hum,Temp_BMP,Press,Alt_BMP,AccX,AccY,AccZ,GyroX,GyroY,GyroZ");
      file.close();
    }
  } else {
    Serial.println("SD Card Initialization Failed!");
  }
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (millis() - lastLogTime >= LOG_INTERVAL) {
    lastLogTime = millis();

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);


    float t_dht = dht.readTemperature();
    float h = dht.readHumidity();
    float t_bmp = bmp.readTemperature();
    float p_bmp = bmp.readPressure();
    float a_bmp = bmp.readAltitude(1013.25);
    double lat = gps.location.lat();
    double lng = gps.location.lng();
    double alt_gps = gps.altitude.meters();
    double speed = gps.speed.kmph();
    uint32_t sats = gps.satellites.value();
    
    float mpu_ax = a.acceleration.x;
    float mpu_ay = a.acceleration.y;
    float mpu_az = a.acceleration.z;
    float mpu_gx = g.gyro.x;
    float mpu_gy = g.gyro.y;
    float mpu_gz = g.gyro.z;

    String utcStr = "NO_FIX";
    if (gps.time.isValid()) {
      char timeBuf[10];
      snprintf(timeBuf, sizeof(timeBuf), "%02d:%02d:%02d", gps.time.hour(), gps.time.minute(), gps.time.second());
      utcStr = String(timeBuf);
    }

    String dataLine = String(counter) + ",";
    dataLine += utcStr + ",";
    dataLine += String(lat, 6) + ",";
    dataLine += String(lng, 6) + ",";
    dataLine += String(alt_gps, 1) + ",";
    dataLine += String(speed, 1) + ",";
    dataLine += String(sats) + ",";
    dataLine += String(t_dht, 1) + ",";
    dataLine += String(h, 1) + ",";
    dataLine += String(t_bmp, 2) + ",";
    dataLine += String(p_bmp, 2) + ",";
    dataLine += String(a_bmp, 2) + ",";
    dataLine += String(mpu_ax, 2) + ",";
    dataLine += String(mpu_ay, 2) + ",";
    dataLine += String(mpu_az, 2) + ",";
    dataLine += String(mpu_gx, 2) + ",";
    dataLine += String(mpu_gy, 2) + ",";
    dataLine += String(mpu_gz, 2);

    Serial.println(dataLine);

    File file = SD.open(logFile, FILE_APPEND);
    if (file) {
      file.println(dataLine);
      file.close();
    }

    LoRa.beginPacket();
    LoRa.println(dataLine);
    LoRa.endPacket();

    counter++;
  }
}
" 
This code gives us this output 
"

229,00:00:00,0.000000,0.000000,0.0,0.0,0,30.6,95.0,31.23,98840.34,208.95,0.00,-91.79,16.55,-1.30,0.00,0.00
230,00:00:00,0.000000,0.000000,0.0,0.0,0,30.4,95.0,31.23,98844.50,208.60,0.00,-91.79,16.55,-1.30,0.00,0.00
231,00:00:00,0.000000,0.000000,0.0,0.0,0,30.4,95.0,31.23,98841.25,208.87,0.00,0.00,0.00,0.00,0.00,0.00
232,00:00:00,0.000000,0.000000,0.0,0.0,0,30.6,95.0,31.23,98843.00,208.72,0.00,89.21,-8.28,0.00,0.00,0.00
233,00:00:00,0.000000,0.000000,0.0,0.0,0,30.6,95.0,31.23,98842.00,208.81,0.00,0.00,0.00,0.00,0.00,0.00
"
our first value is around 229 to 233 which is basically the dataline as a timestamping method to not timestamp the exact time but later change it by checking the exact time the code begun at 

secondly we get 00:00:00 which is The RTC sensor which should output the time in a HH:MM:SS format in UTC (co-ordinated universal time) the Clock is not yet callibrated that's why we get this outpt so first we start by fixing this clock by uploading a code which sets it's exact time 
the clock shall not drift even after it will be powered off because of it' onbard CoinCell battery 

I used the library RTCds1302 to set the rtc clock's time
after that i found out conflicting pin definitions in the RTC module and LoRa both were using pin 5 as their Chip enable pin 

The main issue was that of MPU6050 the one i was using had a address of 0x70 instead of 0x68 which triggered it to abort the initilization and then what i did was change the code in the WHO_AM_I register to start the sensor even when the code isn't exactly 0x68 

Then i set the RTC time and date and finally all the sensors for the avionics were working 
Aftert this i need to start working on the ground station

# GROUND STATION 
So for the ground station i have a very cool idea that is No-1 i need an esp32 and then the LoRa RA-02 ofc along with a small speaker that i got 

Now first of all my goal is to set up the gorund station telem,netry tyo establish that the data is being transferred smoothly between the two station and then i will be working on increasing the speed of data logging in the flight controller and the speed of telementry to it's absoulte limits. then i need the speaker to be used during the following times no-1 is when the system will be started up and initialized that is iit till speak MPu6050 init BMP280 init LoRa init etc etc and then i will make it also have some emergency warnings like if the altitude decreases very suddenly the speaker will play "Whoop Whoop pull up" warning as a i mean nice easter egg and also terrain terrain if the parachute deployment fails and all

After this sytem works i will start on making the communication between this ground station and my PC set up because i need the Cool ass python graphs and Mission Control Vibes 

After this entire ground station telementry and Avionics work i will make a seperate subsystem for remote ignition of the rocket motor i need to keep this system as an external failproof system which wil only detect the signals from the ground station like 1 and 0 to ignite the fuse for the rocket motor usinf an external 12V battery which is capable of providing Very high current to set fire to the nichrome wire  


