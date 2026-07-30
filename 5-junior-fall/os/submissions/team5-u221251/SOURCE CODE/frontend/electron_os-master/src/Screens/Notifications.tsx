import React, { useEffect, useState } from 'react';
import {BellRing} from "lucide-react";
import {Button} from "@/components/ui/button";

const {ipcRenderer} = window.require('electron')
const Notifications = () => {
    //'judge-notification', async (event, id, status, tableName
    const [notifications, setNotifications] = useState([]);
async function getNotifs() {
	try {
	    const response = await ipcRenderer.invoke('get-doc-notification', localStorage.getItem('doctorID'), localStorage.getItem('lastLogin'));
	    if (response.success) {
	    	setNotifications(JSON.parse(response.data))
	       	console.log(response.data);
		return response.data;
	    } else {
		throw new Error(response.error);
	    }
	} catch (error) {
	    console.error('Failed to communicate with backend:', error);
	    throw error;
	}
    }
    async function judgeNotifs(id, status) {
        try {
            const response = await ipcRenderer.invoke('judge-notification',  id, status, "appointments");
            if (response.success) {
                   //setNotifications(JSON.parse(response.data))
                   console.log(response.data);
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
        getNotifs()
    }, [])
    return (
        <div>
            <div className="flex flex-1 flex-col gap-4 p-4">
            <h1 className="scroll-m-20 text-4xl font-extrabold tracking-tight lg:text-5xl">
                Notifications
            </h1>
            {notifications.length === 0 ? <div>No notifications</div> : notifications?.map((item, index) => (
                <div className="flex items-center space-x-4 rounded-md border p-4">
                <BellRing />
                <div className="flex-1 space-y-1">
                    <p className="text-sm font-medium leading-none">
                        {item.FullName}
                    </p>
                    <p className="text-sm text-muted-foreground">
                        Date: {item.DateTime}
                    </p>
                    <p className="text-sm text-muted-foreground">
                        Status: {item.Status}
                    </p>
                </div>
                <Button onClick={() => judgeNotifs(item.AppointmentID, "Booked")}>Accept</Button>
                <Button onClick={() => judgeNotifs(item.AppointmentID, "Cancelled")}>Reject</Button>
            </div>
            ))}
        

            </div>
        </div>
    );
};

export default Notifications;
