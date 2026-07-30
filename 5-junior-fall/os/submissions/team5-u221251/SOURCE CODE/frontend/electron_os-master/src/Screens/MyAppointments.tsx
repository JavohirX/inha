import React from 'react';
import {BellRing, ClipboardPlus, Clock9} from "lucide-react";
import {Button} from "@/components/ui/button";

const MyAppointments = () => {
    return (
        <div>
            <div>
                <div className="flex flex-1 flex-col gap-4 p-4">
                    <h1 className="scroll-m-20 text-4xl font-extrabold tracking-tight lg:text-5xl">
                        My appointments
                    </h1>
                    <div className="flex items-center space-x-4 rounded-md border p-4">
                        <Clock9/>
                        <div className="flex-1 space-y-1">
                            <p className="text-sm font-medium leading-none">
                                Patient 1
                            </p>
                            <p className="text-sm text-muted-foreground">
                                12:00 - 13:00
                            </p>
                        </div>
                        <Button>Cancel</Button>
                    </div>

                </div>
            </div>
        </div>
    );
};

export default MyAppointments;
