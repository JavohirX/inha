import {Calendar, Home, Inbox, LogOut, Search, Settings, Hospital,Clock9, ClipboardPlus} from "lucide-react"

import {
    Sidebar,
    SidebarContent,
    SidebarGroup,
    SidebarGroupContent,
    SidebarGroupLabel, SidebarHeader,
    SidebarMenu,
    SidebarMenuButton,
    SidebarMenuItem,
} from "@/components/ui/sidebar"
import {Avatar, AvatarFallback} from "@/components/ui/avatar";
import {
    DropdownMenu,
    DropdownMenuContent,
    DropdownMenuItem,
    DropdownMenuLabel, DropdownMenuSeparator,
    DropdownMenuTrigger
} from "@/components/ui/dropdown-menu";
import {Link, useLocation} from "react-router";
import {cn} from "@/lib/utils";

// Menu items.
const items = [
    {
        title: "Hospitals",
        url: "/patient_menu",
        icon: Hospital,
    },
    {
        title: "Notifications",
        url: "/patient_notify",
        icon: Inbox,
    },
    {
        title: "My Appointments",
        url: "/appoints",
        icon: Clock9,
    },
    {
        title: "Case History",
        url: "/case_history",
        icon: ClipboardPlus,
    },
]

export function PatientSidebar() {
    const location = useLocation();
    return (
        <Sidebar>
            <SidebarContent>
                <SidebarHeader>
                    <DropdownMenu>
                        <DropdownMenuTrigger asChild>
                            <SidebarMenuButton
                                size="lg"
                                className="data-[state=open]:bg-sidebar-accent data-[state=open]:text-sidebar-accent-foreground"
                            >
                                <Avatar className="h-8 w-8 rounded-lg">
                                    <AvatarFallback className="rounded-lg">A</AvatarFallback>
                                </Avatar>
                                <div className="grid flex-1 text-left text-sm leading-tight">
                                    <span className="truncate font-semibold">Akmal Sodikov</span>
                                    <span className="truncate">Patient</span>
                                </div>

                            </SidebarMenuButton>
                        </DropdownMenuTrigger>
                        <DropdownMenuContent
                            side='right'
                            className="w-[--radix-dropdown-menu-trigger-width] min-w-56 rounded-lg"
                            align="end"
                            sideOffset={4}
                        >
                            <DropdownMenuLabel className="p-0 font-normal">
                                <div className="flex items-center gap-2 px-1 py-1.5 text-left text-sm">
                                    <Avatar className="h-8 w-8 rounded-lg">
                                        <AvatarFallback className="rounded-lg">CN</AvatarFallback>
                                    </Avatar>
                                    <div className="grid flex-1 text-left text-sm leading-tight">
                                        <span className="truncate font-semibold">Akmal</span>
                                        <span className="truncate text-xs">ID:U2210214</span>
                                    </div>
                                </div>
                            </DropdownMenuLabel>
                            <DropdownMenuSeparator />
                            <DropdownMenuItem>
                                <LogOut/>
                                Log out
                            </DropdownMenuItem>
                        </DropdownMenuContent>
                    </DropdownMenu>

                </SidebarHeader>

                <SidebarGroup>
                    <SidebarGroupLabel>Menu</SidebarGroupLabel>
                    <SidebarGroupContent>
                        <SidebarMenu>
                            {items.map((item) => {
                                const isActive = location.pathname === item.url;
                                return (<SidebarMenuItem autoFocus={true} key={item.title}>
                                    <SidebarMenuButton className={cn(
                                        "w-full",
                                        isActive && "bg-accent text-accent-foreground"
                                    )} asChild>
                                        {/* Use React Router's Link for navigation */}
                                        <Link defaultValue={'/patient_menu'} to={item.url}>
                                            <item.icon />
                                            <span>{item.title}</span>
                                        </Link>
                                    </SidebarMenuButton>
                                </SidebarMenuItem>)
                            })}
                        </SidebarMenu>
                    </SidebarGroupContent>
                </SidebarGroup>
            </SidebarContent>
        </Sidebar>
    )
}
