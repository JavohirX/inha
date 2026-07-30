import React, { useEffect, useState } from 'react';
import {BellRing, Check, CircleUserRound, Hospital} from "lucide-react";
import {Button} from "@/components/ui/button";
import {Select, SelectContent, SelectItem, SelectTrigger, SelectValue} from "@/components/ui/select";
import {useNavigate} from "react-router";
import { Dialog, DialogContent, DialogHeader, DialogTitle } from '@/components/ui/dialog';
import { Calendar } from '@/components/ui/calendar';


const {ipcRenderer} = window.require('electron')
const PatientMenu = () => {
    const navigate = useNavigate();
    const [region, setRegion] = useState('');
    const [district, setDistrict] = useState('');
    const [hospital, setHospital] = useState('');
    const [spec, setSpec] = useState('');
    const [hospitalID, setHospitalID] = useState('');
    const [date, setDate] = useState<Date | undefined>(new Date());


    const [regions, setRegions] = useState([])
    const [districts, setDistricts] = useState([])
    const [hospitals, setHospitals] = useState([])
    const [specs, setSpecs] = useState([])
    const [docs, setDocs] = useState([])

    async function getRegions() {
        try {
            const response = await ipcRenderer.invoke('get-regions');
            if (response.success) {
                console.log(response.data)
                setRegions(JSON.parse(response.data))
                return response.data;
            } else {
                throw new Error(response.error);
            }
        } catch (error) {
            console.error('Failed to communicate with backend:', error);
            throw error;
        }
    }

    async function getDistricts() {
        try {
            const response = await ipcRenderer.invoke('get-districts', region);
            if (response.success) {
                console.log(response.data)
                setDistricts(JSON.parse(response.data))
                return response.data;
            } else {
                throw new Error(response.error);
            }
        } catch (error) {
            console.error('Failed to communicate with backend:', error);
            throw error;
        }
    }
    async function getHospitals() {
        try {
            const response = await ipcRenderer.invoke('get-hospitals', region, district);
            if (response.success) {
                console.log(response.data)
                setHospitals(JSON.parse(response.data))
                return response.data;
            } else {
                throw new Error(response.error);
            }
        } catch (error) {
            console.error('Failed to communicate with backend:', error);
            throw error;
        }
    }

    async function selectHospital() {
        try {
            const response = await ipcRenderer.invoke('select-hospital',hospital, region, district);
            if (response.success) {
                console.log(response.data)
                setHospitalID(JSON.parse(response.data).HospitalID)
                return response.data;
            } else {
                throw new Error(response.error);
            }
        } catch (error) {
            console.error('Failed to communicate with backend:', error);
            throw error;
        }
    }

    async function getSpecs() {
        try {
            const response = await ipcRenderer.invoke('get-specs', hospitalID.toString());
            if (response.success) {
                console.log(response.data)
                setSpecs(JSON.parse(response.data))
                return response.data;
            } else {
                throw new Error(response.error);
            }
        } catch (error) {
            console.error('Failed to communicate with backend:', error);
            throw error;
        }
    }

    async function getDocs() {
        try {
            const response = await ipcRenderer.invoke('get-docs', parseInt(hospitalID), spec);
            if (response.success) {
                console.log(response.data)
                setDocs(JSON.parse(response.data))
                return response.data;
            } else {
                throw new Error(response.error);
            }
        } catch (error) {
            console.error('Failed to communicate with backend:', error);
            throw error;
        }
    }

    async function docSelect(name) {
        try {
            const response = await ipcRenderer.invoke('selectDoc', parseInt(hospitalID),name );
            if (response.success) {
                console.log(response.data)
                //setDocs(JSON.parse(response.data))
                return response.data;
            } else {
                throw new Error(response.error);
            }
        } catch (error) {
            console.error('Failed to communicate with backend:', error);
            throw error;
        }
    }

    async function getSchedule() {
        try {
            const response = await ipcRenderer.invoke('get-schedule', localStorage.getItem("doctorID"), formatDate(date));
            if (response.success) {
            	//setAppointments(JSON.parse(response.data))
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



    useEffect(() => {
        getRegions();
    }, [])

    useEffect(() => {
            if (region) {
                getDistricts();
            }
    }, [region])

    useEffect(() => {
        if (region && district) {
            getHospitals();
        }
    }, [district])

    useEffect(() => {
        if (region && district) {
            getHospitals();
        
        }
    }, [district])
    useEffect(() => {
        if (region && district && hospital) {
            selectHospital();
        }
    }, [hospital])

    useEffect(() => {
        if (hospitalID) {
            getSpecs();
        }
    }, [hospitalID])

    useEffect(() => {
        if (spec) {
            getDocs();
        }
    }, [spec])

    const [isOpened, setIsOpened] = useState(false);
    const [selectedSlot, setSelectedSlot] = useState(null);
    const [selectedAppointments, setSelectedAppointments] = useState([
        { time: '9:00-10:00' },
        { time: '10:00-11:00' },
        { time: '11:00-12:00' },
        { time: '12:00-13:00' },
        { time: '13:00-14:00' },
        { time: '14:00-15:00' },
        { time: '15:00-16:00' },
        { time: '16:00-17:00' }
    ]);




    const appointments = {
        "2024-12-23": [
            { time: "14:00 - 15:00" },
            { time: "16:00 - 17:00" },
        ],
        "2024-12-24": [
            { time: "10:00 - 11:00" },
        ],
        "2024-12-29": [
            { time: "10:00 - 11:00" },
            { time: "11:00 - 12:00" },
        ],
    };

    const formatDate = (date: Date) => {
        const year = date.getFullYear();
        const month = String(date.getMonth() + 1).padStart(2, "0"); // Months are 0-based
        const day = String(date.getDate()).padStart(2, "0");
        return `${year}-${month}-${day}`;
    };

    useEffect(() => {
        const formattedDate = date ? formatDate(date) : undefined;
        getSchedule();
    }, [date]);

    const handleSelect = (appointment) => {
        setSelectedSlot(appointment);
    };

    
    return (
        <div>
            <div>
                <div className="flex flex-1 flex-col gap-4 p-4">
                    <h1 className="scroll-m-20 text-4xl font-extrabold tracking-tight lg:text-5xl">
                        Hospitals
                    </h1>
                    <div className='flex flex-row gap-x-4'>
                        <Select  value={region} onValueChange={(e) => setRegion(e)}>
                            <SelectTrigger className="w-[180px]">
                                <SelectValue placeholder="Region" />
                            </SelectTrigger>
                            <SelectContent>
                                {regions.map((item) => (
                                    <SelectItem value={item}>{item}</SelectItem>
                                ))}
            
                            </SelectContent>
                        </Select>
                        <Select value={district} onValueChange={(e) => setDistrict(e)}>
                            <SelectTrigger className="w-[180px]">
                                <SelectValue placeholder="District" />
                            </SelectTrigger>
                            <SelectContent>
                            {districts.map((item) => (
                                    <SelectItem value={item}>{item}</SelectItem>
                                ))}
                            </SelectContent>
                        </Select>
                        <Select value={hospital} onValueChange={(e) => setHospital(e)}>
                            <SelectTrigger className="w-[180px]">
                                <SelectValue placeholder="Hospitals" />
                            </SelectTrigger>
                            <SelectContent>
                            {hospitals.map((item) => (
                                    <SelectItem value={item.Name}>{item.Name}</SelectItem>
                                ))}
                            </SelectContent>
                        </Select>
                        <Select value={spec} onValueChange={(e) => setSpec(e)}>
                            <SelectTrigger className="w-[180px]">
                                <SelectValue placeholder="Specialities" />
                            </SelectTrigger>
                            <SelectContent>
                            {specs.map((item) => (
                                    <SelectItem value={item.Spec}>{item.Spec}</SelectItem>
                                ))}
                            </SelectContent>
                        </Select>
                    </div>
                    {docs.map((item) => (
                        <div>

                        <div onClick={() => {setIsOpened(true); docSelect(item)}} className="flex items-center space-x-4 rounded-md border p-4">
                            <CircleUserRound />
                            <div className="flex-1 space-y-1">
                                <p className="text-sm font-medium leading-none">
                                    {item}
                                </p>
                            

                            </div>
                        </div>
                            <Dialog  open={isOpened} onOpenChange={setIsOpened}>
                                <DialogContent>
                                    <DialogHeader>
                                        <DialogTitle className='flex justify-center'>Booking</DialogTitle>
                                        <div className="w-full flex gap-x-4">
                                            <Calendar
                                                mode="single"
                                                selected={date}
                                                onSelect={setDate}
                                                className="rounded-md border"
                                            />

                                            <div className="flex flex-col gap-y-4 min-w-[200px]">
                                                <h1 className='font-bold'></h1>
                                                <div className="overflow-y-auto max-h-[300px] pr-2">
                                                    {selectedAppointments.length > 0 ? (
                                                        selectedAppointments.map((appointment, index) => (
                                                            <div
                                                                key={index}
                                                                onClick={() => handleSelect(appointment)}
                                                                className={` flex items-center space-x-4 rounded-md border p-4 mb-2 last:mb-0 cursor-pointer hover:bg-primary transition-colors ${
                                                                    selectedSlot === appointment ? 'border-white bg-primary' : ''
                                                                }`}
                                                            >
                                                                <div className="flex-1 space-y-1">
                                                                    <p className="text-sm font-medium leading-none">
                                                                        {appointment.time}
                                                                    </p>
                                                                </div>
                                                                {selectedSlot === appointment && (
                                                                    <Check className="h-4 w-4 text-base" />
                                                                )}
                                                            </div>
                                                        ))
                                                    ) : (
                                                        <p className="text-muted-foreground">No available slots</p>
                                                    )}
                                                </div>
                                            </div>
                                        </div>
                                        <Button className='mx-16 mt-16' onClick={() => setIsOpened(false)} >Book</Button>
                                    </DialogHeader>
                                </DialogContent>
                            </Dialog>
                        </div>
                    ))
                }

                </div>
            </div>
        </div>
    );
};

export default PatientMenu;
