# Serverus
Serverus is an intrusion detection and prevention system which uses deep learning tools in order to identify and avoid attacks on servers (based on ubuntu OS).

Created by *Ofir Shapira* and *Omri Zaiman*

## Table of contents
todo

## Installation
1. Register to our website [here](http://defence.rocks/), it will provide you the project files with a uniqe identifier that was generated especially for you. 

## Requirements
Make sure you have the following technologies installed in your machine:
#### Python modules
- pika (for message queue)
- Json

## Instructions
todo

## Main components

### Sniffing unit
The Sniffing unit is a sniffer-like python program. It uses Scapy module for packets' sniffing, and sends the packets to the model using message queuing.

### Model component
The model component (implemented in C++ language) is based on an ensemble of autoencoders. It analyzes metadata (jitter, packets' sizes, etc...) and determines whether each packet is considered an anomaly with respect to the server's normal behaviour.

### Defending unit
todo

### Server component
todo

## Examples
todo

## Credits
todo


