from flask import Flask, request, jsonify
import os,subprocess
import signal
import psutil
app = Flask(__name__)




def kill(proc_pid):
    process = psutil.Process(proc_pid)
    for proc in process.children(recursive=True):
        proc.kill()
    process.kill()

counter =1
process1= subprocess.Popen('',shell=True);
process2= subprocess.Popen('',shell=True);
@app.route('/', methods=['GET'])
def update_sensor():

    arg=request.args.get('status')
    global counter
    global process1
    global process2
    if(arg=='1'):
        print ('start genuinue traffic')
        cmd = 'dumpcap -i 1 -f "host 192.168.1.109" -P -w'+ ' ./genuine/genuineDataset'+str(counter)+'.pcap'
        counter +=1
        process1 = subprocess.Popen(cmd,shell=True)
    elif (arg =='2'):
        print ('Finished genuine traffic')
        kill(process1.pid)
    elif(arg =='3'):
        print ('start malicious traffic')
        cmd = 'dumpcap -i 1 -f "host 192.168.1.109" -P -w'+ ' ./malicious/maliciousDataset'+str(counter)+'.pcap'
        counter +=1
        process2 = subprocess.Popen(cmd,shell=True)
    elif(arg =='4'):
        print ('Finished malicious traffic')
        kill(process2.pid)

    return 'http_status 200'


if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0')
