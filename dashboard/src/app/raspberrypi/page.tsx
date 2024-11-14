'use client'

import React, { useState } from "react";
import TableComponent from "@/components/TableComponent";
import axios from 'axios';
import { NEXT_PUBLIC_BACKENDSERVER } from "./config";

export default function RaspberryPi() {
    const [sounds, setSounds] = useState([]);
    const [apiKey, setApiKey] = useState('');
    const [connectBackend, setConnectBackend] = useState(false);
    const [isRecording, setIsRecording] = useState(false);

    const getSounds = () => {
        if (connectBackend) {
            setConnectBackend(!connectBackend);
            return;
        }
        else if (apiKey === '') {
            alert('โปรดใส่ API Key');
            return;
        }
        else {
            axios.get(`${NEXT_PUBLIC_BACKENDSERVER}/sounds`, {
                headers: {
                    Authorization: `Bearer ${apiKey}`
                }
            }).then((res) => {
                setSounds(res.data);
                setConnectBackend(!connectBackend);
                console.log(res.data);
            }).catch((err) => {
                console.log(err);
            }
        );
        }
    }

    return (
        <div className="p-8 pb-20 gap-16 sm:p-20 min-h-screen">
        <main className="font-LINESeedSansTH_W_Rg">
            <div className='flex py-4'>
                <span className="text-6xl font-bold">Raspberry Pi Controller</span>
            </div>
            <p className="text-lg text-gray-500 py-4 flex">
                แผงควบคุม Raspberry Pi สำหรับงาน Machine Learning
            </p>

            <div className="flex flex-wrap gap-4 py-4">
                <input
                type="text"
                className="border rounded px-4 py-4 w-96 text-lg"
                placeholder="โปรดใส่ API Key"
                value={apiKey}
                onChange={(e) => setApiKey(e.target.value)}
                />
                <button
                    className={`mx-4 px-6 py-2 text-white rounded hover:scale-105 transition-all ${connectBackend ? 'bg-red-500 hover:bg-red-600' : 'bg-green-500 hover:bg-green-600'}`}
                    onClick={getSounds}
                    >
                    {connectBackend ? 'Disconnect' : 'Connect'}
                </button>
            </div>
            
            <div className='border-2 rounded-lg p-6 shadow-sm mb-6 mt-6'>
                ไฟล์ที่บันทึกล่าสุด
                <TableComponent tabledatas={sounds} />
            </div>

            <button className={`${isRecording ? 'bg-red-500 hover:bg-red-600' : 'bg-green-500 hover:bg-green-600'} text-white rounded-md p-2`} onClick={() => setIsRecording(!isRecording)}>
                {isRecording ? 'Stop Recording' : 'Start Recording'}
            </button>

        </main>
        </div>
    );
}
