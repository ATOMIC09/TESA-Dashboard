'use client'

import React, { useEffect, useState } from "react";
// import { LineChartComponent } from "@/components/line-chart";
import {  NEXT_PUBLIC_MQTTWEBSOCKET, NEXT_PUBLIC_MQTT_USERNAME, NEXT_PUBLIC_MQTT_PASSWORD } from "@/app/raspberrypi/config";
import mqtt, { MqttClient } from "mqtt";

export default function RaspberryPi() {
    // const [isRecording, setIsRecording] = useState(false);
    const [connectWebSocket, setConnectWebSocket] = useState(false);


    // Create MQTT over WebSocket connection to get the predicted data from Raspberry Pi
    useEffect(() => {
        if (connectWebSocket) {
            const client = mqtt.connect(NEXT_PUBLIC_MQTTWEBSOCKET || '', {
                username: NEXT_PUBLIC_MQTT_USERNAME,
                password: NEXT_PUBLIC_MQTT_PASSWORD,
                protocol: 'ws',
            });
      
            client.on('connect', () => {
                console.log('Connected to MQTT broker');
      
            client.subscribe('#', (err) => {
                if (err) {
                    console.log(err);
                }
                console.log('Subscribed to all topics');
            }
            );
            });

            client.on('message', (topic, message) => {
                console.log(`Received message from topic: ${topic}`);
                console.log(message.toString());
            });

        }
        
    }, [connectWebSocket]);
    

    return (
        <div className="p-8 pb-20 gap-16 sm:p-20 min-h-screen">
        <main className="font-LINESeedSansTH_W_Rg">
            <div className='flex py-4'>
                <span className="text-6xl font-bold">Raspberry Pi Controller</span>
            </div>
            <p className="text-lg text-gray-500 py-4 flex">
                แผงควบคุม Raspberry Pi สำหรับงาน Machine Learning
            </p>

            {/* Predicted from RPi */}
            {/* <div className='border-2 rounded-lg p-6 shadow-sm mb-6 mt-6'> */}
                {/* <LineChartComponent title={'Predicted'} description={'ผลการทำนายจาก Raspberry Pi'} chartData={punchPositionChartData} chartConfig={punchPositionLineChartConfig} varname={'ตำแหน่ง'} color={'#a768de'}/> */}
            {/* </div> */}

            <button className={`${connectWebSocket ? 'bg-red-500 hover:bg-red-600' : 'bg-green-500 hover:bg-green-600'} text-white rounded-md p-2`} onClick={() => setConnectWebSocket(!connectWebSocket)}>
                {connectWebSocket ? 'Disconnect' : 'Connect'}
            </button>

            {/* <button className={`${isRecording ? 'bg-red-500 hover:bg-red-600' : 'bg-green-500 hover:bg-green-600'} text-white rounded-md p-2`} onClick={() => setIsRecording(!isRecording)}>
                {isRecording ? 'Stop Recording' : 'Start Recording'}
            </button> */}

        </main>
        </div>
    );
}
