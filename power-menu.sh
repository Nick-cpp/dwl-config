#!/bin/bash

choice=$(echo -e "Reboot\nShutdown" | wmenu -f "JetBrainsMono Nerd Font Bold 12" -p "Power Menu:")

case "$choice" in
    "Reboot")
        confirm=$(echo -e "Yes\nNo" | wmenu -p "Reboot?")
        if [ "$confirm" = "Yes" ]; then
            pkill -15 -x Hyprland
            loginctl reboot
        fi
        ;;
    "Shutdown")
        confirm=$(echo -e "Yes\nNo" | wmenu -p "Shutdown?")
        if [ "$confirm" = "Yes" ]; then
            pkill -15 -x Hyprland
            loginctl poweroff
        fi
        ;;
esac
