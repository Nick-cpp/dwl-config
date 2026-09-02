#!/bin/bash

choice=$(echo -e "Reboot\nShutdown" | wmenu -f "JetBrainsMono Nerd Font Bold 12" -p "Power Menu:")

case "$choice" in
    "Reboot")
        confirm=$(echo -e "Yes\nNo" | wmenu -f "JetBrainsMono Nerd Font Bold 12" -p "Reboot?")
        if [ "$confirm" = "Yes" ]; then
            pkill -15 -x dwl
            loginctl reboot
        fi
        ;;
    "Shutdown")
        confirm=$(echo -e "Yes\nNo" | wmenu -f "JetBrainsMono Nerd Font Bold 12" -p "Shutdown?")
        if [ "$confirm" = "Yes" ]; then
            pkill -15 -x dwl
            loginctl poweroff
        fi
        ;;
esac
