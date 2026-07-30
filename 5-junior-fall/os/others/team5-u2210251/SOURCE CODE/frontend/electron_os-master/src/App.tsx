import {HashRouter, Route, Routes, useLocation} from "react-router";
import {Start} from "@/Screens/Start";
import {PatientRegister} from "@/Screens/PatientRegister";
import Main from "@/Screens/Main";
import Notifications from "@/Screens/Notifications";
import {AppSidebar} from "@/My Components/AppSidebar";
import {SidebarProvider, SidebarTrigger} from "@/components/ui/sidebar";
import DocRegister from "@/Screens/DocRegister";
import DocLogin from "@/Screens/DocLogin";
import PatientLogin from "@/Screens/PatientLogin";
import {PatientSidebar} from "@/My Components/PatientSidebar";
import PatientMenu from "@/Screens/PatientMenu";
import PatientNotifications from "@/Screens/PatientNotification";
import DoctorsList from "@/Screens/DoctorsList";
import MyAppointments from "@/Screens/MyAppointments";
import CaseHistory from "@/Screens/CaseHistory";
import AdminLogin from "@/Screens/AdminLogin";
import AdminPanel from "@/Screens/AdminPanel";

export function App() {
    return (
        <HashRouter>
            <SidebarProvider>
                <div className="flex w-full">
                    <Sidebar />
                    <main className="flex-1">
                        <Routes>
                            <Route path="/" element={<Start />} />
                            <Route path="/register" element={<PatientRegister />} />
                            <Route path="/doc_register" element={<DocRegister />} />
                            <Route path="/doc_login" element={<DocLogin />} />
                            <Route path="/patient_login" element={<PatientLogin />} />
                            <Route path="/main" element={<Main />} />
                            <Route path="/notify" element={<Notifications />} />
                            <Route path="/patient_notify" element={<PatientNotifications />} />
                            <Route path="/patient_menu" element={<PatientMenu />} />
                            <Route path="/doctors_list" element={<DoctorsList />} />
                            <Route path="/appoints" element={<MyAppointments />} />
                            <Route path="/case_history" element={<CaseHistory />} />
                            <Route path="/admin_login" element={<AdminLogin />} />
                            <Route path="/admin_panel" element={<AdminPanel />} />
                        </Routes>
                    </main>
                </div>
            </SidebarProvider>
        </HashRouter>
    )
}


const Sidebar = () => {
    const location = useLocation(); // Get the current location (route)

    // List of routes where sidebar should be hidden
    const hideSidebarRoutes = ["/","/register","/admin_login","/admin_panel", "/login",'/patient_login', "/doc_register","/doc_login", "/patient_login",];

    // Check if the current route is in the hideSidebarRoutes array
    const shouldHideSidebar = hideSidebarRoutes.includes(location.pathname);



    if (shouldHideSidebar) {
        return null; // Return nothing if the sidebar should be hidden
    }



    if (localStorage.getItem('userRole') === "patient") {
        return <PatientSidebar/>
    }
    return (
        <AppSidebar />
    );
};
