import {Button} from "@/components/ui/button";
import {useNavigate} from "react-router";


//const {ipcRenderer} = window.require('electron')
export function Start() {
    //  async function sendJsonToBackend(jsonData: String) {
    //     try {
    //         const response = await ipcRenderer.invoke('get-regions');
    //         if (response.success) {
    //             console.log(response.data)
    //             return response.data;
    //         } else {
    //             throw new Error(response.error);
    //         }
    //     } catch (error) {
    //         console.error('Failed to communicate with backend:', error);
    //         throw error;
    //     }
    // }


    const navigate = useNavigate()
    return (
        <div className='bg-gradient-to-r from-violet-200 to-pink-200 flex flex-col items-center justify-center h-screen'>

            <div className="flex flex-col items-center justify-center text-center min-h-screen  px-4">
                <div className="max-w-2xl">
                    <h1 className="text-black text-3xl lg:text-5xl font-extrabold leading-tight">
                        Welcome to Doctor's Reservation System
                    </h1>
                    <p className="mt-4 text-black text-lg lg:text-xl">
                        Who are you?
                    </p>
                    <div className="flex flex-row gap-4 mt-6 justify-center">
                        <Button onClick={() => {navigate('/doc_register'); localStorage.setItem("userRole", "doctor");}} >Doctor</Button>
                        <Button onClick={() => {navigate('/register'); localStorage.setItem("userRole", "patient");}} >Patient</Button>
                        <Button onClick={() => {navigate('/admin_login'); localStorage.setItem("userRole", "admin");}} >Admin</Button>
                    </div>
                </div>
            </div>
        </div>
    )
}