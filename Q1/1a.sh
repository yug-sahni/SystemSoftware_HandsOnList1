#!/bin/bash
ln -s original.txt soft.txt
if [ $? -eq 0 ]
then
	echo "Softlink created successfully"
else
	echo "Failed to create softlink"
fi
