# Use the official Eclipse Mosquitto base image
FROM eclipse-mosquitto:2.0

# Set up configuration directory and copy files into the image
WORKDIR /mosquitto

# Copy configuration files
COPY /etc/secrets/passwd /mosquitto/passwd
COPY ./data /mosquitto/data
COPY ./log /mosquitto/log
COPY ./mosquitto.conf /mosquitto/mosquitto.conf

# Ensure proper permissions (optional, depending on your setup)
RUN chmod 0600 /mosquitto/passwd \
    && chmod 0644 /mosquitto/mosquitto.conf \
    && chown -R mosquitto:mosquitto /mosquitto

# Expose default Mosquitto ports
EXPOSE 1883 9001

# Run the Mosquitto broker with the custom configuration
CMD ["mosquitto", "-c", "/mosquitto/mosquitto.conf"]