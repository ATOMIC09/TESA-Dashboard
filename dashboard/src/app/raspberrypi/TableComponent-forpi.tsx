import React from "react";
import {
  Table,
  TableBody,
  TableCaption,
  TableCell,
  TableHead,
  TableHeader,
  TableRow,
} from "@/components/ui/table";

// Define the type for tabledata data
interface TableData {
  id: number;
  timestamp: number;
  created_at: string;
  classification: string;
  confidence: number;
}

interface TableComponentForPiProps {
  tabledatas: TableData[];
}

const TableComponentForPi: React.FC<TableComponentForPiProps> = ({ tabledatas }) => {
  // Function to format the timestamp based on Thailand locale
  const formatTimestamp = (timestamp: string) => {
    const date = new Date(timestamp);
    const milliseconds = date.getMilliseconds();
    return (
      date.toLocaleString("th-TH", {
        timeZone: "Asia/Bangkok", // Thailand's time zone
        year: "numeric",
        month: "long",
        day: "numeric",
        hour: "numeric",
        minute: "numeric",
        second: "numeric",
      }) + `.${milliseconds.toString().padStart(3, "0")}`
    );
  };

  // Convert X, N, F to full text
  const classificationMapping: { [key: string]: string } = {
    X: "Unknown",
    N: "Normal",
    F: "Fault",
  };

  // Conditional styling for classification
  const getClassificationStyle = (classification: string) => {
    switch (classification) {
      case "N":
        return "text-green-500"; // Green for Normal
      case "F":
        return "text-red-500"; // Red for Fault
      default:
        return "text-gray-500"; // Default for Unknown
    }
  };

  // Reverse the tabledatas to show the latest data at the top
  const reversedTableData = [...tabledatas].reverse(); // Create a shallow copy and reverse the array

  return (
    <Table className="m-4">
      <TableCaption>ผลลัพธ์การทำนาย</TableCaption>
      <TableHeader>
        <TableRow>
          <TableHead>Timestamp</TableHead>
          <TableHead>Classification</TableHead>
          <TableHead>Confidence</TableHead>
        </TableRow>
      </TableHeader>
      <TableBody>
        {reversedTableData.map((tabledata) => (
          <TableRow key={tabledata.id}>
            <TableCell>{formatTimestamp(tabledata.created_at)}</TableCell>
            <TableCell className={getClassificationStyle(tabledata.classification)}>
              {classificationMapping[tabledata.classification]}
            </TableCell>
            <TableCell>{tabledata.confidence}</TableCell>
          </TableRow>
        ))}
      </TableBody>
    </Table>
  );
};

export default TableComponentForPi;
