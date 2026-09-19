#!/bin/bash
mknod myfifo p
if [ $? -eq 0 ]
then
	echo "FIFO created successfully"
else
	echo "Failed to create FIFO"
fi
