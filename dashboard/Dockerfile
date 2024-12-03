# Use Node.js for building and serving Next.js
FROM node:18-alpine AS builder

WORKDIR /app

ENV NEXT_PUBLIC_BACKENDSERVER=$NEXT_PUBLIC_BACKENDSERVER
ENV NEXT_PUBLIC_MQTT_PASSWORD=$NEXT_PUBLIC_MQTT_PASSWORD
ENV NEXT_PUBLIC_MQTT_USERNAME=$NEXT_PUBLIC_MQTT_USERNAME
ENV NEXT_PUBLIC_MQTTWEBSOCKET=$NEXT_PUBLIC_MQTTWEBSOCKET

# Copy code and install dependencies
COPY package.json package-lock.json ./
RUN npm install

# Copy source code and build the app
COPY . .
RUN npm run build

# Production image to serve the app
FROM node:18-alpine

WORKDIR /app
COPY --from=builder /app ./
EXPOSE 3000
CMD ["npm", "run", "start"]
