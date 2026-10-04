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
<img width="1535" height="718" alt="image" src="https://github.com/user-attachments/assets/a41f3ce7-8f09-4d2c-82ff-67c7a0ad01c4" />
<img width="1535" height="713" alt="image" src="https://github.com/user-attachments/assets/ca316ad9-4d0c-4b7e-a811-ed69003d3d6a" />






  
