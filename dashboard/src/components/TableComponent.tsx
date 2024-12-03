import React from "react"
import {
  Table,
  TableBody,
  TableCaption,
  TableCell,
  TableHead,
  TableHeader,
  TableRow,
} from "@/components/ui/table"
// import { NEXT_PUBLIC_BACKENDSERVER } from "@/app/server/config";

// Define the type for tabledata data
interface TableData {
  deviceId: string
  filePath: string
  timeStamp: number
}

interface TableComponentProps {
  tabledatas: TableData[]
}

const TableComponent: React.FC<TableComponentProps> = ({ tabledatas }) => {
  // Function to format the timestamp based on Thailand locale
  const formatTimestamp = (timestamp: number) => {
    const date = new Date(timestamp);
    return date.toLocaleString("th-TH", {
      timeZone: "Asia/Bangkok", // Thailand's time zone
      year: "numeric",
      month: "long",
      day: "numeric",
      hour: "numeric",
      minute: "numeric",
      second: "numeric",
    });
  };

  return (
    <Table>
      <TableCaption className="py-1">รายการไฟล์ล่าสุดในเซิร์ฟเวอร์</TableCaption>
      <TableHeader>
        <TableRow>
          <TableHead>Device ID</TableHead>
          <TableHead>Timestamp</TableHead>
          <TableHead>File name</TableHead>
          <TableHead>Download</TableHead>
        </TableRow>
      </TableHeader>
      <TableBody>
        {tabledatas.map((tabledata) => (
          <TableRow key={tabledata.deviceId}>
            <TableCell>{tabledata.deviceId}</TableCell>
            <TableCell>{formatTimestamp(tabledata.timeStamp)}</TableCell>
            <TableCell>{tabledata.filePath.split('/').pop()?.replace(/_[a-f0-9\-]+\.wav$/, '.wav')}</TableCell>
            <TableCell>
              <a target="_blank" rel="noopener noreferrer" href={`https://openfruit-tesa-backend.onrender.com${tabledata.filePath.split('/static/sound/,')}`}>
                <button className="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded">
                  Download
                </button>
              </a>
            </TableCell>
          </TableRow>
        ))}
      </TableBody>
    </Table>
  )
}

export default TableComponent
