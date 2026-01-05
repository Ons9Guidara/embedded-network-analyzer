# Embedded Network Traffic Analyzer

A lightweight network packet capture tool for embedded Linux, written in C using `libpcap`.  
It captures TCP and UDP packets, counts them, and computes total bytes in real time.  



---

## Features

- Captures TCP and UDP packets on a specified network interface
- Counts packets per protocol
- Computes total bytes transmitted
- Real-time console output
- Lightweight and efficient C implementation for embedded Linux

---

## Requirements

- Linux environment (tested on Ubuntu)
- `libpcap` library installed

sudo apt install libpcap-dev
## Installation & Usage

### 1. Compile
make

### 2. Run
sudo make run

### 3. Clean compiled files
make clean


### 4. Testing
python3 -m http.server 8080 &
curl http://127.0.0.1:8080

### Generate UDP traffic: 
nc -ul 5005
echo "hello UDP" | nc -u 127.0.0.1 5005
### After sending traffic, the analyzer prints a live summary
 
