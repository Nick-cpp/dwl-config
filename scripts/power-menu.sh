#!/bin/bash

WMENU_OPTS="-f 'JetBrainsMono Nerd Font Bold 12' -N '#1e2030' -n '#c0caf5' -S '#7aa2f7' -s '#15161e' -M '#1e2030'"

choice=$(echo -e "Reboot\nShutdown" | eval wmenu $WMENU_OPTS -p '"Power Menu:"')

case "$choice" in
    "Reboot")
        confirm=$(echo -e "Yes\nNo" | eval wmenu $WMENU_OPTS -p '"Reboot?"')
        if [ "$confirm" = "Yes" ]; then
            pkill -15 -x dwl
            loginctl reboot
        fi
        ;;
    "Shutdown")
        confirm=$(echo -e "Yes\nNo" | eval wmenu $WMENU_OPTS -p '"Shutdown?"')
        if [ "$confirm" = "Yes" ]; then
            pkill -15 -x dwl
            loginctl poweroff
        fi
        ;;
esac
