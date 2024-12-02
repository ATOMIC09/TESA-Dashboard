# Use the official MongoDB base image
FROM mongo:5.0

# Copy the initialization script into the MongoDB container
COPY ./mongo-init.js /docker-entrypoint-initdb.d/mongo-init.js

# Expose the MongoDB default port
EXPOSE 27017

# Set the container's hostname to 'mongodb' (optional, not mandatory in Dockerfile)
ENV MONGO_INITDB_ROOT_USERNAME=$MONGO_INITDB_ROOT_USERNAME
ENV MONGO_INITDB_ROOT_PASSWORD=$MONGO_INITDB_ROOT_PASSWORD