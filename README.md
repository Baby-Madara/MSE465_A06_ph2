# Bluetooth-Controlled car
A project for "Microprocessors & Microcontrollers" course in MSA university - Faculty of Engineering

## AUTHORS

|*Authors*          |Group|
|-------------------|-----|
| Ahmed Farahat     | C   |
| Yasmin Ibrahim    | B   |
| Mahmoud Hashim    | B   |

|*under supervision of*   |||
|-------------------|-----|-|
|Dr. |Ahmed Emam Newir    ||
|Eng.|Nada Abdellah       ||
---

## Used MCU

ATMega328p (inside arduino Nano board)

## IDE

VSCode using platformIO extension

## Connections

```
                  
                      ______|---|______
             |       |D13   |___|   D12|       |
             |       |3v3           D11|       |
             |       |AREF          D10|       |
          LL |  PC0  |A0             D9|  PB1  | MAen
          LR |  PC1  |A1             D8|  PB0  | MA1
             |  PC2  |A2   arduino   D7|  PD7  | MA2
             |  PC3  |A3     nano    D6|  PD6  | MB3
   ENCODER_R |  PC4  |A4     OBD     D5|  PD5  | MB4
   ENCODER_L |  PC5  |A5   (is in)   D4|  PD4  | MBen
             |       |A6             D3|  PD3  |  BTTx brown myRX(old)
             |       |A7 ATMega328p  D2|  PD2  |  BTRx black myTX(old)
             |       |5V (is inMdle)GND|       |
             |       |RST           RST|       |
             |       |GND   * * *   RX0|  PD0  |  BTTx brown (new)
             |       |VIN   * * *   TX1|  PD1  |  BTRx black (new)
                     |_________________|
               (hardware conection is outside)                         
                  
```

***arduino equivalent code is in file ```../test/arduinoSource.txt```