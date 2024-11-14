"use client";

import { CartesianGrid, Line, LineChart, XAxis, YAxis, Tooltip } from "recharts";
import {
  Card,
  CardContent,
  CardDescription,
  CardFooter,
  CardHeader,
  CardTitle,
} from "@/components/ui/card";
import {
  ChartConfig,
  ChartContainer,
} from "@/components/ui/chart";

interface LineChartComponentProps {
  title: string;
  description: string;
  chartData: Array<{ cycleCount: number; var1: number; var2: number; var3: number }>;
  chartConfig: ChartConfig;
}

export const LineChartComponent: React.FC<LineChartComponentProps> = ({
  title,
  description,
  chartData,
  chartConfig,
}) => {
  return (
    <Card>
      <CardHeader>
        <CardTitle>{title}</CardTitle>
        <CardDescription>{description}</CardDescription>
      </CardHeader>
      <CardContent>
        <ChartContainer config={chartConfig}>
          <LineChart
            accessibilityLayer
            data={chartData}
            margin={{
              left: 12,
              right: 12,
            }}
          >
            <CartesianGrid vertical={false} />
            <XAxis
              dataKey="cycleCount"
              tickLine={false}
              axisLine={false}
              tickMargin={8}
              tickFormatter={(value) => value.toString()}
            />
            <YAxis
              domain={['auto', 'auto']} // Ensure the Y-axis scales properly
              
            />
            <Tooltip />
            <Line
              dataKey="var1"
              type="monotone"
              stroke="#ff7300" // Example fixed color for L1
              strokeWidth={2}
              dot={false}
            />
            <Line
              dataKey="var2"
              type="monotone"
              stroke="#387908" // Example fixed color for L2
              strokeWidth={2}
              dot={false}
            />
            <Line
              dataKey="var3"
              type="monotone"
              stroke="#0060ff" // Example fixed color for L3
              strokeWidth={2}
              dot={false}
            />
          </LineChart>
        </ChartContainer>
      </CardContent>
      <CardFooter>
        {/* <div className="flex w-full items-start gap-2 text-sm">
          <div className="grid gap-2">
            <div className="flex items-center gap-2 font-medium leading-none">
              Trending up by 5.2% this voltage <TrendingUp className="h-4 w-4" />
            </div>
            <div className="flex items-center gap-2 leading-none text-muted-foreground">
              Showing total visitors for the last 6 months
            </div>
          </div>
        </div> */}
      </CardFooter>
    </Card>
  );
};
