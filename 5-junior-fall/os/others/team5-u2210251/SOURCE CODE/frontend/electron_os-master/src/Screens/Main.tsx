
import {
    SidebarGroupContent,
     SidebarInput, SidebarInset,
     SidebarProvider, SidebarTrigger,
} from "@/components/ui/sidebar";
import { Search,} from "lucide-react";
import {AppSidebar} from "@/My Components/AppSidebar";
import {Label} from "@/components/ui/label";
import react from '../assets/react.svg'
import {Button} from "@/components/ui/button";
import {Calendar} from "@/components/ui/calendar";
import {useState, useEffect} from "react";
import { Dialog, DialogContent, DialogHeader, DialogTitle } from "@/components/ui/dialog";

const {ipcRenderer} = window.require("electron")
const Main = () => {

    const [date, setDate] = useState<Date | undefined>(new Date())
    const [appointments, setAppointments] = useState([])
    const [waitlist, setWaitlist] = useState([])
    const [hourlyInfo, setHourlyInfo] = useState({})
    const [caseHistory, setCaseHistory] = useState([]);
    
    const [isOpened, setIsOpened] = useState(false)

    /*const appointments = {
        "2024-12-23": [
            { time: "14:00 - 15:00", patient: "Patient 1" },
            { time: "16:00 - 17:00", patient: "Patient 2" },
        ],
        "2024-12-24": [
            { time: "10:00 - 11:00", patient: "Patient 3" },
        ],
        "2024-12-29": [
            { time: "10:00 - 11:00", patient: "Patient 3" },
            { time: "10:00 - 11:00", patient: "Patient 3" },
            { time: "10:00 - 11:00", patient: "Patient 3" },
            { time: "10:00 - 11:00", patient: "Patient 3" },
            { time: "10:00 - 11:00", patient: "Patient 3" },
        ],
    };*/

   
    //'getWaitlist', async (event, PatientID, DoctorID)
    
    
    const formatDate = (date: Date) => {
        const year = date.getFullYear();
        const month = String(date.getMonth() + 1).padStart(2, "0"); // Months are 0-based
        const day = String(date.getDate()).padStart(2, "0");
        return `${year}-${month}-${day}`;
    };
    
    async function getSchedule() {
        try {
            const response = await ipcRenderer.invoke('get-schedule', localStorage.getItem("doctorID"), formatDate(date));
            if (response.success) {
            	setAppointments(JSON.parse(response.data))
                console.log(response)
                return response.data;
            } else {
                throw new Error(response.error);
            }
        } catch (error) {
            console.error('Failed to communicate with backend:', error);
            throw error;
        }
    }
    
    async function getWaitlist() {
        try {
            const response = await ipcRenderer.invoke('getWaitlist', formatDate(date), localStorage.getItem("doctorID"));
            if (response.success) {
            	setWaitlist(JSON.parse(response.data))
                console.log(response)
                return response.data;
            } else {
                throw new Error(response.error);
            }
        } catch (error) {
            console.error('Failed to communicate with backend:', error);
            throw error;
        }
    }

    async function getHourInfo(dateTime) {
        try {
            const response = await ipcRenderer.invoke('get-hour-info', localStorage.getItem("doctorID"), dateTime);
            if (response.success) {
            	setHourlyInfo(JSON.parse(response.data)[0])
                console.log(response)
                return response.data;
            } else {
                throw new Error(response.error);
            }
        } catch (error) {
            console.error('Failed to communicate with backend:', error);
            throw error;
        }
    }

    async function getCaseHistory(patientID) {
        try {
            const response = await ipcRenderer.invoke('get-case-history', patientID);
            if (response.success) {
            	setCaseHistory(JSON.parse(response.data))
                console.log(response)
                return response.data;
            } else {
                throw new Error(response.error);
            }
        } catch (error) {
            console.error('Failed to communicate with backend:', error);
            throw error;
        }
    }

    //'get-case-history', async (event, patientID)

    const handleDownload = async (patientID) => {


        
        const caseInfo = await getCaseHistory(patientID.toString())
        

        const formatObject = (obj, indent = "") => {
            return Object.entries(obj)
              .map(([key, value]) => {
                if (typeof value === "object" && value !== null) {
                  // Handle nested objects
                  return `${indent}${key}:\n${formatObject(value, indent + "  ")}`;
                }
                // Handle primitive values
                return `${indent}${key}: ${value}`;
              })
              .join('\n');
          };
          console.log(caseInfo);
          const fileContent = JSON.parse(caseInfo).map(obj => formatObject(obj)).join('\n\n');
          console.log(fileContent)
        
        
        const blob = new Blob([fileContent], { type: "text/plain" });
        
      
        const url = URL.createObjectURL(blob);
        
    
        const a = document.createElement("a");
        a.href = url;
        a.download = "CASE_HISTORY.txt"; 
        

        a.click();
        
        // Clean up the URL object
        URL.revokeObjectURL(url);
      };

    //'get-hour-info', async (event, doctorID, DateTime)

    const formattedDate = date ? formatDate(date) : undefined;

    const selectedWaitlist = date ? formatDate(date) : undefined;

    const selectedAppointments = formattedDate ? appointments[formattedDate] || [] : [];
    
    useEffect(() => {
    	getSchedule();
    	getWaitlist();
    }, [date])
   


    return (
            <div>
                <SidebarProvider>
                    <SidebarInset>
                        <header className="flex h-16 shrink-0 items-center gap-2 border-b px-4">
                            <SidebarTrigger className="-ml-1" />
                        </header>
                        <div className="flex flex-1 flex-col gap-4 p-4">
                            <h1 className="scroll-m-20 text-4xl font-extrabold tracking-tight lg:text-5xl">
                                Agenda
                            </h1>
                            <div className="w-full flex gap-x-4">
                                <Calendar
                                    mode="single"
                                    selected={date}
                                    onSelect={setDate}
                                    className="rounded-md border"
                                />

                                <div className="flex flex-col gap-y-4 min-w-[200px]">
                                    <h1 className='font-bold'>Appointments</h1>
                                    <div className="overflow-y-auto max-h-[300px] pr-2">
                                        {appointments.length > 0 ? (
                                            appointments.map((appointment, index) => (
                                                <div
                                                    key={index}
                                                    className="flex items-center space-x-4 rounded-md border p-4 mb-2 last:mb-0"
                                                >
                                                    <Dialog open={isOpened} onOpenChange={setIsOpened}>
                                                        <DialogContent>
                                                            <DialogHeader>
                                                                <DialogTitle className='flex justify-center'>Doctor name: {hourlyInfo.DoctorName}</DialogTitle>
                                                                <DialogTitle className='flex justify-center'>Hospital name: {hourlyInfo.HospitalName}</DialogTitle>
                                                                <DialogTitle className='flex justify-center'>Patient name: {hourlyInfo.PatientName}</DialogTitle>
                                                                <DialogTitle className='flex justify-center'>Patient ID: {hourlyInfo.PatientID}</DialogTitle>
                                                                <Button className='mx-16' onClick={() => handleDownload(hourlyInfo.PatientID)}>DOWNLOAD PATIENT CASE HISTORY</Button>
                                                            </DialogHeader>
                                                        </DialogContent>
                                                    </Dialog>
                                                    <div onClick={() => {setIsOpened(true); getHourInfo(appointment.DateTime)}} className="flex-1 space-y-1">
                                                        <p className="text-sm font-medium leading-none">
                                                            {appointment.DateTime}
                                                        </p>
                                                        <p className="text-sm text-muted-foreground">
                                                            {appointment.Status}
                                                        </p>
                                                    </div>
                                                </div>
                                            ))
                                        ) : (
                                            <p className="text-muted-foreground">No appointments for this date.</p>
                                        )}
                                    </div>
                                </div>

                                <div className="flex flex-col gap-y-4 min-w-[200px]">
                                    <h1 className='font-bold'>Waitlist</h1>
                                    <div className="overflow-y-auto max-h-[300px] pr-2">
                                        {waitlist?.length > 0 ? (
                                            waitlist.map((appointment, index) => (
                                                <div
                                                    key={index}
                                                    className="flex items-center space-x-4 rounded-md border p-4 mb-2 last:mb-0"
                                                >
                                                    <div className="flex-1 space-y-1">
                                                        
                                                        <p className="text-sm text-medium">
                                                            {appointment.FullName}
                                                        </p>
                                                        <p className="text-sm text-muted-foreground">
                                                            Patient ID: {appointment.PatientID}
                                                        </p>
                                                        <p className="text-sm text-muted-foreground">
                                                            Waitlist ID: {appointment.WaitlistID}
                                                        </p>
                                                    </div>
                                                </div>
                                            ))
                                        ) : (
                                            <p className="text-muted-foreground">Waitlist is empty</p>
                                        )}
                                    </div>
                                </div>
                            </div>
                        </div>
                    </SidebarInset>

                </SidebarProvider>
            </div>

    );
};

export default Main;
