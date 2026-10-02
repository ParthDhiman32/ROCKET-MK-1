# SIMULATION-2
**Parameteres**
Nose cone shape changed from Ogive to Haack series with shape parameter 0 Von Kármán profile<br>
Noise cone length increased from 150mm to 250mm for shifting COM higher and also improving stability caliber<br>
Nose cone wall thickness decreased froim 2mm to 1.6mm to reduce weight and hence reduce drag <br>
Nose cone profile set to Smooth paint <br>
<img width="1503" height="480" alt="image" src="https://github.com/user-attachments/assets/c1e2c949-7d27-4cf3-876e-828da91fce6f" />

Fin Set Root chod increased from 110mm to 120mm<br>
Fin Set Tip Chord reduced from 45mm to 20mm<br>
Fin Set height increased from 50mm to 65mm<br>
Fin Set sweep angle increased from 47.7 to 64 degrees<br>
<img width="1143" height="658" alt="image" src="https://github.com/user-attachments/assets/4a91dc63-9958-42c8-a809-067c642d0c53" />

## FLIGHT PERFORMANCE CHANGES WRT ORIGINAL PARAMETERES
Overall length increased from 750mm  to 883mm<br>
Stability margin increased from 1.58 Cal to 2.19cal <br>
Simulated apogee increased from 293m to 295m  <br>
Max velocity decreased from 85.5 to 82.1 m/s (Mach 0.242)<br>
Max acceleration decreased from 88.6 to 85.5 m/s<br>

# BEFORE 
<img width="1470" height="370" alt="image" src="https://github.com/user-attachments/assets/65c11134-f985-4a4d-bce7-4df6bd76648a" />

# AFTER
<img width="1462" height="368" alt="image" src="https://github.com/user-attachments/assets/5659bc61-967f-4ecb-99e9-361441327b21" />

The point of making these changes was to increase the stability caliber of the rocket whilist also giving it a more agressive look <br>

# MASS SENSITIVITY 
Original wet mass = 735g<br>

**Case-1**
10% lesser mass = 661.5g<br>
Apogee = 339m<br>
Max Velocity = 92.2 m/s<br>
Max acceleration = 95.7 m/s^2<br>
Stability = 2.25 Cal <br>

**Case-2**
5% lesser mass = 698g<br>
Apogee = 316m<br>
Max velocity = 86.8 m/s<br>
Max acceleration = 90.4 m/s^2<br>
Stability = 2.22 Cal <br>

**Case-3**
Nominal mass = 296m<br>
Max Velocity = 82.1 m/s<br>
Max acceleration = 85.5 m/s^2<br>
Stability = 2.2 Cal<br>

**Case-4**
5% more mass = 771g<br>
Apogee = 275m<br>
Max Velocity = 77.6 m/s<br>
Max acceleration = 81.1 m/s^2<br>
Stability = 2.18 Cal <br>

**Case-5**
10% more mass = 808g<br>
Apogee = 256m<br>
Max velocity = 73.6 m/s<br>
Max acceleration = 77.1 m/s<br>
Stability = 2.15 Cal<br>

## GRAPHED DATA
<img width="938" height="474" alt="image" src="https://github.com/user-attachments/assets/eeca8246-ae69-4a80-920e-aebcc3b09cab" />
<img width="939" height="469" alt="image" src="https://github.com/user-attachments/assets/c668d4c1-0516-489a-a928-a9394efea229" />
<img width="955" height="481" alt="image" src="https://github.com/user-attachments/assets/b10aff41-893c-434e-932a-1e443810f51c" />
<img width="958" height="498" alt="image" src="https://github.com/user-attachments/assets/cbb3a809-8fcf-4fe4-b5c7-219a5345581e" />

## Wind sensitivity 
**case-1**
Windspeed = 0 m/s<br>
Apogee = 297m<br>
Max velocity = 82 m/s<br>
Max acceleration = 85.5 m/s^2<br>
Stability = 2.2 Cal <br>
Velocity off rod = 15.2 m/s
Optimim delay = 6.89 seconds<br>
Time to apogee = 14s<br>
Flight time = 37.9s<br>
Ground hit velocity = 16.1 m/s<br>

**Case-2**
Windspeed = 2 m/s<br>
Apogee = 296m<br>
Max velocity = 82.1 m/s<br>
Max acceleration = 85.5 m/s^2<br>
Stability = 2.2 Cal <br>
Velocity off rod = 15.2 m/s<br>
Optimum delay =  6.88s<br>
Time to apogee = 14s<br>
Flight time = 22.7s<br>
Ground hit velocity = 64.8m/s<br>

**Case-3**
Windspeed = 4 m/s<br>
Apogee = 289m<br>
Max velocity = 81.7 m/s<br>
Max acceleration = 85.6 m/s^2<br>
Stability = 2.2 Cal<br>
Velocity off rod = 15.2 m/s<br>
Optimum delay = 6.79s <br>
Time to apogee = 13.9s<br>
Flight time = 22.1s<br>
Ground hit velocity = 64.5 m/s<br>

**Case-4**
Windspeed = 6 m/s <br>
Apogee = 282m<br>
Max velocity = 81.3 m/s<br>
Max acceleration = 85.6 m/s^2<br>
Velocity off rod = 15.2 m/s<br>
Optimum delay = 6.69 s<br>
Time to apogee = 13.8 s<br>
Flight time = 21.8 s<br>
Ground hit velocity = 63.7 m/s <br>

## OBSERVATIONS 
Apogee decreases 2.6m every 1 m/s increase in wind velocity <br>
Velocity is not affected much by wind velocity (although weathercoking may occur because of higher Stability caliber)<br>
Max acceleration is almost insensetive to wind speed<br>
Stability caliber is constant because it does not directly depend on wind velocity but rather the change in wind velocity may produce a change in the center of pressure which may affect Stability Caliber<br>
Velocity off rod is not affected by wind velocity <br>
Optional delay decreases by 2.9% for every 1 m/s increase in wind velocity <br>
Time to apogee decreases almost by 0.2s for every 1 m/s increase in wind velocity <br>

## GRAPHED DATA 
<img width="1260" height="810" alt="image" src="https://github.com/user-attachments/assets/9dca0b52-305e-4c61-b869-b7425360359b" />
<img width="1260" height="810" alt="image" src="https://github.com/user-attachments/assets/ef7cc6ab-1339-4755-9e5f-80802fae4e58" />
<img width="1260" height="810" alt="image" src="https://github.com/user-attachments/assets/8be6c224-8582-40b3-bd49-27faa8853a09" />
<img width="1260" height="810" alt="image" src="https://github.com/user-attachments/assets/88b67a5e-1165-4d6c-a31b-bc7523572e85" />



