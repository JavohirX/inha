import {useEffect, useState} from 'react';
import {Card, CardContent, CardDescription, CardFooter, CardHeader, CardTitle} from "@/components/ui/card";
import {Label} from "@/components/ui/label";
import {Input} from "@/components/ui/input";
import {Button} from "@/components/ui/button";
import {useNavigate} from "react-router";
import {Select, SelectContent, SelectItem, SelectTrigger, SelectValue} from "@/components/ui/select";
import {
    Dialog,
    DialogContent,
    DialogDescription,
    DialogHeader,
    DialogTitle,
    DialogTrigger
} from "@/components/ui/dialog";


const {ipcRenderer} = window.require("electron");
const DocRegister = () => {
    const navigate = useNavigate();
    

    //FullName, Spec, Role, HospitalID, PhoneNumber, Email, Password
    //
    const [isOpened, setIsOpened] = useState(false);
    const [name, setName] = useState('');
    const [phone, setPhone] = useState('');
    const [email, setEmail] = useState('');
    const [password, setPassword] = useState('');
    const [role, setRole] = useState('');
    
    const [doctorID, setDoctorID] = useState('');
    

    const [region, setRegion] = useState('')
    const [district, setDistrict] = useState('');
    const [hospital, setHospital] = useState('');
    const [hospitalID, setHospitalID] = useState('');
    const [spec, setSpec] = useState('');
    
    
    const [regions, setRegions] = useState([])
    const [districts, setDistricts] = useState([])
    const [hospitals, setHospitals] = useState([])
    const [specs, setSpecs] = useState([])
    
    
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
             const response = await ipcRenderer.invoke('get-hospitals',region, district);
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
     
     async function selectHospitals() {
         try {
             const response = await ipcRenderer.invoke('select-hospital',hospital, region, district, "Kogon Main St. 101, Bukhara");
             if (response.success) {
                 console.log(response.data)
                 setHospitalID(JSON.parse(response.data).HospitalID)
                 console.log(hospitalID)
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
             const response = await ipcRenderer.invoke('get-specs',hospitalID.toString());
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
     
     
     
     async function docReg() {
         try {
             const response = await ipcRenderer.invoke('doc-reg', name, spec, role, hospitalID, phone, email, password);
             if (response.success) {
     		 setDoctorID(JSON.parse(response.data).DoctorID);
     		 localStorage.setItem('doctorID', JSON.parse(response.data).DoctorID)
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
     	if (!spec || !name || !role || !hospitalID || !phone || !email || !password) {
     		console.log("missing fields");
     		return;
     	} else {
     	    docReg();
     	    setIsOpened(true)
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
     	if (district){
     		getHospitals()
     	}
     	
     }, [district])
     
     useEffect(() => {
     	if (hospital) {
     		selectHospitals();
	}
     }, [hospital])
     
    useEffect(() => {
	     if (hospitalID) {
	     	getSpecs();
	     } 
     
     }, [hospitalID])


     
    
     
     
     


    return (
        <div className=' flex items-center justify-center h-screen'>
            <Dialog open={isOpened} onOpenChange={setIsOpened}>
                <DialogContent>
                    <DialogHeader>
                        <DialogTitle className='flex justify-center'>Your Doctor ID - {doctorID}</DialogTitle>
                        <Button className='mx-16 mt-16' onClick={() => navigate('/doc_login')}>Okay</Button>
                    </DialogHeader>
                </DialogContent>
            </Dialog>
            <Card className="bg-background w-96 max-w-lg">
                <CardHeader>
                    <CardTitle>Register Doctor</CardTitle>
                </CardHeader>
                <CardContent>
                    <form>
                        <div className="grid w-full items-center gap-4">
                            <div className='flex flex-col space-y-1.5 '>
                                <Select value={region} onValueChange={(e) => setRegion(e)}>
                                    <SelectTrigger>
                                        <SelectValue placeholder="Region" />
                                    </SelectTrigger>
                                    <SelectContent>
                                    	{regions?.map((item) => (
                                    		<SelectItem value={item}>{item}</SelectItem>
                                    	))}
                                    </SelectContent>
                                </Select>
                            </div>
                            <Select value={district} onValueChange={(e) => setDistrict(e)}>
                                <SelectTrigger>
                                    <SelectValue placeholder="District" />
                                </SelectTrigger>
                                <SelectContent>
                                    {districts?.map((item) => (
                                    		<SelectItem value={item}>{item}</SelectItem>
                                    	))}
                                </SelectContent>
                            </Select>
                            <Select value={hospital} onValueChange={(e) => setHospital(e)}>
                                <SelectTrigger>
                                    <SelectValue placeholder="Hospital" />
                                </SelectTrigger>
                                <SelectContent>
                                     {hospitals?.map((item) => (
                                    		<SelectItem value={item.Name}>{item.Name}</SelectItem>
                                    	))}
                                </SelectContent>
                            </Select>
                            <Select value={spec} onValueChange={(e) => setSpec(e)}>
                                <SelectTrigger>
                                    <SelectValue placeholder="Speciality" />
                                </SelectTrigger>
                                <SelectContent>
                                     {specs?.map((item) => (
                                    		<SelectItem value={item.Spec}>{item.Spec}</SelectItem>
                                    	))}
                                </SelectContent>
                            </Select>
                            <div className="flex flex-col space-y-1.5">
                                <Label htmlFor="name">Name</Label>
                                <Input id="name" placeholder="Full name" value={name} onChange={(e) => setName(e.target.value)} />
                            </div>
                            
                            <div className="flex flex-col space-y-1.5">
                                <Label htmlFor="name">Role</Label>
                                <Input id="name" placeholder="Your role" value={role} onChange={(e) => setRole(e.target.value)} />
                            </div>
                            
                            <div className="flex flex-col space-y-1.5">
                                <Label htmlFor="name">Phone</Label>
                                <Input value={phone} onChange={(e) => setPhone(e.target.value)} id="name" placeholder="Your phone number" />
                            </div>
                        <div className="flex flex-col space-y-1.5">
                            <Label htmlFor="name">Email</Label>
                            <Input value={email} onChange={(e) => setEmail(e.target.value)}  id="name" placeholder="Your email" />
                        </div>
                        <div className="flex flex-col space-y-1.5">
                            <Label htmlFor="name">Password</Label>
                            <Input value={password} onChange={(e) => setPassword(e.target.value)} type='password' id="name" placeholder="Your password" />
                        </div>
                        </div>
                    </form>
                </CardContent>
                <CardFooter className='flex flex-col gap-4'>
                	<CardDescription>
              Already in? <span onClick={() => navigate('/doc_login')} className='text-primary cursor-pointer'>Log in</span>
            </CardDescription>
                    <Button onClick={() => validateForm()} className='w-full'>Submit</Button>
                </CardFooter>
            </Card>
        </div>
    );
};

export default DocRegister ;
