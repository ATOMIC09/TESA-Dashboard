/* eslint-disable @typescript-eslint/no-explicit-any */
"use client";

import { useState } from "react";
import {
  CartesianGrid,
  Line,
  LineChart,
  XAxis,
  YAxis,
  Tooltip,
  Brush,
  ReferenceArea,
} from "recharts";
import {
  Card,
  CardContent,
  CardDescription,
  CardFooter,
  CardHeader,
  CardTitle,
} from "@/components/ui/card";
import { ChartContainer } from "@/components/ui/chart";

interface LineChartComponentProps {
  title: string;
  description: string;
  chartData: Array<{
    cycleCount: string;
    [key: string]: number | string;
  }>;
  chartConfig: any;
  varname: string;
  color: string;
}

export const LineChartComponent: React.FC<LineChartComponentProps> = ({
  title,
  description,
  chartData,
  chartConfig,
  varname,
  color,
}) => {
  const [zoomDomain, setZoomDomain] = useState<{ x1: number | null; x2: number | null }>({
    x1: null,
    x2: null,
  });

  const [selectionArea, setSelectionArea] = useState<{ startX: number | null; endX: number | null }>({
    startX: null,
    endX: null,
  });

  const handleMouseDown = (e: any) => {
    if (e && e.activeLabel != null) {
      setSelectionArea({ startX: e.activeLabel, endX: null });
    }
  };

  const handleMouseUp = () => {
    if (selectionArea.startX !== null && selectionArea.endX !== null) {
      const [x1, x2] = [
        Math.min(selectionArea.startX, selectionArea.endX),
        Math.max(selectionArea.startX, selectionArea.endX),
      ];
      setZoomDomain({ x1, x2 });
    }
    setSelectionArea({ startX: null, endX: null });
  };

  return (
    <Card>
      <CardHeader>
        <CardTitle>{title}</CardTitle>
        <CardDescription>{description}</CardDescription>
      </CardHeader>
      <CardContent>
        <ChartContainer config={chartConfig}>
          <LineChart
            data={chartData}
            margin={{
              left: 12,
              right: 12,
            }}
            onMouseDown={handleMouseDown}
            onMouseUp={handleMouseUp}
          >
            <CartesianGrid vertical={false} />
            <XAxis
              dataKey="cycleCount"
              tickLine={false}
              axisLine={false}
              tickMargin={8}
              tickFormatter={(value) => value.toString()}
              domain={
                zoomDomain.x1 !== null && zoomDomain.x2 !== null
                  ? [zoomDomain.x1, zoomDomain.x2]
                  : ["auto", "auto"]
              }
            />
            <YAxis domain={["auto", "auto"]} />
            <Tooltip />
            {selectionArea.startX !== null && selectionArea.endX !== null && (
              <ReferenceArea
                x1={selectionArea.startX}
                x2={selectionArea.endX}
                strokeOpacity={0.3}
                fill="#8884d8"
              />
            )}
            <Brush height={30} />
            <Line
              dataKey="var1"
              name={varname}
              type="monotone"
              stroke={color}
              strokeWidth={2}
              dot={false}
              animationDuration={1}
            />
          </LineChart>
        </ChartContainer>
      </CardContent>
      <CardFooter className="flex justify-center">
      </CardFooter>
    </Card>
  );
};
