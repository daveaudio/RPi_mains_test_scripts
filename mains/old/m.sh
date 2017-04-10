#!/bin/bash

clear

# reset the GPIO
echo "2" > /sys/class/gpio/unexport
echo "3" > /sys/class/gpio/unexport
echo "4" > /sys/class/gpio/unexport
echo "7" > /sys/class/gpio/unexport
echo "8" > /sys/class/gpio/unexport
echo "9" > /sys/class/gpio/unexport
echo "10" > /sys/class/gpio/unexport
echo "11" > /sys/class/gpio/unexport
echo "14" > /sys/class/gpio/unexport
echo "15" > /sys/class/gpio/unexport
echo "17" > /sys/class/gpio/unexport
echo "18" > /sys/class/gpio/unexport
echo "22" > /sys/class/gpio/unexport
echo "23" > /sys/class/gpio/unexport
echo "24" > /sys/class/gpio/unexport
echo "25" > /sys/class/gpio/unexport
echo "27" > /sys/class/gpio/unexport
echo "28" > /sys/class/gpio/unexport
echo "29" > /sys/class/gpio/unexport
echo "30" > /sys/class/gpio/unexport
echo "31" > /sys/class/gpio/unexport

# reserve the pins
echo "Reserving pins..."
echo "2" > /sys/class/gpio/export
echo "3" > /sys/class/gpio/export
echo "4" > /sys/class/gpio/export
echo "7" > /sys/class/gpio/export
echo "8" > /sys/class/gpio/export
echo "9" > /sys/class/gpio/export
echo "10" > /sys/class/gpio/export
echo "11" > /sys/class/gpio/export
echo "14" > /sys/class/gpio/export
echo "15" > /sys/class/gpio/export
echo "17" > /sys/class/gpio/export
echo "18" > /sys/class/gpio/export
echo "22" > /sys/class/gpio/export
echo "23" > /sys/class/gpio/export
echo "24" > /sys/class/gpio/export
echo "25" > /sys/class/gpio/export
echo "27" > /sys/class/gpio/export
echo "28" > /sys/class/gpio/export
echo "29" > /sys/class/gpio/export
echo "30" > /sys/class/gpio/export
echo "31" > /sys/class/gpio/export

# pin direction
echo "Setting pin direction"
echo "out" > /sys/class/gpio/gpio2/direction
echo "out" > /sys/class/gpio/gpio3/direction
echo "out" > /sys/class/gpio/gpio7/direction
echo "out" > /sys/class/gpio/gpio8/direction
echo "out" > /sys/class/gpio/gpio9/direction
echo "out" > /sys/class/gpio/gpio10/direction
echo "out" > /sys/class/gpio/gpio11/direction
echo "out" > /sys/class/gpio/gpio14/direction
echo "out" > /sys/class/gpio/gpio15/direction
echo "out" > /sys/class/gpio/gpio17/direction
echo "out" > /sys/class/gpio/gpio18/direction
echo "out" > /sys/class/gpio/gpio22/direction
echo "out" > /sys/class/gpio/gpio23/direction
echo "out" > /sys/class/gpio/gpio24/direction
echo "out" > /sys/class/gpio/gpio25/direction
echo "out" > /sys/class/gpio/gpio27/direction
echo "out" > /sys/class/gpio/gpio28/direction
echo "out" > /sys/class/gpio/gpio29/direction
echo "out" > /sys/class/gpio/gpio30/direction
echo "out" > /sys/class/gpio/gpio31/direction

# pin value
echo "Turning off the relays"
echo "1" > /sys/class/gpio/gpio17/value		# pin 1
echo "1" > /sys/class/gpio/gpio27/value		# pin 2
echo "1" > /sys/class/gpio/gpio22/value		# pin 3
echo "1" > /sys/class/gpio/gpio23/value		# pin 4
echo "1" > /sys/class/gpio/gpio31/value		# pin 5
echo "1" > /sys/class/gpio/gpio30/value		# pin 6
echo "1" > /sys/class/gpio/gpio25/value		# pin 7
echo "1" > /sys/class/gpio/gpio24/value		# pin 8

sleep 2

# pin value
echo "Turning on  the relays"
echo "0" > /sys/class/gpio/gpio17/value		# pin 1
echo "0" > /sys/class/gpio/gpio27/value		# pin 2
echo "0" > /sys/class/gpio/gpio22/value		# pin 3
echo "0" > /sys/class/gpio/gpio23/value		# pin 4
echo "0" > /sys/class/gpio/gpio31/value		# pin 5
echo "0" > /sys/class/gpio/gpio30/value		# pin 6
echo "0" > /sys/class/gpio/gpio25/value		# pin 7
echo "0" > /sys/class/gpio/gpio24/value		# pin 8

sleep 2

# pin value
echo "Setting pin output to zero"
echo "1" > /sys/class/gpio/gpio17/value		# pin 1
echo "1" > /sys/class/gpio/gpio27/value		# pin 2
echo "1" > /sys/class/gpio/gpio22/value		# pin 3
echo "1" > /sys/class/gpio/gpio23/value		# pin 4
echo "1" > /sys/class/gpio/gpio31/value		# pin 5
echo "1" > /sys/class/gpio/gpio30/value		# pin 6
echo "1" > /sys/class/gpio/gpio25/value		# pin 7
echo "1" > /sys/class/gpio/gpio24/value		# pin 8

# reset the GPIO
#echo "Resetting the GPIO..."
#echo "4" > /sys/class/gpio/unexport
#echo "14" > /sys/class/gpio/unexport
#echo "15" > /sys/class/gpio/unexport
#echo "17" > /sys/class/gpio/unexport
#echo "18" > /sys/class/gpio/unexport
#echo "22" > /sys/class/gpio/unexport
#echo "23" > /sys/class/gpio/unexport
#echo "27" > /sys/class/gpio/unexport

echo ""
echo "Script complete"
echo ""
