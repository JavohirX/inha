import React, {useEffect, useState} from 'react';
import {Check, CircleUserRound} from "lucide-react";
import {Button} from "@/components/ui/button";
import {Dialog, DialogContent, DialogHeader, DialogTitle} from "@/components/ui/dialog";
import {Calendar} from "@/components/ui/calendar";

const DoctorsList = () => {
    const [isOpened, setIsOpened] = useState(false);
    const [selectedSlot, setSelectedSlot] = useState(null);
    const [selectedAppointments, setSelectedAppointments] = useState([]);
    const [date, setDate] = useState<Date | undefined>(new Date());

    const doctors = [
        {
            name: 'John Doe',
            specs: 'Ontologist',
            freeDates: [
                "2024-01-01",
                "2024-01-02",
            ]
        }
    ];

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
        setSelectedAppointments(formattedDate ? appointments[formattedDate] || [] : []);
    }, [date]);

    const handleSelect = (appointment) => {
        setSelectedSlot(appointment);
    };
    return (
        <div>
            <div className="flex flex-1 flex-col gap-4 p-4">
                <h1 className="scroll-m-20 text-4xl font-extrabold tracking-tight lg:text-5xl">
                    Doctors
                </h1>
                {
                    doctors.map((item) => (
                        <div>

                        <div onClick={() => setIsOpened(true)} className="flex items-center space-x-4 rounded-md border p-4">
                            <CircleUserRound />
                            <div className="flex-1 space-y-1">
                                <p className="text-sm font-medium leading-none">
                                    {item.name}
                                </p>
                                <p className="text-sm text-muted-foreground">
                                    {item.specs}
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
    );
};

export default DoctorsList;