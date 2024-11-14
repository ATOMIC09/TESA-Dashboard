'use client';

import React, { useState, useEffect } from 'react';
import { LineChartComponent } from "@/components/line-chart";

export default function Home() {
  const [apiKey, setApiKey] = useState('');
  const [connectWebSocket, setConnectWebSocket] = useState(false);

  // States to store historical data for chart
  const [voltageL1, setVoltageL1] = useState<number[]>([]);
  const [voltageL2, setVoltageL2] = useState<number[]>([]);
  const [voltageL3, setVoltageL3] = useState<number[]>([]);
  const [cycleCount, setCycleCount] = useState<number[]>([]);
  const [power, setPower] = useState<number[]>([]);
  const [pressure, setPressure] = useState<number[]>([]);
  const [force, setForce] = useState<number[]>([]);
  const [punchPosition, setPunchPosition] = useState<number[]>([]);


  interface LineChartComponentProps {
    title: string;
    description: string;
    chartData: number[];
    chartConfig: {};
  }

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
          const newVoltageL1 = response["Voltage"]["L1-GND"];
          const newVoltageL2 = response["Voltage"]["L2-GND"];
          const newVoltageL3 = response["Voltage"]["L3-GND"];
          const newPower = response["Energy Consumption"]["Power"];
          const newPressure = response["Pressure"];
          const newForce = response["Force"];
          const newPosition = response["Position of the Punch"];

          // Append new data to the existing data arrays and limit to last 10 items
          setCycleCount((prevCycleCount) => {
            const updatedCycleCount = [...prevCycleCount, newCycleCount];
            return updatedCycleCount.slice(-10);
          });

          setVoltageL1((prevL1) => {
            const updatedL1 = [...prevL1, newVoltageL1];
            return updatedL1.slice(-10);
          });

          setVoltageL2((prevL2) => {
            const updatedL2 = [...prevL2, newVoltageL2];
            return updatedL2.slice(-10);
          });

          setVoltageL3((prevL3) => {
            const updatedL3 = [...prevL3, newVoltageL3];
            return updatedL3.slice(-10);
          });

          setPower((prevPower) => {
            const updatedPower = [...prevPower, newPower];
            return updatedPower.slice(-10);
          });

          setPressure((prevPressure) => {
            const updatedPressure = [...prevPressure, newPressure];
            return updatedPressure.slice(-10);
          });

          setForce((prevForce) => {
            const updatedForce = [...prevForce, newForce];
            return updatedForce.slice(-10);
          });

          setPunchPosition((prevPosition) => {
            const updatedPosition = [...prevPosition, newPosition];
            return updatedPosition.slice(-10);
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

  // Prepare chart data from historical data
  const voltageChartData = voltageL1.map((_, index) => ({
    cycleCount: cycleCount[index],
    var1: voltageL1[index],
    var2: voltageL2[index],
    var3: voltageL3[index],
  }));

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
  
  const voltageLineChartConfig = {
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
          text: 'Voltage (V)',
        },
      },
    },
  };

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
            className={`mx-4 px-6 py-2 text-white rounded hover:scale-105 transition-all ${connectWebSocket ? 'bg-red-500' : 'bg-green-500'
              }`}
            onClick={() => setConnectWebSocket(!connectWebSocket)}
          >
            {connectWebSocket ? 'Disconnect' : 'Connect'}
          </button>
        </div>
        <div className='gap-4 items-center justify-center grid grid-cols-3'>
          <div className='w-full'>
            <LineChartComponent title={'Power'} description={'กราฟแสดงการเปรียบเทียบพลังงานในแต่ละ Cycle'} chartData={powerChartData} chartConfig={powerLineChartConfig} />
          </div>
          <div className='w-full'>
            <LineChartComponent title={'Voltage'} description={'กราฟแสดงการเปรียบเทียบแรงดันไฟฟ้าในแต่ละ Line เทียบ Ground'} chartData={voltageChartData} chartConfig={voltageLineChartConfig} />
          </div>
          <div className='w-full'>
            <LineChartComponent title={'Pressure'} description={'กราฟแสดงการเปรียบเทียบความดันในแต่ละ Cycle'} chartData={pressureChartData} chartConfig={pressureLineChartConfig} />
          </div>
          <div className='w-full'>
            <LineChartComponent title={'Force'} description={'กราฟแสดงการเปรียบเทียบแรงในแต่ละ Cycle'} chartData={forceChartData} chartConfig={forceLineChartConfig} />
          </div>
          <div className='w-full'>
            <LineChartComponent title={'Punch Position'} description={'กราฟแสดงการเปรียบเทียบตำแหน่งของ Punch ในแต่ละ Cycle'} chartData={punchPositionChartData} chartConfig={punchPositionLineChartConfig} />
          </div>
        </div>
      </main>
    </div>
  );
}
