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
import { NEXT_PUBLIC_BACKENDSERVER } from "@/app/raspberrypi/config";

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
  return (
    <Table>
      <TableCaption>A list of your recent tabledatas.</TableCaption>
      <TableHeader>
        <TableRow>
          <TableHead className="w-[100px]">Device ID</TableHead>
          <TableHead>File Path</TableHead>
          <TableHead className="text-right">Download</TableHead>
        </TableRow>
      </TableHeader>
      <TableBody>
        {tabledatas.map((tabledata) => (
          <TableRow key={tabledata.deviceId}>
            <TableCell className="font-medium">{tabledata.deviceId}</TableCell>
            <TableCell>{tabledata.filePath.split('/static/sound/')}</TableCell>
            <TableCell className="text-right">
              <a target="_blank" rel="noopener noreferrer" href={`${NEXT_PUBLIC_BACKENDSERVER}${tabledata.filePath.split('/static/sound/,')}`}>
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
