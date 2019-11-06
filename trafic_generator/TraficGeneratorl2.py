from scapy.all import *
import random

def rand_mac():
    return "%02x:%02x:%02x:%02x:%02x:%02x" % (
        random.randint(0, 255),
        random.randint(0, 255),
        random.randint(0, 255),
        random.randint(0, 255),
        random.randint(0, 255),
        random.randint(0, 255)
        )

packets = []
port_num = int(input())
out_dir = input().strip()

for i in range(port_num):
    packets.append([])


counter = 0

mac_addresses = []

while True:
    words = input().split()
    if len(words) == 1:
        break


    dst_mac = rand_mac()
    mac_addresses.append(dst_mac)

    dst_ip = words[0]
    packets[counter % port_num].append(Ether(dst=dst_mac) / (IP(dst=dst_ip)/TCP(flags="FS")))
    counter += 1

for now_port_num in range(port_num):
    wrpcap(f"{out_dir}/port{str(now_port_num).zfill(2)}_in.pcap", packets[now_port_num])

mac_file = open("mac_out.txt", "w")

for mac in mac_addresses:
    mac_file.write(mac+"\n")
