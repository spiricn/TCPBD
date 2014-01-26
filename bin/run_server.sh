#!/bin/bash

# Start the server with provided arguments and restart it if it crashes

while true
do
	./tcpbd_server $1 $2
	echo "Server crashed with exit code $?.  Respawning.." >&2
	sleep 5
done
