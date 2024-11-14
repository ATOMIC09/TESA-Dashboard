'use client'

import React, { useState } from "react";
import TableComponent from "@/components/TableComponent";
import axios from 'axios';
import { NEXT_PUBLIC_BACKENDSERVER } from "@/app/server/config";

export default function Server() {
    const [sounds, setSounds] = useState([]);
    const [apiKey, setApiKey] = useState('');
    // const [isRecording, setIsRecording] = useState(false);
    const [file, setFile] = useState<File | null>(null);
    const [deviceId, setDeviceId] = useState('');

    const getSounds = () => {
        if (apiKey === '') {
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
                console.log(res.data);
            }).catch((err) => {
                console.log(err);
            }
        );
        }
    }

    const handleFileChange = (event: React.ChangeEvent<HTMLInputElement>) => {
        const selectedFile = event.target.files ? event.target.files[0] : null;
        setFile(selectedFile);
    };

    // Function to upload the file to the server
    const handleUpload = () => {
        if (!file) {
            alert("Please select a file to upload.");
            return;
        }

        if (apiKey === '') {
            alert('โปรดใส่ API Key');
            return;
        }

        if (deviceId === '') {
            alert('โปรดใส่ Device ID');
            return;
        }
        
        const formData = new FormData();
        formData.append("file", file);
        formData.append("deviceId", deviceId);
        formData.append("timeStamp", new Date().toISOString());

        axios.post(`${NEXT_PUBLIC_BACKENDSERVER}/sound`, formData, {
            headers: {
            "Content-Type": "multipart/form-data",
            Authorization: `Bearer ${apiKey}`
            }
        })
        .then((response) => {
            alert("File uploaded successfully!");
            // Refresh table
            axios.get(`${NEXT_PUBLIC_BACKENDSERVER}/sounds`, {
                headers: {
                    Authorization: `Bearer ${apiKey}`
                }
            }).then((res) => {
                setSounds(res.data);

            }).catch((err) => {
                console.log(err);
            }
            );
        })
        .catch((error) => {
            console.error("There was an error uploading the file:", error);
            alert("Error uploading file.");
        });
    };

    return (
        <div className="p-8 pb-20 gap-16 sm:p-20 min-h-screen">
        <main className="font-LINESeedSansTH_W_Rg">
            <div className='flex py-4'>
                <span className="text-6xl font-bold">Server Controller</span>
            </div>
            <p className="text-lg text-gray-500 py-4 flex">
                แผงควบคุม Server
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
                    className='mx-4 px-6 py-2 text-white rounded hover:scale-105 transition-all bg-green-500 hover:bg-green-600'
                    onClick={getSounds}
                    >
                    Fetch data from server
                </button>
            </div>
            
            {/* File table */}
            <div className='border-2 rounded-lg p-6 shadow-sm mb-6 mt-6'>
                ไฟล์ที่มีอยู่ในเซิร์ฟเวอร์
                <TableComponent tabledatas={sounds} />
            </div>

            {/* Upload component */}
            <div className='border-2 rounded-lg p-6 shadow-sm mb-6 mt-6'>
                อัปโหลดไฟล์ไปยังเซิร์ฟเวอร์
                <div className="flex flex-col">
                    <input
                        type="text"
                        className="border rounded px-1 py-1"
                        placeholder="Device ID"
                        onChange={(e) => setDeviceId(e.target.value)}
                    />
                    <input
                        type="file"
                        className="py-4"
                        onChange={handleFileChange}
                    />
                    <button
                        className="bg-green-500 hover:bg-green-600 text-white rounded-md p-2"
                        onClick={handleUpload}
                        >
                        Upload
                    </button>
                </div>
            </div>
        </main>
        </div>
    );
}
