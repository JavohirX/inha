import { Button } from "@/components/ui/button"
import { Input } from "@/components/ui/input"
import {
    Table,
    TableBody,
    TableCaption,
    TableCell,
    TableHead,
    TableHeader,
    TableRow,
  } from "@/components/ui/table"
import { useEffect, useState } from "react"
  
  const invoices = [
    {
      invoice: "INV001",
      paymentStatus: "Paid",
      totalAmount: "$250.00",
      paymentMethod: "Credit Card",
    },
    {
      invoice: "INV002",
      paymentStatus: "Pending",
      totalAmount: "$150.00",
      paymentMethod: "PayPal",
    },
    {
      invoice: "INV003",
      paymentStatus: "Unpaid",
      totalAmount: "$350.00",
      paymentMethod: "Bank Transfer",
    },
    {
      invoice: "INV004",
      paymentStatus: "Paid",
      totalAmount: "$450.00",
      paymentMethod: "Credit Card",
    },
    {
      invoice: "INV005",
      paymentStatus: "Paid",
      totalAmount: "$550.00",
      paymentMethod: "PayPal",
    },
    {
      invoice: "INV006",
      paymentStatus: "Pending",
      totalAmount: "$200.00",
      paymentMethod: "Bank Transfer",
    },
    {
      invoice: "INV007",
      paymentStatus: "Unpaid",
      totalAmount: "$300.00",
      paymentMethod: "Credit Card",
    },
  ]

  //('adminLogin', async (event, id, Password)

  
  const {ipcRenderer} = window.require('electron')
  export default function AdminPanel() {
    const [query, setQuery] = useState('');

    const [data, setData] = useState([]);
    const [headers, setHeaders] = useState([]);


    async function sqlExec() {
        try {
            const response = await ipcRenderer.invoke('sqlExe',query );
            if (response.success) {
                console.log(response.data)
                setData(JSON.parse(response.data))
                
                return response.data;
            } else {
                throw new Error(response.error);
            }
        } catch (error) {
            console.error('Failed to communicate with backend:', error);
            throw error;
        }
    }
    useEffect(() => {
        if (data.length > 0) { 
            setHeaders(Object.keys(data[0]));
        };
    }, [data])

    return (
        <div>
            <div className='mt-16 gap-x-4  flex flex-row'>
            <Input onChange={(e) => setQuery(e.target.value)} className='ml-16 mb-4 w-64' placeholder="Enter SQL query" />
            <Button onClick={() => sqlExec()}>EXECUTE</Button>
            </div>
    
      <Table>
        <TableCaption>SQL table</TableCaption>
        <TableHeader>
          <TableRow>
            
        
            {headers && headers?.map((item) => (
                <TableHead>{item}</TableHead>
            ))}
          </TableRow>
        </TableHeader>
        <TableBody>
        {data && data?.map((item) => (
            <TableRow>
                {headers && headers?.map((header) => 
                    <TableCell key={header}>
                        {item[header]}
                    </TableCell>
                )}
            </TableRow>
              
            ))}
        </TableBody>
      </Table>
      </div>
    )
  }