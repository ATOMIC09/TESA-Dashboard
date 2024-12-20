import { LayoutDashboard, Grape, Server } from "lucide-react"
import { Separator } from "@/components/ui/separator"

import {
    Sidebar,
    SidebarContent,
    // SidebarFooter,
    SidebarGroup,
    // SidebarHeader,
    SidebarMenuItem,
    SidebarMenuButton,
    SidebarMenu,
    SidebarGroupContent,
    SidebarGroupLabel, 
  } from "@/components/ui/sidebar"
  
  const items: SidebarItem[] = [
    {
      title: "Machine",
      icon: LayoutDashboard,
      url: "/",
    },
    {
      title: "Server",
      icon: Server,
      url: "/server",
    },
    {
      title: "Raspberry Pi",
      icon: Grape,
      url: "/raspberrypi",
    }
  ]

  interface SidebarItem {
    title: string
    icon: React.ComponentType
    url: string
  }

  export function AppSidebar() {
    return (
      <Sidebar>
      <SidebarContent>
        <SidebarGroup>
          <SidebarGroupLabel className="font-LINESeedSansTH_W_Bd text-2xl">Menu</SidebarGroupLabel>
          <Separator className="my-2"/>
          <SidebarGroupContent>
            <SidebarMenu className="font-LINESeedSansTH_W_Rg">
              {items.map((item) => (
                <SidebarMenuItem key={item.title}>
                  <SidebarMenuButton className="text-lg" asChild>
                    <a href={item.url}>
                      <item.icon />
                      <span>{item.title}</span>
                    </a>
                  </SidebarMenuButton>
                </SidebarMenuItem>
              ))}
            </SidebarMenu>
          </SidebarGroupContent>
        </SidebarGroup>
      </SidebarContent>
    </Sidebar>
    )
  }
  