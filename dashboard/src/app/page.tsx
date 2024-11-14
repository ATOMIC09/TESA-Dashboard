'use client';

import React, { useState, useEffect } from 'react';
import { LineChartComponent } from "@/components/line-chart";

export default function Home() {
  const [apiKey, setApiKey] = useState('');
  const [connectWebSocket, setConnectWebSocket] = useState(false);
  const [cycleCount, setCycleCount] = useState<number[]>([]);
  const [power, setPower] = useState<number[]>([]);
  const [pressure, setPressure] = useState<number[]>([]);
  const [force, setForce] = useState<number[]>([]);
  const [punchPosition, setPunchPosition] = useState<number[]>([]);

  // WebSocket connection and handling
  useEffect(() => {
    let ws: WebSocket | null = null;

    if (connectWebSocket) {
      ws = new WebSocket('ws://technest.ddns.net:8001/ws');

      ws.onopen = () => {
        console.log('WebSocket connected.');
        ws?.send(apiKey);
      };

      ws.onmessage = (event) => {
        try {
          const response = JSON.parse(event.data);
          console.log('WebSocket data received:', response); // Log raw response

          // Extract data voltage
          const newCycleCount = response["Cycle Count"];
          const newPower = response["Energy Consumption"]["Power"];
          const newPressure = response["Pressure"];
          const newForce = response["Force"];
          const newPosition = response["Position of the Punch"];

          // Check if the length exceeds 200 and reset the state if true
          setCycleCount((prevCycleCount) => {
            const updatedCycleCount = [...prevCycleCount, newCycleCount];
            return updatedCycleCount.length > 200 ? [] : updatedCycleCount;
          });

          setPower((prevPower) => {
            const updatedPower = [...prevPower, newPower];
            return updatedPower.length > 200 ? [] : updatedPower;
          });

          setPressure((prevPressure) => {
            const updatedPressure = [...prevPressure, newPressure];
            return updatedPressure.length > 200 ? [] : updatedPressure;
          });

          setForce((prevForce) => {
            const updatedForce = [...prevForce, newForce];
            return updatedForce.length > 200 ? [] : updatedForce;
          });

          setPunchPosition((prevPosition) => {
            const updatedPosition = [...prevPosition, newPosition];
            return updatedPosition.length > 200 ? [] : updatedPosition;
          });

        } catch (error) {
          console.error('Error parsing WebSocket data:', error);
        }
      };

      ws.onclose = () => console.log('WebSocket disconnected.');
    }

    return () => {
      if (ws) {
        ws.close();
      }
    };
  }, [connectWebSocket, apiKey]);

  const powerChartData = power.map((_, index) => ({
    cycleCount: cycleCount[index],
    var1: power[index],
  }));

  const pressureChartData = pressure.map((_, index) => ({
    cycleCount: cycleCount[index],
    var1: pressure[index],
  }));

  const forceChartData = force.map((_, index) => ({
    cycleCount: cycleCount[index],
    var1: force[index],
  }));

  const punchPositionChartData = punchPosition.map((_, index) => ({
    cycleCount: cycleCount[index],
    var1: punchPosition[index],
  }));

  const powerLineChartConfig = {
    responsive: true,
    scales: {
      x: {
        type: 'linear',
        position: 'bottom',
        title: {
          display: true,
          text: 'Cycle Count',
        },
      },
      y: {
        title: {
          display: true,
          text: 'Power (W)',
        },
      },
    },
  };

  const pressureLineChartConfig = {
    responsive: true,
    scales: {
      x: {
        type: 'linear',
        position: 'bottom',
        title: {
          display: true,
          text: 'Cycle Count',
        },
      },
      y: {
        title: {
          display: true,
          text: 'Pressure (MPa)',
        },
      },
    },
  };

  const forceLineChartConfig = {
    responsive: true,
    scales: {
      x: {
        type: 'linear',
        position: 'bottom',
        title: {
          display: true,
          text: 'Cycle Count',
        },
      },
      y: {
        title: {
          display: true,
          text: 'Force (N)',
        },
      },
    },
  };

  const punchPositionLineChartConfig = {
    responsive: true,
    scales: {
      x: {
        type: 'linear',
        position: 'bottom',
        title: {
          display: true,
          text: 'Cycle Count',
        },
      },
      y: {
        title: {
          display: true,
          text: 'Position (mm)',
        },
      },
    },
  };

  const numberOfSamples = cycleCount.length;
  const totalSamples = 200;
  
  return (
    <div className="items-center justify-items-center min-h-screen p-8 pb-20 gap-16 sm:p-20">
      <main className="font-LINESeedSansTH_W_Rg">
        <div className='flex justify-center py-4'>
          <span className="text-6xl font-bold">Welcome to </span>
          <span className="text-6xl font-bold bg-clip-text text-transparent bg-gradient-to-r from-green-400 to-orange-400">
          &nbsp;OpenFruit
          </span>
        </div>
        <p className="text-lg text-gray-500 py-2 flex justify-center">
          An extraordinary dashboard for TESA Top Gun Rally 2024
        </p>
        <div className="flex flex-wrap gap-4 items-center justify-center py-4">
          <input
            type="text"
            className="border rounded px-4 py-4 w-96 text-lg"
            placeholder="โปรดใส่ API Key"
            value={apiKey}
            onChange={(e) => setApiKey(e.target.value)}
          />
          <button
            className={`mx-4 px-6 py-2 text-white rounded hover:scale-105 transition-all ${connectWebSocket ? 'bg-red-500 hover:bg-red-600' : 'bg-green-500 hover:bg-green-600' 
              }`}
            onClick={() => setConnectWebSocket(!connectWebSocket)}
          >
            {connectWebSocket ? 'Disconnect' : 'Connect'}
          </button>
        </div>
        <div>
          <p className="text-lg text-gray-500 py-2 flex justify-center">
            Number of samples: {numberOfSamples}/{totalSamples}
          </p>
        </div>
        <div className='gap-4 items-center justify-center flex flex-col w-screen'>
          <div className='w-3/4 px-8'>
            <LineChartComponent title={'Energy Consumption'} description={'การใช้พลังงานของเครื่องจักร'} chartData={powerChartData} chartConfig={powerLineChartConfig} varname={'กำลัง'} color={'#8884d8'}/>
          </div>
          <div className='w-3/4 px-8'>
            <LineChartComponent title={'Pressure'} description={'ค่า Square Wave ที่แสดงถึงความดันของ Punch'} chartData={pressureChartData} chartConfig={pressureLineChartConfig} varname={'ความดัน'} color={'#82ca9d'} />
          </div>
          <div className='w-3/4 px-8'>
            <LineChartComponent title={'Force'} description={'ค่า Square Wave ที่แสดงถึงแรงของ Punch'} chartData={forceChartData} chartConfig={forceLineChartConfig} varname={'แรง'} color={'#ff7300'} />
          </div>
          <div className='w-3/4 px-8'>
            <LineChartComponent title={'Punch Position'} description={'ค่า Triangle wave ที่แสดงถึงตำแหน่งของ Punch'} chartData={punchPositionChartData} chartConfig={punchPositionLineChartConfig} varname={'ตำแหน่ง'} color={'#ff0000'}/>
          </div>
        </div>
      </main>
    </div>
  );
}
