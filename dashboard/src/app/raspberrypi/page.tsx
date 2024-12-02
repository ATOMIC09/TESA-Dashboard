/* eslint-disable react-hooks/exhaustive-deps */
'use client';

import React, { useEffect, useState, useRef } from "react";
import { LineChartComponentForPi } from "./line-chart-forpi";
import TableComponentForPi from "./TableComponent-forpi";
import mqtt from "mqtt";

export default function RaspberryPi() {
    const [connectWebSocket, setConnectWebSocket] = useState(false);
    const [mluData, setMluData] = useState<mluDatai[]>([]);
    const [isRecording, setIsRecording] = useState(false);
    const [isOnline, setIsOnline] = useState(false);
    const [elapsedTime, setElapsedTime] = useState(0);
    const [isAutoMode, setIsAutoMode] = useState(false);
    const [logStatus, setLogStatus] = useState<string[]>([]);
    const [isConnected, setIsConnected] = useState(false);
    const [isConnecting, setIsConnecting] = useState(false);

    const timerRef = useRef<NodeJS.Timeout | null>(null);
    const client = mqtt.connect('wss://6dfbc63868d14af8a538980749d13caf.s1.eu.hivemq.cloud', {
        username: process.env.NEXT_PUBLIC_MQTT_USERNAME,
        password: process.env.NEXT_PUBLIC_MQTT_PASSWORD,
        path: '/mqtt',
        port: 8884,
    });
    const dataTimeoutRef = useRef<NodeJS.Timeout | null>(null);

    interface mluDatai {
        id: number;
        timestamp: number;
        created_at: string;
        classification: string;
        confidence: number;
    }


    useEffect(() => {
        if (connectWebSocket) {
            console.log('Connecting to MQTT broker...');
            console.log('Username:', process.env.NEXT_PUBLIC_MQTT_USERNAME);
            console.log('Password:', process.env.NEXT_PUBLIC_MQTT_PASSWORD);
            console.log('Password:', process.env.NODE_ENV_TEST);
            console.log('Password:', process.env.REACT_APP_TEST);
            console.log('Password:', process.env.TEST);
            setIsConnecting(true);
            client.on('connect', () => {
                setIsConnected(true);
                setIsConnecting(false);
                console.log('Connected to MQTT broker');
                
                // Subscribe to topics
                const topics = ['rpi/mlu/data', 'rpi/10000000bab0b141/status'];
                topics.forEach((topic) => {
                    client.subscribe(topic, (err) => {
                        if (err) {
                            console.error(`Subscription error on ${topic}:`, err);
                        } else {
                            console.log(`Subscribed to ${topic}`);
                        }
                    });
                });
    
                // Stop recording message
                publishMessage('stopRecord');
            });
    
            client.on('error', (err) => {
                console.error('Connection error: ', err);
                client.end();
            });
    
            client.on('message', (topic, message) => {
                try {
                    const data = JSON.parse(message.toString());
    
                    if (topic === 'rpi/mlu/data') {
                        setIsOnline(true);
                        // Clear previous timeout and set a new one
                        if (dataTimeoutRef.current) {
                            clearTimeout(dataTimeoutRef.current);
                        }
    
                        console.log('Received data:', data);
    
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
                            return updatedData.slice(-30); // Keep the last 30 items
                        });
    
                        // Set timeout to mark as offline after 30 seconds of inactivity
                        dataTimeoutRef.current = setTimeout(() => {
                            setIsOnline(false);
                            console.log('Raspberry Pi is offline due to no data update');
                        }, 30 * 1000);
                    }
    
                    if (topic === 'rpi/10000000bab0b141/status') {
                        setLogStatus((prev) => [
                            ...prev,
                            `State: ${data.report_state}, File: ${data.filename || 'N/A'}, Time: ${data.timestamp}`,
                        ]);
                    }
                } catch (error) {
                    console.error('Error parsing message data:', error);
                }
            });
    
            return () => {
                // Unsubscribe from topics
                client.unsubscribe(['rpi/mlu/data', 'rpi/10000000bab0b141/status'], (err) => {
                    if (err) {
                        console.error('Unsubscribe error:', err);
                    } else {
                        console.log('Unsubscribed from topics');
                    }
                });

                if (dataTimeoutRef.current) {
                    clearTimeout(dataTimeoutRef.current);
                }
                
                client.end();
                setIsConnected(false);
                setIsConnecting(false);
                setIsOnline(false);
                console.log('Disconnected from MQTT broker');
                
            };
        }
    }, [connectWebSocket]);
    

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
            if (timerRef.current) {
                clearInterval(timerRef.current);
                timerRef.current = null;
            }
            publishMessage('stopRecord');
        } else {
            setIsRecording(true);
            setElapsedTime(0);
            timerRef.current = setInterval(() => {
                setElapsedTime((prevTime) => prevTime + 1);
            }, 1000);
            publishMessage('startRecord');
        }
    };

    const publishMessage = (command: string) => {
        if (isConnected) {
            client.publish('rpi/10000000bab0b141/command',
                JSON.stringify({ command }),
                (err) => {
                    if (err) {
                        console.log(err);
                    }
                    console.log(`Published ${command} command`);
                });
        }
    };

    useEffect(() => {
        if (isAutoMode) {
            publishMessage('normalRecord');
        } else {
            publishMessage('stopRecord');
        }
    }, [isAutoMode]);

    const reset = () => {
        setMluData([]);
        setElapsedTime(0);
    };

    const formatElapsedTime = (seconds: number) => {
        const hrs = Math.floor(seconds / 3600);
        const mins = Math.floor((seconds % 3600) / 60);
        const secs = seconds % 60;
        return `${hrs.toString().padStart(2, '0')}:${mins.toString().padStart(2, '0')}:${secs.toString().padStart(2, '0')}`;
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

                <div className="py-4 flex">
                    <div className="flex flex-row items-center mr-4">
                        <span className="text-lg font-bold">Predict Status</span>
                        <div className={`w-4 h-4 rounded-full ${isOnline ? 'bg-green-500' : 'bg-red-500'} ml-2`}></div>
                    </div>
                    <button
                        className={`${connectWebSocket ? 'bg-red-500 hover:bg-red-600' : 'bg-green-500 hover:bg-green-600'} text-white rounded-md p-2`}
                        onClick={() => setConnectWebSocket(!connectWebSocket)}
                        disabled={isConnecting}
                    >
                        {connectWebSocket ? 'Disconnect' : 'Connect'}
                    </button>
                    <button
                        className='bg-blue-500 hover:bg-blue-600 text-white rounded-md p-2 ml-2'
                        onClick={reset}
                    >
                        Reset
                    </button>
                    <div className="border-2 rounded-md h-14 mx-4 border-gray-300"></div>
                    <div className="flex gap-4 mr-4">
                        <div>
                            <label className="text-lg font-bold">
                                Recording Mode
                            </label>
                            <div>
                                {isAutoMode ? 'Auto' : 'Manual'}
                            </div>
                        </div>    
                        <label className="relative inline-flex items-center cursor-pointer">
                            <input
                                type="checkbox"
                                className="sr-only"
                                checked={isAutoMode}
                                onChange={() => setIsAutoMode(!isAutoMode)}
                                disabled={isRecording || !isConnected}
                            />
                            <div className="w-11 h-6 bg-gray-200 rounded-full peer peer-focus:ring-4 peer-focus:ring-blue-300 dark:peer-focus:ring-blue-800">
                                <div
                                    className={`w-5 h-5 bg-white rounded-full shadow-md transform transition-transform duration-300 ease-in-out ${
                                        isAutoMode ? 'translate-x-5' : 'translate-x-0'
                                    }`}
                                ></div>
                            </div>
                        </label>
                    </div>
                    {!isAutoMode &&
                    <div className="mr-4">
                        <span className="text-lg font-bold">Elapsed Time</span>
                        <div>{formatElapsedTime(elapsedTime)}</div>
                    </div>}
                    {!isAutoMode &&
                    <button
                        className={`${isRecording ? 'bg-red-900 hover:bg-red-950' : 'bg-red-500 hover:bg-red-600'} text-white rounded-md p-2`}
                        onClick={handleStartRecording}
                        disabled={!isOnline || !isConnected}
                    >
                        {isRecording ? 'Stop Recording' : 'Start Recording'}
                    </button>}
                </div>

                <div className="flex flex-row justify-between">
                    <LineChartComponentForPi
                        title={'Predicted'}
                        description={'ผลการทำนายจาก Raspberry Pi'}
                        chartData={mluData}
                        chartConfig={mluConfig}
                        color={'#a768de'}
                    />
                    <div className='border-2 rounded-lg shadow-sm min-w-[40em]'>
                        <TableComponentForPi tabledatas={mluData} />
                    </div>
                </div>

                <div className="mt-4 p-4 bg-gray-100 border border-gray-300 rounded-md">
                    <span className="text-md font-semibold">Log Status:</span>
                    <div className="text-sm text-gray-700">
                        {logStatus.length > 0 ? (
                            logStatus.map((log, index) => (
                                <div key={index}>{log}</div>
                            ))
                        ) : (
                            "No log updates available."
                        )}
                    </div>
                </div>

            </main>
        </div>
    );
}