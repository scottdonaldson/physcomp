"""
This program sends 10 random values between 0.0 and 1.0 to the /filter address,
waiting for 1 seconds between each value.

Example edited on 9-20-16 by Joseph Paetz for use in Intro to Physical
    Computing (60-223) at Carnegie Mellon University

MODIFIED by eholthau and sdonalds for 60-223 F16.  This version sends power and turning values stored in an array of arrays to the address at the time interval specified as the third element.

data format: instructions = [ (power1, rotation1, time1), (power2, rotation2, time2), ...(power_n, rotation_n, time_n) ]
"""
import argparse
import random
import time
import curses

from pythonosc import osc_bundle_builder
from pythonosc import osc_message_builder
from pythonosc import udp_client

power = 100
rotation = 100

def stabilize(x):
	if x < 100:
		x += 1
	elif x > 100:
		x -= 1
	return x

def clamp(x):
	if x > 200: return 200
	if x < 0: return 0
	return x

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

	stdscr = curses.initscr()

	curses.noecho()

	curses.cbreak()

	stdscr.keypad(1)

	stdscr.nodelay(1)

	while True:

		c = stdscr.getch()

		power = stabilize(power)

		if c == ord('w'):
			power += 10
		elif c == ord('s'):
			power -= 10

		rotation = stabilize(rotation)

		if c == ord('a'):
			rotation -= 3
		elif c == ord('d'):
			rotation += 3

		power = clamp(power)
		rotation = clamp(rotation)

		if c == ord('q'):
			curses.nocbreak()
			stdscr.keypad(0)
			curses.echo()
			curses.endwin()

			break


		stdscr.addstr(
			0, 
			0, 
			"power: " + str(power - 100).zfill(3) + " / rotation: " + str(rotation - 100).zfill(3)
		)
		stdscr.refresh()

        # build the msg to send to the NodeMCU. This is the address that
		# the NodeMCU will be watching for

		msg = osc_message_builder.OscMessageBuilder(address = "/led")

		# send 0, 0 to shut it off
		msg.add_arg(power)
		msg.add_arg(rotation)

		msg = msg.build()

		client.send(msg)
		time.sleep(0.15)

	msg = osc_message_builder.OscMessageBuilder(address = "/led")

	# send 0, 0 to shut it off
	msg.add_arg(100)
	msg.add_arg(100)

	msg = msg.build()

	client.send(msg)
	time.sleep(1)
