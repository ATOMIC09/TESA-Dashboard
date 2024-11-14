const mqtt = require('mqtt');
require('dotenv').config();

// Connect to the MQTT broker (change to your broker URL)
const client = mqtt.connect(process.env.NEXT_PUBLIC_MQTTWEBSOCKET, {
  username: process.env.NEXT_PUBLIC_MQTT_USERNAME,
  password: process.env.NEXT_PUBLIC_MQTT_PASSWORD,
  protocol: 'ws',
});
// Simulate data
function generateRandomData() {
  const classificationValues = ['N', 'F', 'X'];
  return {
    id: Math.floor(Math.random() * 1000), // Random ID between 0-1000
    timestamp: Math.floor(Date.now() / 1000), // Current timestamp in seconds
    created_at: new Date().toISOString(), // Current time in ISO 8601 format
    classification: classificationValues[Math.floor(Math.random() * 3)], // Random classification, 'N' or 'Y'
    confidence: parseFloat((Math.random()).toFixed(15)) // Random confidence value between 0 and 1 with high precision
  };
}

// Publish data to MQTT topic
function publishData() {
  const data = generateRandomData();
  const topic = 'rpi/mlu/data';
  
  client.publish(topic, JSON.stringify(data), (err) => {
    if (err) {
      console.error('Error publishing message:', err);
    } else {
      console.log('Message sent:', JSON.stringify(data));
    }
  });
}

// When the client is connected, start publishing data every 5 seconds
client.on('connect', () => {
  console.log('Connected to MQTT broker');
  setInterval(publishData, 900); // Send data every 0.9 seconds
});

// Handle MQTT client error
client.on('error', (err) => {
  console.error('MQTT connection error:', err);
});
