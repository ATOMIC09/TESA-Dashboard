'use client';

import React, { useEffect, useState, useRef } from "react";
import { LineChartComponentForPi } from "./line-chart-forpi";
import TableComponentForPi from "./TableComponent-forpi";
import { NEXT_PUBLIC_MQTTWEBSOCKET, NEXT_PUBLIC_MQTT_USERNAME, NEXT_PUBLIC_MQTT_PASSWORD } from "@/app/raspberrypi/config";
import mqtt from "mqtt";

export default function RaspberryPi() {
    const [connectWebSocket, setConnectWebSocket] = useState(false);
    const [mluData, setMluData] = useState<mluDatai[]>([]);
    const [isRecording, setIsRecording] = useState(false);
    const [isOnline, setIsOnline] = useState(false);

    interface mluDatai {
        id: number;
        timestamp: number;
        created_at: string;
        classification: string;
        confidence: number;
    }

    const client = mqtt.connect(NEXT_PUBLIC_MQTTWEBSOCKET || '', {
        username: NEXT_PUBLIC_MQTT_USERNAME,
        password: NEXT_PUBLIC_MQTT_PASSWORD,
        protocol: 'ws',
    });

    // References for the timeouts to reset the online status
    const dataTimeoutRef = useRef<NodeJS.Timeout | null>(null);

    // Create MQTT over WebSocket connection to get the predicted data from Raspberry Pi
    useEffect(() => {
        if (connectWebSocket) {
            client.on('connect', () => {
                console.log('Connected to MQTT broker');
                client.subscribe('rpi/mlu/data', (err) => {
                    if (err) {
                        console.log(err);
                    }
                    console.log('Subscribed to rpi/mlu/data');
                });

                // Subscribe to the status topic
                client.subscribe('rpi/10000000bab0b141/status', (err) => {
                    if (err) {
                        console.log(err);
                    }
                    console.log('Subscribed to rpi/10000000bab0b141/status');
                });
            });

            client.on('message', (topic, message) => {
                const data = JSON.parse(message.toString());

                // If the message is from 'rpi/mlu/data'
                if (topic === 'rpi/mlu/data') {
                    setIsOnline(true);
                    // Reset the data timeout whenever a new message is received
                    if (dataTimeoutRef.current) {
                        clearTimeout(dataTimeoutRef.current); // Clear previous timeout
                    }

                    // Handle the machine learning data
                    setMluData((prevData) => {
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

                    // Set a timeout to reset status to offline after 5 minutes of no data update
                    dataTimeoutRef.current = setTimeout(() => {
                        setIsOnline(false);
                        console.log('Raspberry Pi is offline due to no data update');
                    }, 30 * 1000); // 30 seconds in milliseconds
                } 
                // If the message is from 'rpi/10000000bab0b141/status'
                else if (topic === 'rpi/10000000bab0b141/status') {
                    // If the status is 'online', set it as online
                    if (data.status === 'online') {
                        setIsOnline(true);
                    } else {
                        setIsOnline(false);
                    }
                }
            });

            return () => {
                if (dataTimeoutRef.current) {
                    clearTimeout(dataTimeoutRef.current); // Clean up the data timeout on unmount
                }
                client.end();
            };
        } else {
            client.end();
        }
    }, [connectWebSocket]); // Dependency on connectWebSocket state

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

    const handleStartRecording = () => {
        if (isRecording) {
            setIsRecording(false);
            publishMessage('stopRecord');
        } else {
            setIsRecording(true);
            publishMessage('startRecord');
        }
    };

    const publishMessage = (command: string) => {
        client.publish('rpi/10000000bab0b141/command',
            JSON.stringify({
                command: command,
            }),
            (err) => {
                if (err) {
                    console.log(err);
                }
                console.log('Published start command');
            });
    }

    return (
        <div className="p-8 pb-20 gap-16 sm:p-20 min-h-screen">
            <main className="font-LINESeedSansTH_W_Rg">
                <div className="flex py-4">
                    <span className="text-6xl font-bold">Raspberry Pi Controller</span>
                </div>
                <p className="text-lg text-gray-500 py-4 flex">
                    แผงควบคุม Raspberry Pi สำหรับงาน Machine Learning
                </p>

                <div className="py-4 flex">
                    <div className="flex flex-row items-center mr-4">
                        <span className="text-lg font-bold">Status: </span>
                        <div className={`w-4 h-4 rounded-full ${isOnline ? 'bg-green-500' : 'bg-red-500'} ml-2`}></div>
                    </div>
                    <button
                        className={`${connectWebSocket ? 'bg-red-500 hover:bg-red-600' : 'bg-green-500 hover:bg-green-600'} text-white rounded-md p-2`}
                        onClick={() => setConnectWebSocket(!connectWebSocket)}
                    >
                        {connectWebSocket ? 'Disconnect' : 'Connect'}
                    </button>
                    <button // reset button
                        className='bg-blue-500 hover:bg-blue-600 text-white rounded-md p-2 ml-2'
                        onClick={() => setMluData([])}
                    >
                        Reset
                    </button>
                    {/* Separator */}
                    <div className="border-2 rounded-md h-10 mx-4 border-gray-300"></div>
                    <button
                        className={`${isRecording ? 'bg-red-900 hover:bg-red-950' : 'bg-red-500 hover:bg-red-600'} text-white rounded-md p-2`}
                        onClick={handleStartRecording}
                    >
                        {isRecording ? 'Stop Recording' : 'Start Recording'}
                    </button>

                </div>

                <div className="flex flex-row justify-between">
                    <LineChartComponentForPi
                        title={'Predicted'}
                        description={'ผลการทำนายจาก Raspberry Pi'}
                        chartData={mluData}
                        chartConfig={mluConfig}
                        varname={'ตำแหน่ง'}
                        color={'#a768de'}
                    />
                    <div className='border-2 rounded-lg shadow-sm min-w-[40em]'>
                        <TableComponentForPi tabledatas={mluData}/>
                    </div>
                </div>    

            </main>
        </div>
    );
}
