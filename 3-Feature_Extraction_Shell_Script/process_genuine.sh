for ((i = 1 ; i <= 500 ; i++)); do
  cd /home/User/Desktop/Python/Genuine_Pcaps; /opt/zeek/bin/zeek -r genuineDataset$i.pcap;
  cat /home/User/Desktop/Python/Genuine_Pcaps/conn.log | /opt/zeek/bin/zeek-cut proto duration orig_pkts | awk '$1 == "icmp"' | sed  "s/\s/,/g" | sed 's/^icmp,//'   | sed "s/$/,0 /g" >> /home/User/Desktop/final_normal.csv;
  echo $i;
  find /home/User/Desktop/Python/Genuine_Pcaps -maxdepth 1 -type f -name "*.log" -print0 | xargs -I{} -0 mv {} /home/User/Desktop/Python/Genuine_Logs/logs$i;
done