import { Button } from "@/components/ui/button"
import {
    Card,
    CardContent,
    CardDescription,
    CardFooter,
    CardHeader,
    CardTitle,
} from "@/components/ui/card"
import { Dialog, DialogContent, DialogHeader, DialogTitle } from "@/components/ui/dialog";
import { Input } from "@/components/ui/input"
import { Label } from "@/components/ui/label"
import {useState} from "react";
import {useNavigate} from "react-router";

const {ipcRenderer} = window.require('electron')
export function PatientRegister() {
    const navigate = useNavigate()

    const [isOpened, setIsOpened] = useState(false);

    const [name, setName] = useState('');
    const [DOB, setDOB] = useState('');
    const [address, setAddress] = useState('');
    const [phone, setPhone] = useState('');
    const [email,setEmail] = useState('');
    const [passportID, setPassportID] = useState('');
    const [citizen, setCitizen] = useState('');
    const [password, setPassword] = useState('');
    const [patientID, setPatientID] = useState('');

    


    async function patientReg() {
        try {
            const response = await ipcRenderer.invoke('reg-patient', name, DOB, address, phone, email, passportID, citizen, password);
            if (response.success) {
                //(event, name, DOB, Address, PhoneNumber, Email, PassportID, Citizenship, Password)
                setPatientID(JSON.parse(response.data).PatientID);
                localStorage.setItem('patientID', JSON.parse(response.data).PatientID)
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
        //FullName, Spec, Role, HospitalID, PhoneNumber, Email, Password
            if (!name || !DOB || !passportID || !address || !phone || !email || !password || !citizen) {
                console.log("missing fields");
                return;
            } else {
                patientReg();
                setIsOpened(true)
            }
        }
    
    
    


    return (
        <div className=' flex items-center justify-center h-screen'>
            <Dialog open={isOpened} onOpenChange={setIsOpened}>
                <DialogContent>
                    <DialogHeader>
                        <DialogTitle className='flex justify-center'>Your Patient ID - {patientID} </DialogTitle>
                        <Button className='mx-16 mt-16' onClick={() => navigate('/patient_login')}>Okay</Button>
                    </DialogHeader>
                </DialogContent>
            </Dialog>
            <Card className="bg-background w-96 max-w-lg">
                <CardHeader>
                    <CardTitle>Registration</CardTitle>
                    <CardDescription>Start using our services</CardDescription>
                </CardHeader>
                <CardContent>
                    <form>
                        <div className="grid w-full items-center gap-4">
                            <div className="flex flex-col space-y-1.5">
                                <Label htmlFor="name">Name</Label>
                                <Input value={name} onChange={(e) => setName(e.target.value)} id="name" placeholder="Your name" value={name} onChange={(e) => setName(e.target.value)} />
                            </div>
                            <div className="flex flex-col space-y-1.5">
                                <Label htmlFor="name">DOB</Label>
                                <Input value={DOB} onChange={(e) => setDOB(e.target.value)} id="name" placeholder="DOB" />
                            </div>
                            <div className="flex flex-col space-y-1.5">
                                <Label htmlFor="name">Address</Label>
                                <Input value={address} onChange={(e) => {setAddress(e.target.value)}} id="name" placeholder="Your address" />
                            </div><div className="flex flex-col space-y-1.5">
                            <Label htmlFor="name">Phone number</Label>
                            <Input value={phone} onChange={(e) => setPhone(e.target.value)} id="name" placeholder="Your phone number" />
                        </div>
                            <div className="flex flex-col space-y-1.5">
                            <Label htmlFor="name">Email</Label>
                            <Input value={email} onChange={(e) => setEmail(e.target.value)} id="name" placeholder="Your email" />
                        </div>
                            <div className="flex flex-col space-y-1.5">
                                <Label htmlFor="name">Passport ID</Label>
                                <Input value={passportID} onChange={(e) => setPassportID(e.target.value)} id="name" placeholder="Your passport ID" />
                            </div>
                            <div className="flex flex-col space-y-1.5">
                                <Label htmlFor="name">Citizenship</Label>
                                <Input value={citizen} onChange={(e) => setCitizen(e.target.value)} id="name" placeholder="Your citizenship" />
                            </div>
                            <div className="flex flex-col space-y-1.5">
                                <Label htmlFor="name">Password</Label>
                                <Input value={password} onChange={(e) => setPassword(e.target.value)} id="name" placeholder="Password" />
                            </div>
                        </div>
                    </form>
                </CardContent>
                <CardFooter className='flex flex-col gap-4'>
                <div>Already in? <span onClick={() => navigate('/patient_login')} className='text-primary cursor-pointer'>Log in</span></div>
                    <Button onClick={() => validateForm()} className='w-full'>Register</Button>
                </CardFooter>
            </Card>
        </div>
    )
}