#!/bin/bash
clear
echo "Strat executing"
gnome-terminal -- sh -c "python3 ./DefenderComponent/Defender.py; bash"
sleep 2
gnome-terminal -- sh -c "python3 ./SnifferComponent/SnifferToSqlite.py; bash"
sleep 4
gnome-terminal -- sh -c "./ModelComponent/cmake-build-debug/idps-20-21; bash"