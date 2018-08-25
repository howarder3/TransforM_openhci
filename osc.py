import OSC
c = OSC.OSCClient()
c.connect(('192.168.43.112', 8000))  # connect to SuperCollider
oscmsg = OSC.OSCMessage()
oscmsg.setAddress("/run-code")
oscmsg.append('oh yeahhhhhhhh')
c.send(oscmsg)