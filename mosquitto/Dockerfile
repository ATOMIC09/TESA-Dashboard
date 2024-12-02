# Use the official Eclipse Mosquitto base image
FROM eclipse-mosquitto:2.0

# Set up configuration directory and create necessary directories
WORKDIR /mosquitto

# Create /data and /log directories before copying files
RUN mkdir -p ./data ./log

# Copy configuration files into the image
COPY ./data /mosquitto/data
COPY ./log /mosquitto/log
COPY ./mosquitto.conf /mosquitto/mosquitto.conf

# Copy the entrypoint script to handle the secret
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# Ensure proper permissions (optional, depending on your setup)
RUN chmod 0644 /mosquitto/mosquitto.conf \
    && chown -R mosquitto:mosquitto /mosquitto

# Expose default Mosquitto ports
EXPOSE 1883 9001

# Use the entrypoint script to manage secrets and start Mosquitto
ENTRYPOINT ["/entrypoint.sh"]
