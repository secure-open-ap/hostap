#!/usr/bin/sudo /bin/bash
if [ -z "$1" ]; then
  echo "Interface must be specified. Exit."
  exit 1
fi
nmcli nm wifi off
rfkill unblock wlan
ifconfig $1 up

