const mqtt = require('mqtt');
const WebSocket = require('ws'); // Import WebSocket library
require('dotenv').config();

// Connect to the MQTT broker (change to your broker URL)
const client = mqtt.connect(process.env.NEXT_PUBLIC_MQTTWEBSOCKET, {
  username: process.env.NEXT_PUBLIC_MQTT_USERNAME,
  password: process.env.NEXT_PUBLIC_MQTT_PASSWORD,
  protocol: 'wss',
});

// Function to generate random simulation data for WebSocket
function generateSimulationData() {
  const triangularWave = (t, amplitude, period) => 
    (2 * amplitude / period) * (t % period) - amplitude;
  const squareWave = (t, amplitude, period) =>
    ((t / period) % 2 < 1 ? amplitude : -amplitude);

  const timestamp = Math.floor(Date.now() / 1000);
  const t = timestamp % 20000; // Time within a cycle

  return {
    "Energy Consumption": {
      "Power": parseFloat((90 + Math.random() * 20).toFixed(2)), // Power with noise
    },
    "Voltage": {
      "L1-GND": parseFloat((220 + Math.random() * 10).toFixed(2)), // Random voltage
      "L2-GND": parseFloat((220 + Math.random() * 10).toFixed(2)),
      "L3-GND": parseFloat((220 + Math.random() * 10).toFixed(2)),
    },
    "Pressure": parseFloat((squareWave(t, 20, 5000) + Math.random()).toFixed(2)), // Square wave with noise
    "Force": parseFloat((squareWave(t, 30, 5000) + Math.random()).toFixed(2)), // Square wave with noise
    "Cycle Count": t, // Cycle count from 0 to 20,000
    "Position of the Punch": parseFloat((triangularWave(t, 120, 10000) + Math.random()).toFixed(2)), // Triangular wave
  };
}

// WebSocket server setup
const wss = new WebSocket.Server({ port: 8001 });

wss.on('connection', (ws) => {
  console.log('WebSocket client connected');

  const intervalId = setInterval(() => {
    const data = generateSimulationData();
    ws.send(JSON.stringify(data));
  }, 200);

  ws.on('close', () => {
    clearInterval(intervalId); // Stop sending data when the client disconnects
    console.log('WebSocket client disconnected');
  });
});

// Original MQTT code remains unchanged
function generateRandomData() {
  const classificationValues = ['N', 'F', 'X'];
  return {
    id: Math.floor(Math.random() * 1000),
    timestamp: Math.floor(Date.now() / 1000),
    created_at: new Date().toISOString(),
    classification: classificationValues[Math.floor(Math.random() * 3)],
    confidence: parseFloat((Math.random()).toFixed(15)),
  };
}

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

client.on('connect', () => {
  console.log('Connected to MQTT broker');
  setInterval(publishData, 500);
});

client.on('error', (err) => {
  console.error('MQTT connection error:', err);
});
