from flask import Flask, request, jsonify, Response
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
        # cmd = 'dumpcap -i 1 -f "host 192.168.1.120" -P -w'+ ' ./genuine/genuineDataset'+str(counter)+'.pcap'
        cmd = 'dumpcap -i 1  -P -w' + ' ./genuine/genuineDataset' + str(counter) + '.pcap'
        counter +=1
        process1 = subprocess.Popen(cmd,shell=True)
    elif (arg =='2'):
        print ('Finished genuine traffic')
        kill(process1.pid)
    elif(arg =='3'):
        print ('start malicious traffic '+str(counter))
        cmd = 'dumpcap -i 1 -f "icmp and host not 192.168.2.152 and host not 192.168.2.1" -P -w'+ ' ./malicious/maliciousDataset'+str(counter)+'.pcap'
        counter +=1
        process2 = subprocess.Popen(cmd,shell=True)
    elif(arg =='4'):
        print ('Finished malicious traffic')
        kill(process2.pid)

    return Response(status=200, mimetype='application/json')


if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0')
