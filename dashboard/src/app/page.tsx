'use client';

import React, { useState, useEffect } from 'react';
import { LineChartComponent } from "@/components/line-chart";

// Utility function to parse Thai Buddhist calendar datetime into JavaScript Date
const parseThaiDateTime = (thaiDateTime: string): Date => {
  // console.log('Parsing Thai datetime:', thaiDateTime);
  const [datePart, timePart] = thaiDateTime.split(" ");
  const [day, month, year] = datePart.split("/").map(Number);
  const [hours, minutes, seconds] = timePart.split(":").map(Number);

  // Convert Buddhist year to Gregorian year
  const gregorianYear = year - 543;

  return new Date(gregorianYear, month - 1, day, hours, minutes, seconds);
};

export default function Home() {
  const [apiKey, setApiKey] = useState('');
  const [connectWebSocket, setConnectWebSocket] = useState(false);
  const [cycleCount, setCycleCount] = useState<string[]>([]);
  const [power, setPower] = useState<number[]>([]);
  const [pressure, setPressure] = useState<number[]>([]);
  const [force, setForce] = useState<number[]>([]);
  const [punchPosition, setPunchPosition] = useState<number[]>([]);
  const [reset, setReset] = useState<boolean>(false);

  // Filters with datetime strings
  const [startSample, setStartSample] = useState<string>("14/11/2567 00:00:00");
  const [endSample, setEndSample] = useState<string>("14/11/2567 23:59:59");

  useEffect(() => {
    setStartSample(new Date().toLocaleString("th-TH", {
      year: "numeric",
      month: "2-digit",
      day: "2-digit",
      hour: "2-digit",
      minute: "2-digit",
      second: "2-digit",
    }));
  }, [, reset]);

  // Add 10 minutes to current datetime
  useEffect(() => {
    setEndSample(new Date(parseThaiDateTime(startSample).getTime() + 600000).toLocaleString("th-TH", {
      year: "numeric",
      month: "2-digit",
      day: "2-digit",
      hour: "2-digit",
      minute: "2-digit",
      second: "2-digit",
    }));
  }, [startSample]);

  
  // WebSocket connection and handling
  useEffect(() => {
    let ws: WebSocket | null = null;

    if (connectWebSocket) {
      ws = new WebSocket('wss://openfruit-tesa-simulation-test.onrender.com/ws');

      ws.onopen = () => {
        console.log('WebSocket connected.');
        ws?.send(apiKey);
      };

      ws.onmessage = (event) => {
        try {
          const response = JSON.parse(event.data);
          console.log('WebSocket data received:', response);

          const newCycleCount = new Date().toLocaleString("th-TH", {
            year: "numeric",
            month: "2-digit",
            day: "2-digit",
            hour: "2-digit",
            minute: "2-digit",
            second: "2-digit",
          });

          const newPower = response["Energy Consumption"]["Power"];
          const newPressure = response["Pressure"];
          const newForce = response["Force"];
          const newPosition = response["Position of the Punch"];

          // setCycleCount((prev) => [...prev, newCycleCount].slice(-200));
          // setPower((prev) => [...prev, newPower].slice(-200));
          // setPressure((prev) => [...prev, newPressure].slice(-200));
          // setForce((prev) => [...prev, newForce].slice(-200));
          // setPunchPosition((prev) => [...prev, newPosition].slice(-200));

          setCycleCount((prev) => {
            const updatedCycleCount = [...prev, newCycleCount];
            return updatedCycleCount.length > 200 ? [newCycleCount] : updatedCycleCount;
          });
      
          setPower((prev) => {
            const updatedPower = [...prev, newPower];
            return updatedPower.length > 200 ? [newPower] : updatedPower;
          });
      
          setPressure((prev) => {
            const updatedPressure = [...prev, newPressure];
            return updatedPressure.length > 200 ? [newPressure] : updatedPressure;
          });
      
          setForce((prev) => {
            const updatedForce = [...prev, newForce];
            return updatedForce.length > 200 ? [newForce] : updatedForce;
          });
      
          setPunchPosition((prev) => {
            const updatedPunchPosition = [...prev, newPosition];
            return updatedPunchPosition.length > 200 ? [newPosition] : updatedPunchPosition;
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

  // Function to filter data by start and end datetime
  const filterDataByDateTime = (data: number[], cycleData: string[]) => {
    const start = parseThaiDateTime(startSample).getTime();
    const end = parseThaiDateTime(endSample).getTime();

    return data.filter((_, index) => {
      const timestamp = parseThaiDateTime(cycleData[index]).getTime();
      return timestamp >= start && timestamp <= end;
    });
  };

  // Filtered data
  const filteredPower = filterDataByDateTime(power, cycleCount);
  const filteredPressure = filterDataByDateTime(pressure, cycleCount);
  const filteredForce = filterDataByDateTime(force, cycleCount);
  const filteredPunchPosition = filterDataByDateTime(punchPosition, cycleCount);

  // Prepare chart data
  const createChartData = (filteredData: number[]) =>
    filteredData.map((_, index) => ({
      cycleCount: new Date().toLocaleString("th-TH", {
        year: "numeric",
        month: "2-digit",
        day: "2-digit",
        hour: "2-digit",
        minute: "2-digit",
        second: "2-digit",
      }),
      var1: filteredData[index],
    }));

  const powerChartData = createChartData(filteredPower);
  const pressureChartData = createChartData(filteredPressure);
  const forceChartData = createChartData(filteredForce);
  const punchPositionChartData = createChartData(filteredPunchPosition);

  const powerLineChartConfig = {
    responsive: true,
    scales: {
      x: {
        type: 'linear',
        position: 'bottom',
        title: {
          display: true,
          text: 'Datetime',
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
          text: 'Datetime',
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
          text: 'Datetime',
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
          text: 'Datetime',
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
    <div className="p-8 pb-20 gap-16 sm:p-20 min-h-screen">
      <main className="font-LINESeedSansTH_W_Rg">
        <div className='flex py-4'>
          <span className="text-6xl font-bold">Welcome to </span>
          <span className="text-6xl font-bold bg-clip-text text-transparent bg-gradient-to-r from-green-400 to-orange-400">
            &nbsp;OpenFruit
          </span>
        </div>
        <p className="text-lg text-gray-500 py-4 flex">
          An extraordinary dashboard for TESA Top Gun Rally 2024
        </p>
        <div className='border-2 rounded-lg p-6 w-96 shadow-sm mb-6'>
          <div className="flex flex-wrap gap-4 py-4">
            <input
              type="text"
              className="border rounded px-4 py-4 w-96 text-lg"
              placeholder="ไม่จำเป็นต้องใส่ API Key"
              value={apiKey}
              disabled={true}
              onChange={(e) => setApiKey(e.target.value)}
            />
            <div>
              <button
                className={`mx-4 px-6 py-2 text-white rounded hover:scale-105 transition-all ${connectWebSocket ? 'bg-red-500 hover:bg-red-600' : 'bg-green-500 hover:bg-green-600'}`}
                onClick={() => setConnectWebSocket(!connectWebSocket)}
              >
                {connectWebSocket ? 'Disconnect' : 'Connect'}
              </button>
              <button
                className='mx-4 px-6 py-2 text-white rounded hover:scale-105 transition-all bg-blue-500 hover:bg-blue-600'
                onClick={() => setReset(!reset)}
              >
                Reset date
              </button>
            </div>
          </div>

          <div className="flex flex-col py-4">
            <div className="flex justify-between md:w-1/3">
              <label className="font-LINESeedSansTH_W_Bd pr-2">Start:</label>
              <input
                type="datetime"
                value={startSample}
                onChange={(e) => setStartSample(e.target.value)}
                className="border p-2"
              />
            </div>
            <div className="flex justify-between md:w-1/3 pt-2">
              <label className="font-LINESeedSansTH_W_Bd pr-5">End:</label>
              <input
                type="datetime"
                value={endSample}
                onChange={(e) => setEndSample(e.target.value)}
                className="border p-2"
              />
            </div>

            <div className="pt-2">
              <label className="font-LINESeedSansTH_W_Bd">Number of samples: </label>
              {numberOfSamples}/{totalSamples}
            </div>
          </div>
        </div>

        <div className='gap-4 flex flex-col md:w-screen w-full'>
          <div className='w-full md:w-3/4'>
            <LineChartComponent title={'Energy Consumption'} description={'การใช้พลังงานของเครื่องจักร'} chartData={powerChartData} chartConfig={powerLineChartConfig} varname={'กำลัง'} color={'#8884d8'}/>
          </div>
          <div className='w-full md:w-3/4'>
            <LineChartComponent title={'Pressure'} description={'ค่าความดันของเครื่องจักร'} chartData={pressureChartData} chartConfig={pressureLineChartConfig} varname={'ความดัน'} color={'#82ca9d'}/>
          </div>
          <div className='w-full md:w-3/4'>
            <LineChartComponent title={'Force'} description={'แรงที่กระทำของเครื่องจักร'} chartData={forceChartData} chartConfig={forceLineChartConfig} varname={'แรง'} color={'#f06c7a'}/>
          </div>
          <div className='w-full md:w-3/4'>
            <LineChartComponent title={'Punch Position'} description={'ตำแหน่งของหัวแม่แรง'} chartData={punchPositionChartData} chartConfig={punchPositionLineChartConfig} varname={'ตำแหน่ง'} color={'#a768de'}/>
          </div>
        </div>
      </main>
    </div>
  );
}
