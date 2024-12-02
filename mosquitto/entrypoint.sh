#!/bin/bash
# entrypoint.sh

# Ensure the password file is created from the Render secret
echo "$PASSWD_SECRET" > /mosquitto/passwd

# Start Mosquitto with the custom configuration
exec mosquitto -c /mosquitto/mosquitto.conf