#!/bin/bash

echo "[*] Rootkit Detection Script"

# Check LD_PRELOAD environment variable
if [[ "$LD_PRELOAD" != "" ]]; then
    echo "[!] LD_PRELOAD is set to: $LD_PRELOAD"
else
    echo "[*] LD_PRELOAD is not set."
fi

# Compare /proc vs ps output to find hidden processes
echo "[*] Checking for hidden processes..."

for pid in $(ls /proc | grep '^[0-9]'); do
    if ! ps -p $pid > /dev/null 2>&1; then
        echo "[!] Suspicious: PID $pid is in /proc but not in ps"
    fi
done

