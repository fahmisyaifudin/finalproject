import paho.mqtt.client as mqtt
import time
 
# Don't forget to change the variables for the MQTT broker!
mqtt_username = "fahmi"
mqtt_password = "123456"
mqtt_topic = "acak"
mqtt_broker_ip = "192.168.1.100"
 
client = mqtt.Client()
# Set the username and password for the MQTT client
client.username_pw_set(mqtt_username, mqtt_password)
 
# These functions handle what happens when the MQTT client connects
# to the broker, and what happens then the topic receives a message
def on_connect(client, userdata, rc):
    # rc is the error code returned when connecting to the broker
    print "Connected!", str(rc)
    
    # Once the client has connected to the broker, subscribe to the topic
    client.subscribe(mqtt_topic)
def on_message(client, userdata, msg):
    # This function is called everytime the topic is published to.
    # If you want to check each message, and do something depending on
    # the content, the code to do this should be run in this function
    
    print "Topic: ", msg.topic + "\nMessage: " + str(msg.payload)
    f = open("datasuhu.txt", "a+")
    f.write('"' + msg.topic + '":"' +str(msg.payload) + '"\n')
    f.close()
    # The message itself is stored in the msg variable
    # and details about who sent it are stored in userdata
 
# Here, we are telling the client which functions are to be run
# on connecting, and on receiving a message
client.on_connect = on_connect
client.on_message = on_message
 
# Once everything has been set up, we can (finally) connect to the broker
# 1883 is the listener port that the MQTT broker is using
print("connecting to broker ")
client.connect(mqtt_broker_ip, 1883)
print("subscribing ")
client.loop_start()
client.subscribe("Suhu")
