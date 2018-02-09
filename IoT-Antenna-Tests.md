# Testing IoT Antennas for the 915Mhz band

### Yageo Chip Antenna
* Digikey Part Number: [311-1525-1-ND](https://www.digikey.com/products/en?keywords=311-1525-1-ND)
* Gain: 3.32dbi
* Price - 1 un - Digikey: US$3.08
* Price - 1000un - Digikey: US$1.49

Pros: Good price and reasonable performace. We tested it with the broadrouter using the Taoglass Hinged Antenna and could receive it within my 1km mark but I didn't feel that It was going to work longer than 1km because of the RSSI readings in the test. It comes in a cut tape or reel, so can be also Pick'n'Placed.

Cons: The 3.32dBi gain doesn't seem to be real because we achieved better overall results with the Molex Adhesive Antenna and the Taoglas Hinged Antenna, which has lower gain but this doesn't outshine his performace for a chip antenna.

### Taoglas Hinged Antenna
* Digikey Part Number: [931-1216-ND](https://www.digikey.com/products/en?keywords=931-1216-ND)
* Gain: 2.5dbi
* Price - 1 un - Digikey: US$13.62
* Price - 500un - Digikey: US$12.08

Pros: The performace is amazing! With 20dbm we got exausted before losting the signal, in a crowd city enviroment, with the broadrouter inside my room, getting more than 1km was an amazing performace.

Cons: It's giant and won't be pass unnoticed by people around. We didn't also felt that it's a good option to be used outside, in this case, use a FiberGlass antenna that will last longer (In this case try testing a collinear coaxial cable antenna inside a non-black PVC tube)

### Molex Adhesive Antenna
* Digikey Part Number: [WM9669-ND](https://www.digikey.com/products/en?keywords=WM9669-ND)
* Gain: 1.4dbi
* Price - 1 un - Digikey: US$4.52
* Price - 1000un - Digikey: US$2.25

Pros: We tried two nodes with this Molex antenna and the result was almost the same as we got with the two Taoglas Hinged Antenna, I walked around my neighborhood distant almost 1km from my house and couldn't loss the contact with my Broadrouter in my house.

Cons: It's a really high price antenna, with good quality but the gluing process could add more US$0.5 to US$1 in the final price of the node also the cable needs to be handled with extra care as the cable is glued to the antenna flex PCB.

### Texas Instruments DN-038 Helical Antenna
* [DN-038 PDF File](http://www.ti.com/lit/an/swra416/swra416.pdf)
* Gain: 2.33dbi
* PCB printed antenna

Pros: It's almost free to implement because it's already on the PCB just needing some matching components, if you have access to cheap PCB and can try many times different thickness, it's a great way to get a almost free antenna.

Cons: We couldn't make it work on our PCB. On it's original design it asks for a 0.8mm and by mistake we manufactured the PCB with 1.6mm thickness. We tried to match it with the original values of the matching circuit but didn't got good results (The SWR was bigger than 10!). We tried some values around but couldn't match and test it with our MiniVNA PRO.
