'use client';

import React, { useEffect, useState } from "react";
import { LineChartComponentForPi } from "./line-chart-forpi";
import { NEXT_PUBLIC_MQTTWEBSOCKET, NEXT_PUBLIC_MQTT_USERNAME, NEXT_PUBLIC_MQTT_PASSWORD } from "@/app/raspberrypi/config";
import mqtt from "mqtt";

export default function RaspberryPi() {
    const [connectWebSocket, setConnectWebSocket] = useState(false);
    const [mluData, setMluData] = useState<mluDatai[]>([]);

    interface mluDatai {
        id: number;
        timestamp: number;
        created_at: string;
        classification: string;
        confidence: number;
    }

    // Create MQTT over WebSocket connection to get the predicted data from Raspberry Pi
    useEffect(() => {
        const client = mqtt.connect(NEXT_PUBLIC_MQTTWEBSOCKET || '', {
            username: NEXT_PUBLIC_MQTT_USERNAME,
            password: NEXT_PUBLIC_MQTT_PASSWORD,
            protocol: 'ws',
        });
        if (connectWebSocket) {

            client.on('connect', () => {
                console.log('Connected to MQTT broker');
                client.subscribe('rpi/mlu/data', (err) => {
                    if (err) {
                        console.log(err);
                    }
                    console.log('Subscribed to rpi/mlu/data');
                });
            });

            client.on('message', (topic, message) => {
                const data = JSON.parse(message.toString());
                setMluData((prevData) => {
                    // Add new data and limit the array to the last 30 items
                    const updatedData = [
                        ...prevData,
                        {
                            id: data.id,
                            timestamp: data.timestamp,
                            created_at: data.created_at,
                            classification: data.classification,
                            confidence: data.confidence,
                        },
                    ];
                    return updatedData.slice(-30);
                });
            });

            return () => {
                client.end();
            };
        }

        if (!connectWebSocket) {
            client.end();
        }
    }, [connectWebSocket]);

    useEffect(() => {
        console.log("Accumulated mluData:", mluData);
    }, [mluData]);

    const mluConfig = {
        scales: {
            x: {
                title: {
                    display: true,
                    text: 'Timestamp',
                },
            },
            y: {
                title: {
                    display: true,
                    text: 'Confidence',
                },
            },
        },
    };

    return (
        <div className="p-8 pb-20 gap-16 sm:p-20 min-h-screen">
            <main className="font-LINESeedSansTH_W_Rg">
                <div className="flex py-4">
                    <span className="text-6xl font-bold">Raspberry Pi Controller</span>
                </div>
                <p className="text-lg text-gray-500 py-4 flex">
                    แผงควบคุม Raspberry Pi สำหรับงาน Machine Learning
                </p>

                <div className="py-4">
                    <button
                        className={`${connectWebSocket ? 'bg-red-500 hover:bg-red-600' : 'bg-green-500 hover:bg-green-600'} text-white rounded-md p-2`}
                        onClick={() => setConnectWebSocket(!connectWebSocket)}
                    >
                        {connectWebSocket ? 'Disconnect' : 'Connect'}
                    </button>
                </div>

                <LineChartComponentForPi
                    title={'Predicted'}
                    description={'ผลการทำนายจาก Raspberry Pi'}
                    chartData={mluData}
                    chartConfig={mluConfig}
                    varname={'ตำแหน่ง'}
                    color={'#a768de'}
                />
            </main>
        </div>
    );
}
