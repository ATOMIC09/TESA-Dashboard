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

// Define the type for tabledata data
interface TableData {
  id: string
  filename: string
  method: string
  amount: number
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
          <TableHead className="w-[100px]">TableData</TableHead>
          <TableHead>Filename</TableHead>
          <TableHead>Method</TableHead>
          <TableHead className="text-right">Amount</TableHead>
        </TableRow>
      </TableHeader>
      <TableBody>
        {tabledatas.map((tabledata) => (
          <TableRow key={tabledata.id}>
            <TableCell className="font-medium">{tabledata.id}</TableCell>
            <TableCell>{tabledata.filename}</TableCell>
            <TableCell>{tabledata.method}</TableCell>
            <TableCell className="text-right">${tabledata.amount.toFixed(2)}</TableCell>
          </TableRow>
        ))}
      </TableBody>
    </Table>
  )
}

export default TableComponent
