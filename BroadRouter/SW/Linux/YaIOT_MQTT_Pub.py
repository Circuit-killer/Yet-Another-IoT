#!/usr/bin/python
# -*- coding: utf-8 -*-


#######################################################################
#                           WORK IN PROGRESS
# Filename: YaIOT_MQTT_PUB.py
# Eng. Felipe Navarro
# Description: This script is responsible for getting the data from the
# serial and publishing it to the MQTT broker.
# 
# Other features:
#   Add timestamp if data doesn't have one
#   Save data when no connection to the internet availabe
#   Log 
#
#######################################################################

#######################################################################
# Import modules
#######################################################################
import logging
from logging.handlers import RotatingFileHandler

#Import Serial
import serial

#Import PahoMQTT Client
import paho.mqtt.client as paho
import time

#######################################################################
# The next lines of code, sets the loggging of the software.
# We need it because it's a way to see what gone wrong with
# the product while doing a debug.
#######################################################################

log = logging.getLogger('YaIoT')
hdlr = RotatingFileHandler('YaIoT_LOGFILE.log', maxBytes=200000, backupCount=1)
formatter = logging.Formatter('%(asctime)s %(levelname)s %(message)s')
hdlr.setFormatter(formatter)
log.addHandler(hdlr)
log.setLevel(logging.INFO)

#######################################################################
# PYSerial for gettting data from our server node
#######################################################################

ser = serial.Serial(
    port='/dev/ttyAMA0', #Internal RPi Serial
    baudrate=115200
)

#######################################################################
# MQTT functions defines
####################################################################### 
def on_publish(client, userdata, mid):
    print("Published: "+str(mid))

def on_connect(client, userdata, mid):
    log.info("Connected to the Broker")

client = paho.Client()
client.on_publish = on_publish
client.on_connect = on_connect
host = "broker.hivemq.com"
client.connect(host, port=1883)
client.loop_start()



while True:
    for x in range (0, 100):
        msg = x
        (rc, mid) = client.publish("navarro/temperature", msg)
        time.sleep(0.1)
