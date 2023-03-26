for ((i = 1 ; i <= 500 ; i++)); do
  cd /home/mypc/Desktop/Genuine_Pcaps; /opt/zeek/bin/zeek -r genuineDataset$i.pcap;
  cat /home/mypc/Desktop/Genuine_Pcaps/conn.log | /opt/zeek/bin/zeek-cut proto duration orig_pkts | awk '$1 == "icmp"' | sed  "s/\s/,/g" | sed 's/^icmp,//'   | sed "s/$/,0 /g" >> /home/mypc/Desktop/final_normal.csv;
  echo $i;
done