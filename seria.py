import serial
import OSC
c = OSC.OSCClient()
c.connect(('192.168.43.112', 8000))  # connect to SuperCollider
ser = serial.Serial('/dev/ttyACM1',9600)
tmp_state = "green"

while True:
	read_serial=int(ser.readline())
	#print(read_serial)	
	oscmsg = OSC.OSCMessage()
	oscmsg.setAddress("/arduino-message")
	if(read_serial <= 50 and (tmp_state == "yellow" or  tmp_state == "green")):
		#oscmsg.append("someone come front")
		oscmsg.append(1)
		tmp_state = "red"
		print("someone come front")
		c.send(oscmsg)
		#print(tmp_state)
	elif (read_serial > 50 and read_serial <= 100 and tmp_state == "green"):
		#oscmsg.append("someone near here")
		oscmsg.append(2)
		print("someone near here")
		tmp_state = "yellow"
		c.send(oscmsg)
		#print(tmp_state)
	elif(read_serial > 100 and (tmp_state == "yellow" or  tmp_state == "red")):
		#oscmsg.append("someone leave")
		oscmsg.append(3)
		print("someone leave")
		tmp_state = "green"
		c.send(oscmsg)
		#print(tmp_state)


