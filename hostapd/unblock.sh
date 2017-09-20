#!/usr/bin/sudo /bin/bash

if [ -z "$1" ]; then
  echo "Interface must be specified. Exit."
  exit 1
fi
# check nmcli version
# old: `nmcli nm`
# new: `nmcli r`
nmcli nm > /dev/null 2>&1
if [ $? -eq 0 ]; then
  nmcli nm wifi off
else
  nmcli r wifi off
fi
rfkill unblock wlan
ifconfig $1 up

