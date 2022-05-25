## OV-7670 Double camera

The goal of this project was to create stereoscopic camera. In this project STM32F411VET6U microcontroller and 2 OV-7670 cameras were used.

## About microcontroller

Usually for image transfer for microcontrollers DCMI (Digital Camera Interface) is one of most user-friendly methods, but it does not work for 2 cameras. That's why STM32F411VET6U was chosen with it's DMA (Direct Memory Access). DMA works pararelly to main loop of program (interrupts cannot read data flowing continuously). For DMA to work it needs to be triggered, ex. by timer. STM32F411VET6U has 2 DMAs - DMA1 and DMA2. DMA1 allows data transfers _peripheral to memory_ and _memory to peripheral_, DMA2 allows also _memory to memory_. DMAs work through streams and channels. Only one stream per channel can be configured. Tables below present **triggers per channel-stream combination**. 

![obraz](https://user-images.githubusercontent.com/36985129/170352983-89e5014c-857b-4efd-a21a-f0c71edc2711.png)
![obraz](https://user-images.githubusercontent.com/36985129/170355409-e87e6276-ae41-4aaa-bfea-d63b165e2515.png)

For capturing data we use _Input Capture Mode_ - it will we triggered by OV7670 clock. For data transfer I2C interface was used.
OV7670 requeres 100kHZ frequency for I2C.

## About camera

![obraz](https://user-images.githubusercontent.com/36985129/170355324-e55301b2-7214-480f-b8fc-650e36cf44d2.png)

The OV7670 image sensor is a low voltage CMOS device that provides the full functionality of a single-chip VGA camera and image processor. For full documetation please refer to http://web.mit.edu/6.111/www/f2016/tools/OV7670_2006.pdf

For data transfer from microcontroller to PC UART has been used.

Image format used: QCIF 320 x 240, RGB565/555

## Connection


![obraz](https://user-images.githubusercontent.com/36985129/170355686-3900f968-b6dc-45db-be5a-863e31acd4b3.png)

**Connection schema**

Pin functions:
- PB6, PB7, PB3, PB10 – first to are responsible for I2C1 (PB6 – SCL, PB7 - SDA) to configure camera 1, second pair for camera 2
- PB3 i PB5 – VSYNC signals receivers, they generate interrupts for falling slope
- PB1 i PB4 – they work like PB3 i PB5, but for HREF signal (interrupts for rising slopes)
- PE9 i PE13 – channel 1 i channel 3 of timer 1, both trigger DMA for rising slope on PCLK
- PA8 – clock signal for both cameras
- PC0-PC7 i PD0-PD7 – 8 bit registers for data capture
- PA2 i PA3 – transmitter and receiver lines for UART

## The way it works

# PCLK configuration


![obraz](https://user-images.githubusercontent.com/36985129/170357584-2cedc60c-6bd1-41bc-8d3e-0a04b3346b27.png)
![obraz](https://user-images.githubusercontent.com/36985129/170357603-56f2d8b4-bde4-4b12-a05b-4c7b7eb126ae.png)
![obraz](https://user-images.githubusercontent.com/36985129/170357618-6255deb9-79f2-40da-a361-db98cb127955.png)

**3 stages of PCLK configuration**


# How data is captured
Data is captured only in case of high voltage for HREF and low voltage for VSYNC. When rising slope for PCLK occurs then DMA sends data to memory. Receinving image on PC requires program to receive data from UART. Such data needs to be put in some converter (bits to RGB565 image)

# How it looks

![obraz](https://user-images.githubusercontent.com/36985129/170358425-6ef4d6b8-64b6-4647-b011-0a662e7e5d4c.png)

**The circuit put together**

![obraz](https://user-images.githubusercontent.com/36985129/170358536-e9570e5a-29b2-4858-b2e7-0184751b8a23.png)

**Photo for one camera - computer monitor**

![obraz](https://user-images.githubusercontent.com/36985129/170358848-3145b04e-d875-4fc8-8094-6e6fff1970c7.png)

**Photos for two cameras - same monitor from different perspectives**

**NOTE**: cameras are very sensitive when it comes to image sharpness configuration (it has to be done manually and destabilizes quickly)
