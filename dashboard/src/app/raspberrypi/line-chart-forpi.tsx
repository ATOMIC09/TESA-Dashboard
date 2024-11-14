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
import { ChartConfig, ChartContainer } from "@/components/ui/chart";

interface LineChartComponentProps {
  title: string;
  description: string;
  chartData: Array<{
    created_at: string; // ISO string timestamp
    classification: string;
    confidence: number; // Add confidence to data structure
  }>;
  chartConfig: ChartConfig;
  color: string;
}

const classificationMapping = {
  X: "Unknown",
  N: "Normal",
  F: "Fault",
};

const classificationToNumber = {
  X: 1,
  N: 2,
  F: 3,
};

export const LineChartComponentForPi: React.FC<LineChartComponentProps> = ({
  title,
  description,
  chartData,
  chartConfig,
  color,
}) => {
  const [zoomDomain, setZoomDomain] = useState<{ x1: number | null; x2: number | null }>({
    x1: null,
    x2: null,
  });

  // Prepare data for recharts (convert classification to numerical scale)
  const formattedData = chartData.map((item) => ({
    ...item,
    formattedTime: new Date(item.created_at).toLocaleString("th-TH"), // Format time in Thai locale
    classificationValue: classificationToNumber[item.classification] || 0, // Map classification to a number
  }));

  // Handle Brush change to update zoomDomain
  const handleBrushChange = (newDomain: any) => {
    if (newDomain && newDomain.length === 2) {
      const [x1, x2] = newDomain;
      setZoomDomain({ x1, x2 });
    }
  };

  return (
    <Card className="mr-8 w-[45vw]">
      <CardHeader>
        <CardTitle>{title}</CardTitle>
        <CardDescription>{description}</CardDescription>
      </CardHeader>
      <CardContent>
        <ChartContainer config={chartConfig}>
          <LineChart
            data={formattedData}
            margin={{
              left: 12,
              right: 12,
            }}
          >
            <CartesianGrid vertical={false} />
            <XAxis
              dataKey="formattedTime"
              tickLine={false}
              axisLine={false}
              tickMargin={8}
              tickFormatter={(value) => value} // Time already formatted to Thai locale
              domain={
                zoomDomain.x1 !== null && zoomDomain.x2 !== null
                  ? [zoomDomain.x1, zoomDomain.x2]
                  : ["auto", "auto"]
              }
            />
            <YAxis
              domain={[0, 4]} // Adjust domain to fit classification and confidence values
              tickFormatter={(value) =>
                value <= 3
                  ? Object.entries(classificationToNumber).find(
                      ([, num]) => num === value
                    )?.[0] || ""
                  : value.toFixed(2) // Show confidence as decimal
              }
            />
            <Tooltip
              formatter={(value: any, name: any, props: any) =>
                name === "classificationValue"
                  ? classificationMapping[props.payload.classification]
                  : value
              }
              labelFormatter={(label: string) => `Time: ${label}`}
            />
            <Brush height={30} onChange={handleBrushChange} />
            {/* Classification Line */}
            <Line
              dataKey="classificationValue"
              name="Classification"
              type="monotone"
              stroke={color}
              strokeWidth={2}
              dot={false}
              animationDuration={1}
            />
            {/* Confidence Line */}
            <Line
              dataKey="confidence"
              name="Confidence"
              type="monotone"
              stroke="#82ca9d"
              strokeWidth={2}
              dot={false}
              animationDuration={1}
            />
          </LineChart>
        </ChartContainer>
      </CardContent>
      <CardFooter className="flex justify-center"></CardFooter>
    </Card>
  );
};
