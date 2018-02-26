### Working on next version of the YaIoT node

#### Planned new features:
* In board MPTT charger with LTC4121-4.2: LT3652 doesn't work really well with 6v solar panels, in our tests around 5v it stop working, so, we only really charge when there is full sun.  
* In board PCF2129 RTC for precision timing measurements: I'm thinking about the idea of adding a PCF2129AT on the bottom side of the board to use in the case of a weather station node.
* Add a 18650 Cell-Holder on board: This is one of the features that I'm expecting the most. The way we get the battery "around" inside the node case at the moment annoys me a lot! With the Cell-Holder it get's really easy to mount the project in the plastic case.
* In board battery gauge with BQ27750: I think a battery gauge can be a "Variant" of the project, sometimes it's nice to know if how the charging is going and how much battery we got left.

##### Features deprecated on this version:
* MCP73831 - With the inboard MPTT charger we don't need two battery chargers
* Hi-Link Power Supply - If you need a mains connected node, just get the V1.0 of the hardware. 
* Si70xx - Maybe I'm getting rid of the Si70xx because we have them in the pH-SPI-Board and in the plastic case I use at the moment in the nodes, while using the shield we got a more precise measurement of the enviroment around.
