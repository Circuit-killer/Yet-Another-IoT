# History of the Yet Another IoT

A while ago, I was working on three different projects in the IoT area that at was going to be
only test cases of the usage of IoT devices in different projects and enviroments.
When you just need to prototype a test case, it needs to be shipped fast to the client and do the
job, it doesn't need to be the cheaper neither the most optimized. So we picked some Arduino UNO boards, a RaspberryPi and developed the node and broadrouter around it.
With the Arduino ecosystem we got radio and a lot of sensor drivers that break out our delivery time by a tenth (remember, time is money). 

### Examples of how the delivery time was broke down by a tenth using the Arduino Ecossystem:
* A real well written radio driver could need between 2 to 4 months to be well written and tested and in that time AT command modules for LoRa, SigFox (we didn't had Sigfox network in Brazil in that time) was really and still a expensive thing, so we didn't tought about them and also in Brazil a Arduino and a RaspberryPi are common and easy to buy.
* We could test a lot of different radios fast and easily by just swapping the code in the Arduino and testing another radio ( You will never understand it before you walk a kilometer in the street carrying a IoT node in your bag, just to test the radio range)
* To stay in the KISS design principle and doesn't mess around with "How we can get the lowest battery consumption out of it" we simple used a TPL5111 which is a System Timer  to disable the voltage regulator, a simple and elegant solution when you need to only send data to the broadrouter.
This also can be used also when you need to do two-way communication, but not in the current way it's implemented. 

This ecossystem of Node, Broadrouter and Expansion port is proven to a be a really realiable system for developing prototypes and hobby projects around long range (+1km) IoT projects and can be a test bench for testing protocols, radios, sensors and antennas.
