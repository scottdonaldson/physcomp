"""
This program sends 10 random values between 0.0 and 1.0 to the /filter address,
waiting for 1 seconds between each value.

Example edited on 9-20-16 by Joseph Paetz for use in Intro to Physical
    Computing (60-223) at Carnegie Mellon University
"""
import argparse
import random
import time
import requests
import json

from pythonosc import osc_bundle_builder
from pythonosc import osc_message_builder
from pythonosc import udp_client

power = 0
rotation = 100

instructions = [
			#t0
	(15,1,3),
	(31,15,2),  
	(40,1,3.5),  #t07
	(40,0,3.5),
	(40,6,5),
	(15,0,2),
	(0,60,0.5), #180 in place
	(20,-1,2),
	(0,60,0.3),
	(30,2,8),
	(0,60,0.33),
	(35,1,2),
	(35,0,2),
	(35,1,2),
	(35,0,2),
	(40,1,2),
	(35,1,2),
	(0,-30,0.5),
	(0,0,0)		#end
]

instructionss = [
					# t00
	(50, 0, 1), 	# t01
	(0, 50, 0.2),
	(0, 0, 1),		
	(50, 0, 0.1),		# jitter
	(-50, 0, 0.1),
	(0, 0, 1),
	(50, 0, 0.1),		# jitter
	(-50, 0, 0.1),
	(0, 0, 2),	
	(50, 0, 2),		
	(0, 0, 1), 		# t06
	(60, 58, 0.5),
	(45, 0, 3),		# t09 = t00
	(0, -60, 0.4),
	(0, 0, 1),
	(50, 0, 0.1),		# jitter
	(-50, 0, 0.1),
	(0, 0, 0.5),
	(0, -20, 0.5),
	(60, 0, 2),		# t12 = t06
	(0, 65, 0.5),
	(65, 0, 1.5),	# t14 = t09 = t00
	(0, 0, 1),
	(0, 65, 0.5),
	(50, 0, 0.1),		# jitter
	(-50, 0, 0.1),
	(0, 0, 0.5),
	(35, 0, 2),		# t17
	(0, 0, 1),
	(0, -60, 0.5),
	(50, -5, 3),	# t22
	(0, 60, 0.5),
	(50, 0, 1),
	(60, 6, 3),		# t26 = t12 = t06
	(0, 60, 0.2),
	(60, 0, 1.5),	# t27
	(0, 60, 0.5),
	(60, 0, 1),		# t28
	(70, -15, 2),	# t30
	(0, 60, 0.6),

	(0, 0, 1),
]

if __name__ == "__main__":
    # REPLACE WITH YOUR NODEMCU's IP
	ip = "192.168.1.9"

    # This should match the localPort variable in the Arduino sketch
	port = 1410

	# these lines set things up to recieve input from the command line
	#  that will over write the default ip and port above
	parser = argparse.ArgumentParser()
	parser.add_argument("--ip", default=ip, help="The ip of the OSC server")
	parser.add_argument("--port", type=int, default=port,
	                help="The port the OSC server is listening on")
	args = parser.parse_args()

	# set up udp client
	client = udp_client.UDPClient(args.ip, args.port)

	for i in range(len(instructions)):
		power = instructions[i][0] + 100
		rotation = instructions[i][1] + 100
		t = instructions[i][2]

		#  - if you wanted to send a bundle, you could use:
		#       bundle = osc_bundle_builder.OscBundleBuilder(osc_bundle_builder.IMMEDIATELY)
		#       {build your message and add data to it like you do below}
		#       bundle.add_content(msg1)
		#       bundle.add_content(msg2)
		#       bundle = bundle.build()
		#       client.sen(bundle)

		# build the msg to send to the NodeMCU. This is the address that
		# the NodeMCU will be watching for
		msg = osc_message_builder.OscMessageBuilder(address = "/led")

		# start byte
		# msg.add_arg(250)

		# power
		msg.add_arg(power)

		# rotation
		msg.add_arg(rotation)

		print("sending")
		print(str(power) + ' ' + str(rotation))

		msg = msg.build()

		#send the message
		client.send(msg)

		time.sleep(t)

	while True:
		# build the msg to send to the NodeMCU. This is the address that
		# the NodeMCU will be watching for
		msg = osc_message_builder.OscMessageBuilder(address = "/led")

		# send 0, 0 to shut it off
		msg.add_arg(100)
		msg.add_arg(100)

		msg = msg.build()

		client.send(msg)
		time.sleep(1)
