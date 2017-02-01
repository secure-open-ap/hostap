#!/usr/bin/sudo /bin/bash
nmcli nm wifi off
rfkill unblock wlan
ifconfig $1 up

