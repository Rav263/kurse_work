#! /bin/python
from scapy.all import *

packets = []
port_num = int(input())
out_dir = input().strip()

for i in range(port_num):
    packets.append([])

counter = 0

while True:
    words = input().split()
    if len(words) == 1:
        break

    dst_ip = words[0]
    packets[counter % port_num].append(IP(dst=dst_ip)/TCP(flags="FS"))
    counter += 1

for now_port_num in range(port_num):
    wrpcap(f"{out_dir}/port{str(now_port_num).zfill(2)}_in.pcap", packets[now_port_num])
