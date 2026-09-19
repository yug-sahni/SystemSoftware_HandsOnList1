#!/bin/bash
ln original.txt hard.txt
if [ $? -eq 0 ]
then
	echo "Hardlink created successfully"
else
	echo "Failed to create hardlink"
fi
