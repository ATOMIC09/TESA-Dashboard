# Use Node.js LTS as the base image
FROM node:18

# Set working directory in the container
WORKDIR /app

# Copy package.json and package-lock.json (if exists)
COPY package*.json ./

# Install dependencies
RUN npm install

# Copy the rest of the application files
COPY . .

# Expose WebSocket server port
EXPOSE 8001

# Set the default command to run the script
CMD ["node", "mlu.js"]
