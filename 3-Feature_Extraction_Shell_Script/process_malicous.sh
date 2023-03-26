for ((i = 1 ; i <= 500 ; i++)); do
  cd /home/mypc/Desktop/Malicious_Pcaps/; /opt/zeek/bin/zeek -r maliciousDataset$i.pcap;
  cat /home/mypc/Desktop/Malicious_Pcaps/conn.log | /opt/zeek/bin/zeek-cut proto duration orig_pkts  | awk '$1 == "icmp"' | sed  "s/\s/,/g" | sed 's/^icmp,//'   | sed "s/$/,1 /g" >> /home/mypc/Desktop/final_Malicious.csv;
  echo $i;
done