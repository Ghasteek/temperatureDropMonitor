# Temperature Drop Monitor
Little Arduino application to monitor drops of temperature with sound notification. 
![Wirring](/wirring.png)

There are two buttons to comunicate with this little device. 
  * The left one will set current temperature as reference temperature. When actual temperature drops bellow threshold (more info futher in text), Arduino will start buzzing with help of NPN tranzistor and PIEZO buzzer. 
  * The right one will reset actual reference temperature and set up the threshold according to DIPSWITCH settings.
  
Dipswitch is for, as I already mentioned, setting threshold of how low can temperature drop, before signalization starts. 
  * Dip 1 - 2°C
  * Dip 2 - 3°C
  * Dip 3 - 4°C
  * Dip 4 - 5°C
  * No dip - 0°C

One and only LED diode is STATUS. When reference temperature is set, and device is checking for temperature drop, it glows green. If you want to stop checking for drops, you can push RESET button, which resets reference temperature and stops checking for drops. This will also turn off STATUS led. 
