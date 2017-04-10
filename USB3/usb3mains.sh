#!/bin/bash

clear;
reboot_counter=0;
delay_val=10
#text_val=10



sudo ./relay_init
sleep 1;


until [ 1 -eq 2 ]; do
	echo ""
	echo "Reboot counter = $reboot_counter";
	echo ""
	sudo ./relay -r 1 -on
	echo "Waiting for hard drive to become visible..."
	exit_loop="no"
	until [ "$exit_loop" == "yes" ]; do
		sleep 2
		string_var="no"
		string_var=$(sudo ls /dev/sda1)
		#echo $string_var
		if [ "$string_var" == "/dev/sda1" ]; then
			#echo $string_var
			exit_loop="yes"
		fi
	done
	echo "HDD found: $string_var"
	sudo mount /dev/sda1 /home/pi/HDD
	sudo ls /home/pi/HDD;
	sudo umount /home/pi/HDD;
	cd /home/pi/USB3;
	let reboot_counter=reboot_counter+1;
	sudo ./relay -r 1 -off
	sleep 5;
done
#exit
