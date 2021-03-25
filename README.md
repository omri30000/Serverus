# Serverus
Serverus is an intrusion detection and prevention system which uses deep learning tools in order to identify and avoid attacks on servers (based on ubuntu OS).

The name "Serverus" is influenced by the great Cerberus from the greek mythology. A Cerberus (often referred to as the hound of Hades) is a creature which resembles to a multi-headed dog, and guards the gates of the Underworld. Since our product's main goal is defending servers from attack, we've found it exteremely similar to the Cerberus.  

Created by *Ofir Shapira* and *Omri Zaiman* as a final project of Magshimim - the Israeli national cyber program. 

## Table of contents
[[_TOC_]]

## Installation
1. Register to our website [here](http://defence.rocks/), it will provide you the project files with a uniqe identifier that was generated especially for you. 

## Requirements
Make sure you have the following technologies installed in your machine:
#### Python modules
- scapy (for sniffing) --> `sudo pip install scapy`
- pika (for message queue) --> `pip install pika`
- Json --> built in module

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


