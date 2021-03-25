# Catch & Shoot
Catch & Shoot is an intrusion detection and prevention system which uses deep learning tools in order to identify and avoid attacks on servers (based on ubuntu OS).

Created by *Ofir Shapira* and *Omri Zaiman*

## Table of contents
- [Installation] (#Installation)
- [Requirements] (#Requirements)
- [Main components] (#Main components)

## Installation
todo

## Requirements
todo

## Main components

### Sniffing unit
The Sniffing unit is a sniffer-like python program. It uses Scapy module for packets' sniffing, and saves the packets in a Sqlite3 database. 

### Model component
The model component (implemented in C++ language) is based on an ensemble of autoencoders. It analyzes metadata (jitter, packets' sizes, etc...) and determines whether each packet is considered an anomaly with respect to the server's normal behaviour.

### Defending unit
todo

### Server component
todo


