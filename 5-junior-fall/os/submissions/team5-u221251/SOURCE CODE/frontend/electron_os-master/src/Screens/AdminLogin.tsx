import React, {useState} from 'react';
import {Card, CardContent, CardFooter, CardHeader, CardTitle} from "@/components/ui/card";
import {Label} from "@/components/ui/label";
import {Input} from "@/components/ui/input";
import {Button} from "@/components/ui/button";
import {useNavigate} from "react-router";


const {ipcRenderer} = window.require('electron')
const AdminLogin = () => {

    const navigate = useNavigate();
    const [adminID, setAdminID] = useState('')
    const [password, setPassword] = useState('')
    //handle('adminLogin', async (event, id, Password)
    async function adminLogin() {
        try {
            const response = await ipcRenderer.invoke('adminLogin', adminID, password);
            if (response.success) {
                //(event, name, DOB, Address, PhoneNumber, Email, PassportID, Citizenship, Password)
                
                //localStorage.setItem('patientID', JSON.parse(response.data).PatientID)
                console.log(response.data)
                
                return response.data;
            } else {
                throw new Error(response.error);
            }
        } catch (error) {
            console.error('Failed to communicate with backend:', error);
            throw error;
        }
    }

    const validateForm = () => {
    	if (!adminID || !password) {
    		console.log("missing fields in login");
    		return;
    	}
    		adminLogin();
    		navigate('/admin_panel');
    	
    }

    

    return (
        <div>
            <div className=' flex items-center justify-center h-screen'>
                <Card className="bg-background w-96 max-w-lg">
                    <CardHeader>
                        <CardTitle>Admin Login</CardTitle>
                    </CardHeader>
                    <CardContent>
                        <form>
                            <div className="grid w-full items-center gap-4">
                                <div className="flex flex-col space-y-1.5">
                                    <Label htmlFor="name">Admin ID</Label>
                                    <Input value={adminID} onChange={(e) => setAdminID(e.target.value)} id="name" placeholder="Admin ID" />
                                </div>
                                <div className="flex flex-col space-y-1.5">
                                    <Label htmlFor="name">Password</Label>
                                    <Input value={password} onChange={(e) => setPassword(e.target.value)} type='password' id="name" placeholder="Your password" />
                                </div>
                            </div>
                        </form>
                    </CardContent>
                    <CardFooter className='flex flex-col gap-4'>
                        <Button onClick={() => validateForm()} className='w-full'>Login</Button>
                    </CardFooter>
                </Card>
            </div>
        </div>
    );
};

export default AdminLogin;