'use client'

import React, { useEffect, useState } from "react";
// import { LineChartComponent } from "@/components/line-chart";
import {  NEXT_PUBLIC_WEBSOCKET } from "@/app/raspberrypi/config";
import mqtt, { MqttClient } from "mqtt";

export default function RaspberryPi() {
    // const [isRecording, setIsRecording] = useState(false);
    const [connectWebSocket, setConnectWebSocket] = useState(false);


    // Create MQTT over WebSocket connection to get the predicted data from Raspberry Pi
    useEffect(() => {
        let ws: WebSocket | null = null;

        if (connectWebSocket) {
            ws = new WebSocket(NEXT_PUBLIC_WEBSOCKET);
      
            ws.onopen = () => {
              console.log('WebSocket connected.');
              ws?.send(apiKey);
            };
      
            ws.onmessage = (event) => {
              try {
                const response = JSON.parse(event.data);
                console.log('WebSocket data received:', response);
              } catch (error) {
                console.error('Error parsing WebSocket data:', error);
              }
            }
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
            <div className='border-2 rounded-lg p-6 shadow-sm mb-6 mt-6'>
                {/* <LineChartComponent title={'Predicted'} description={'ผลการทำนายจาก Raspberry Pi'} chartData={punchPositionChartData} chartConfig={punchPositionLineChartConfig} varname={'ตำแหน่ง'} color={'#a768de'}/> */}
            </div>

            {/* <button className={`${isRecording ? 'bg-red-500 hover:bg-red-600' : 'bg-green-500 hover:bg-green-600'} text-white rounded-md p-2`} onClick={() => setIsRecording(!isRecording)}>
                {isRecording ? 'Stop Recording' : 'Start Recording'}
            </button> */}

        </main>
        </div>
    );
}
