# ROCKET-MK-1
This is a fixed fin experimental rocket built for the purpose of collecting useful flight data and also showcasing high level engineering skills 

# Project Theory
For this project I will be designing simulating and fabricating a fixed fin rocket from scratch using the rocket motor as the starting point for calculating all other parameteres like the diameter of the main body tube and the nosecone length and gemoetry and the fin geometry 
the rocket motor's impulse also dictates the maximum weight of the rocket as the thrust to weight ratio should be a minimum of 5:1 considering the resistive forces acting uptom the rocket like the drag from the rocket's weight and also the aerodynamic drag which is the factor which we need to optimize our rocket for we need a very aeroynamically optimized body for the rocket to be able to cut through the air smoothly with minimum drag and deviation 
the rocket should launch perfectly vertical and shall not deviate more then 1-5 degrees from the horizontal from the launch rail The rockst's fins should be optimized to suffer from no Aerosynamic fin flutter.
Aerodynamic Fin Flutter is a destructive process in which the rocket's wings bend under stress and strain as they are travelling at very high speed (upwards of Mach 0.5) for this rocket the fins start to resonate because of the external force which the air provides for stabilizing the rocket but in this special case the air starts to resonate the fin and the fin starts to vibrate from it's mean position which and hench resonate which exposes the fin to much more flutter than it can possibly handel and hence breaks apart.
to avoid this we must use a lightweight material with the highest young's modulus which provided maximum stiffness and negligible strain 
Materials such as Fiberglass, carbon fiber, 3D printed CF-Nylong provide high stiffness ideal for optimizing the fins from restraining from fin flutter 

# Starting parameteres 
Now let's start talking about numbers and actual starting parameteres for the rocket

**Rocket Motor**
Now there are many different classes of rockets ranging from class micro and A going through E F G H I J K L and reaching to upwards of AJ
However for model rocketry we generally use from class D to the largest one S 
These rocket motor classes are alphabetical and classified by Magnitude of impulse they can produce

For my Rocket i will be using a F class rocket motor producing a Max Impulse of 67Ns
I will be using the rocketeers F57 motor 
<img width="1134" height="477" alt="image" src="https://github.com/user-attachments/assets/3a54384d-6441-468c-a7a5-e4f99b8cdd96" />
This motor has 
Diameter of 29mm <br>
Weight = 177g (wet mass)<br>
Burn time = 1.14s<br>

This motor's casing is made from aerospace grade Aluminium 
Nozzel is manufactured out of graphite 
and all very high quality materials are used in this entire rocket motor assembly

# Rocket dimensions
Thr rocket's exact dimenstions are yet to be simulated and found out but for now we have these as the starting points
Rocket length = 650 ~ 975mm<br>
Main Body tube length = 455 ~ 650mm<br>
Avaionics bay length = 120 ~ 165mm<br>
Nose cone length 195 ~ 325mm<br>
Nose cone profile = Ogive (3:1)<br>
Outter tube diameter = 65mm<br>
Target liftoff mass = 500~600 grams<br>
Static stability margin = 1~1.5 cal<br>
3-4 Fixed fins - Trapezoid shape <br>

# Mission Objective 
Apogee > 100 Meteres<br>
Mantain Stable vertical flight <br>
All Flight Data logged successfully <br>
Working Telementry<br>
Rocket Recovery <br>

# Work Flow
Firstly the rough design will be simulated in Open rocket and the simulation data will be used for finding the perfect rocket profile values 

Then the entire rocket will be imported inside fusion 360 and the launch mechanism the launch rail and the cross section of the rocket and the fin joint mechanism and then avaionics bay will also be shown in the horizontal cross section of the rocket 

Then i will prototype the avaionics bay on breadboards and design the rough data logging program and logic This will be a time consuming process 

After this i will convert the entire avaionics circitry into a PCB which will be as small as possible and Be mounted vertically inside the Avaionics bay 

then i will also create the remote ignition and most importantly the ground telementry station which will comminucate via LoRa

After that I will work on creating proper joining mechanisms for the rocket and the final circuitry 

Then i will finalize the rocket design and start ordering parts for it's fabrication and assembly 

Then carefully assemble each and every part and test for any errors 

then calculate the Moment of inertia find the actual center of mass and center of pressure 

Simulate and perfect again in Openrocket 

Then create an even more accurate model in matlab simulink 

Test and analyze again

Then a dry run 

The Actual Flight 

# Avionics <br>
I will be using these main sensors for the avaionics (rough idea)<br>
ESP32 S3 Wroom-1<br>
BMI270 - 3 axis acceleration + 3 axis gyroscope <br>
ADXL377 - 3 axis high G accelerometer<br>
Barometric pressure sensor - altitude measurement<br>
DS3231 - Time stamping<br>
Sd card module - data logging <br>
loRa - Telementry <br>
2 Li-ion battries for Power<br>
umbilical cord connector = communication of Remote ignition from ground station to the rocket and the launch rail <br>

# Launch rail<br>
The launch rail will be made out of 2020 aluminium extrusion with arms which will hold the rocket in place (cool factor) and it will use a Rail button<br>

# OpenRocket model 
*1st Iteration estimates*
<img width="1535" height="747" alt="image" src="https://github.com/user-attachments/assets/d6361d3e-151c-41d2-b690-7b0dff556bd2" />
<img width="1458" height="361" alt="image" src="https://github.com/user-attachments/assets/66adf616-3d95-4f15-8c41-bc7ec700e722" />
Apogee = 285m <br>
Max speed = Mach 0.245<br>
Max acceleration = 83.3m/s^2<br>

*2nd Iteration estimates*
<img width="1535" height="818" alt="image" src="https://github.com/user-attachments/assets/a046f596-11e4-47e6-a8c9-81c504ea0a56" />
<img width="1460" height="366" alt="image" src="https://github.com/user-attachments/assets/6867f1f8-61af-4c0f-985b-5459f218ebd5" />
Apogee = 281m<br>
Max speed = Mach 0.240<br>
Max acceleration = 84.6m/s^2 <br>

This version has a more agressive look and also has a much higher stability caliber(2.19Cal) then the last iteration.<br>
I upgraded from a 2020 Aluminium extrusion because a 1010 aluminium extrusion was not very easily available in india.<br>

# Render in fusion360
<img width="1535" height="719" alt="image" src="https://github.com/user-attachments/assets/ebce0365-df30-4aa2-bcb6-fa7f54a24a9a" />
<img width="1535" height="810" alt="image" src="https://github.com/user-attachments/assets/ef4349a2-24e9-40e4-b67f-ece9b9b6fd5a" />
<img width="1535" height="818" alt="image" src="https://github.com/user-attachments/assets/fd2a1c9b-e67b-465d-a0f5-a7bd92a78761" />
<img width="1535" height="713" alt="image" src="https://github.com/user-attachments/assets/ca316ad9-4d0c-4b7e-a811-ed69003d3d6a" />

# Avionics sled V1
<img width="853" height="603" alt="image" src="https://github.com/user-attachments/assets/90640175-1c9b-46cb-a45e-253d5aa3ed5a" />
<img width="318" height="635" alt="image" src="https://github.com/user-attachments/assets/5895ecc1-4c78-444a-b0ae-708cb8f90aed" />
<img width="271" height="598" alt="image" src="https://github.com/user-attachments/assets/3794724a-13ce-4a87-aafa-491093e9436f" />

<img width="1535" height="818" alt="image" src="https://github.com/user-attachments/assets/8c49a133-b037-470f-97e2-0d05c43d383d" />

# How to actually build the rocket 
1. Download this repo on your computer
2. Buy all the materials required for the rocket as listed in the BOM
3. Start by taking the carboard main body tube
4. 3D print the nosecone
5. cut the fins out of balsa wood and make insitions inside of the cardboard bodytube for fitting the fins
6. Also cut out the centering rings from the rocket's main body tube
7. Take wood glue and apply it on the centering rings and then slide then at exact depth as mentioned inside the openrocket rocket's model
8. after the centering rings are applied do the same and glue the fins inisde the rocket's main body tube
9. Take the rocket motor and slide it inside the centering rings from the bottom
10. Take the 3d printed nosecone and see if it fits from the top properly
11. make sure it fits tightly enough that it can slip out with force but not when you're lifting the rocket by holding the nosecone
12. Apply tape around the circumfrence of the nose cone's neck if required to a tighter fit
13. after this you may spray a thin layer of primer on the cardboard tube and then spray paint it black
14. Now comes the Avionics
15. Get the Avionics pcb fabricated
16. Solder all the avionics components as shows in the kicad pcb schematics
17. After getting the pcb ready
18. build the ground station on a perf board or a breadboard
19. power up the pcb and the ground station
20. make sure to connect the LoRa antennas before powering on the pcb else it it may fry itself
21. Upload the codes of ther Avionics sender and ground station recuiever respectively
22. Download Serial Studios and open the serial studio profile provided inside the repo
23. Connect the ground station and you should see the serial studio dashboard working
24. After that 3D print the Avionics sled for the Avionics PCB
25. Connect the avionics on the sled via proper M3 screws
26. TAke the sled and slide it inside the rocket's main body tube and then close the nosecone
27. Make sure that the rocket Telementry is working properly
28. Drill a small hole isnide the cardboard tube at the angle bisector between two of the fur fins and connect the rail button
29. Take the 6 Feet 2020 Aluminium extrusion
30. Put it firmly on a tripod stand or a dedicated Launch pad for a model rocket
31. Get the Ignition reciever PCB fabriacted and solder all the components
32. 3D print the acse for the PCB
33. Connecte a 12V Lead acid battery to the ignition bat connector also power the ignition reciever staion with 5V from a smaller battery
34. Connect the igniton plug inside the rocket's motor
35. Now staand atleast 10 meters away from the launch site (make sure you have all the certifications reqired to launch a model rocket according to your local jurisdiction)
36. Load up the Serial studio dashboard
37. Press the launch button o the ground station reciever
38. Rocket launches (hopefully)

# BOM 


| Category | Item Description | Manufacturer / Serial No. / Part Number | Qty | Est. Unit Price (USD) | Primary Vendor / Website |
| :--- | :--- | :--- | :---: | :---: | :--- |
| **Avionics & Processing** | ESP32-S3 Dev Board | Espressif / ESP32-S3-DevKitC-1 | 2 | \$6.50 | [DigiKey](https://www.digikey.com) |
| **Avionics & Processing** | LoRa Transceiver Module (915MHz/433MHz) | HopeRF / RFM95W-915S2 | 2 | \$4.80 | [Adafruit](https://www.adafruit.com) |
| **Avionics & Processing** | 50Ω SMA Male Rubber Duck Antenna | Generic / ANT-SMA-915-01 | 2 | \$2.00 | [Amazon](https://www.amazon.com) |
| **Sensors** | 6-DOF IMU (Gyroscope + Accelerometer) | Bosch / BMI270-BRK | 1 | \$5.50 | [Pimoroni](https://shop.pimoroni.com) |
| **Sensors** | High-G Accelerometer Module | Analog Devices / ADXL345-BRK | 1 | \$4.20 | [SparkFun](https://www.sparkfun.com) |
| **Sensors** | Barometric Pressure & Altitude Sensor | Bosch / BMP280-BRK | 1 | \$3.50 | [Adafruit](https://www.adafruit.com) |
| **Sensors** | 3-Axis Digital Compass / Magnetometer | QST / QMC5883L-MOD | 1 | \$2.50 | [AliExpress](https://www.aliexpress.com) |
| **Sensors** | GPS Receiver Module w/ Ceramic Antenna | u-blox / NEO-6M-0-001 | 1 | \$11.00 | [Amazon](https://www.amazon.com) |
| **Sensors** | Real-Time Clock (RTC) Module | Maxim / DS3231-RTC-MOD | 1 | \$2.80 | [Adafruit](https://www.adafruit.com) |
| **Data & Interfaces** | MicroSD Card Breakout Module (SPI) | Adafruit / ID-254 | 1 | \$1.80 | [Adafruit](https://www.adafruit.com) |
| **Data & Interfaces** | Class 10 MicroSD Card (16GB) | SanDisk / SDSQUNC-016G-GN6MA | 1 | \$7.00 | [Amazon](https://www.amazon.com) |
| **Data & Interfaces** | USB-C High-Speed Data Cable (1m) | Anker / A81E1011 | 2 | \$3.00 | [Monoprice](https://www.monoprice.com) |
| **Power & Passives** | 3.7V 1S LiPo Battery (1000mAh 25C) | Turnigy / N1000.1S.25 | 1 | \$6.50 | [HobbyKing](https://hobbyking.com) |
| **Power & Passives** | TP4056 LiPo Charge/Protection Module | Micro-USB TP4056-PROT | 1 | \$0.80 | [AliExpress](https://www.aliexpress.com) |
| **Power & Passives** | 3.3V Low Dropout LDO Regulator | Advanced Monolithic / AMS1117-3.3 | 2 | \$0.40 | [DigiKey](https://www.digikey.com) |
| **Power & Passives** | Ceramic Capacitor 0.1uF 50V (0805/DIP) | KEMET / C0805C104K5RACTU | 10 | \$0.05 | [Mouser](https://www.mouser.com) |
| **Power & Passives** | Tantalum Capacitor 10uF 16V | AVX / TAJB106K016RNJ | 4 | \$0.25 | [Mouser](https://www.mouser.com) |
| **Power & Passives** | Resistor Kit (2.2kΩ, 4.7kΩ, 10kΩ, 220Ω) | Yageo / MFR-25FRF52 Series | 1 set | \$5.00 | [Amazon](https://www.amazon.com) |
| **Airframe & Hardware** | Spiral Wound Cardboard Tube (62mm ID) | Apogee Components / Tubing-62mm | 1m | \$12.00 | [Apogee Components](https://www.apogeerockets.com) |
| **Airframe & Hardware** | Airframe Coupler Tube (62mm ID Fit) | Apogee Components / Coupler-62mm | 1 | \$5.00 | [Apogee Components](https://www.apogeerockets.com) |
| **Airframe & Hardware** | PETG Filament 1.75mm (Sled Printing) | Prusametrix / PETG-JET-BLACK | 1 | \$22.00 | [Prusa Research](https://www.prusa3d.com) |
| **Airframe & Hardware** | M4 Threaded Rods Stainless Steel (300mm) | McMaster-Carr / 98846A029 | 2 | \$2.50 | [McMaster-Carr](https://www.mcmaster.com) |
| **Airframe & Hardware** | M3 x 5mm x 4.2mm Brass Heat-Set Inserts | McMaster-Carr / 94180A331 | 8 | \$0.20 | [McMaster-Carr](https://www.mcmaster.com) |
| **Airframe & Hardware** | Birch Plywood Centering Rings (62mm OD) | Custom Laser / CR-62-3MM | 3 | \$2.00 | Local Laser Cutting |
| **GCS & Countdown** | Heavy Duty Toggle Switch w/ Safety Cover | Gardner Bender / GSW-11 | 5 | \$1.50 | [Amazon](https://www.amazon.com) |
| **GCS & Countdown** | Momentary Red E-Stop Push Button Switch | Ideal / Push-Red-Mushroom-22mm | 1 | \$3.50 | [AliExpress](https://www.aliexpress.com) |
| **GCS & Countdown** | PAM8403 Audio Amplifier Module | Mini PAM8403-2CH-3W | 1 | \$1.20 | [AliExpress](https://www.aliexpress.com) |
| **GCS & Countdown** | 8Ω 2W Mini Speaker Module | CUI Devices / CMS-151185-078SP | 1 | \$1.50 | [DigiKey](https://www.digikey.com) |
| **GCS & Countdown** | 1-Channel 5V Optocoupler Relay Module | Songle / SRD-05VDC-SL-C | 1 | \$1.00 | [Amazon](https://www.amazon.com) |

*Total Estimated Project Cost: **~$135.00 USD***


  
