'use client'

import TableComponent from "@/components/TableComponent";
import React, { useState } from "react";

export default function RaspberryPi() {
    const invoices = [
        { id: "INV001", filename: "Paid", method: "Credit Card", amount: 250.0 },
        { id: "INV002", filename: "Pending", method: "Bank Transfer", amount: 320.0 },
        { id: "INV003", filename: "Paid", method: "PayPal", amount: 180.0 },
      ]
    const [isRecording, setIsRecording] = useState(false);

    return (
        <div className="p-8 pb-20 gap-16 sm:p-20 min-h-screen">
        <main className="font-LINESeedSansTH_W_Rg">
            <div className='flex py-4'>
                <span className="text-6xl font-bold">Raspberry Pi Controller</span>
            </div>
            <p className="text-lg text-gray-500 py-4 flex">
                แผงควบคุม Raspberry Pi สำหรับงาน Machine Learning
            </p>
            
            <button className={`${isRecording ? 'bg-red-500 hover:bg-red-600' : 'bg-green-500 hover:bg-green-600'} text-white rounded-md p-2`} onClick={() => setIsRecording(!isRecording)}>
                {isRecording ? 'Stop Recording' : 'Start Recording'}
            </button>

            <div className='border-2 rounded-lg p-6 shadow-sm mb-6 mt-6'>
                ไฟล์ที่บันทึกล่าสุด
                <TableComponent tabledatas={invoices} />
            </div>


        </main>
        </div>
    );
}
