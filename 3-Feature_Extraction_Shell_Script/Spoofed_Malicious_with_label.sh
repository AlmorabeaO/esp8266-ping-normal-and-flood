#!/bin/bash

for ((i = 1 ; i <= 500 ; i++)); do
  cd /home/User/Desktop/Python/malicious/; /opt/zeek/bin/zeek -r maliciousDataset$i.pcap;


timeFirst=$(cat /home/User/Desktop/Python/malicious/conn.log  | /opt/zeek/bin/zeek-cut   proto  ts   | awk '$1 == "icmp"' | sort -n | sed  '1q;d' | awk '{print $2}');

timeLast=$(cat /home/User/Desktop/Python/malicious/conn.log  | /opt/zeek/bin/zeek-cut   proto  ts    | awk '$1 == "icmp"' | sort -n | sed -n '$p' | awk '{print $2}');

result=$(awk '{print $1-$2}' <<<"${timeLast} ${timeFirst}")

echoRequest=$(cat /home/User/Desktop/Python/malicious/conn.log  |  /opt/zeek/bin/zeek-cut  proto orig_pkts | awk '$1 == "icmp"'|  awk 'BEGIN{FS="\t"; sum=0} {sum+=$2} END{print sum}');



echo "$result, $echoRequest, 1" >> /home/User/Desktop/malicious_with_label_spoofed.csv; 

echo "$i"


done