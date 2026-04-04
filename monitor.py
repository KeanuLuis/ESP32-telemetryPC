from flask import Flask, jsonify
import psutil
import threading
import time
import requests

app = Flask(__name__)

cpu_usage = 0
ram_usage = 0
cpu_temp = 0
gpu_temp = 0
storage_percent = 0
uptime_str = "0h 0m"



def read_lhm():
    global cpu_temp, gpu_temp

    try:
        data = requests.get("http://YOUR_MACHINE_IP:8085/data.json").json()

        cpu_temp = 0
        gpu_temp = 0

        def search(node, current_hardware=""):
            global cpu_temp, gpu_temp

            
            text = node.get("Text", "").lower()
            image = node.get("ImageURL", "").lower()

            if "cpu" in image or "intel" in text or "amd" in text or "ryzen" in text:
                current_hardware = "CPU"
            elif "nvidia" in image or "ati" in image or "radeon" in text or "rtx" in text or "gtx" in text:
                current_hardware = "GPU"

            value_raw = str(node.get("Value", "")).upper() 
            
            if "°C" in value_raw:
                clean_value = value_raw.replace(" °C", "").replace(",", ".")
                temp = float(clean_value)

                if current_hardware == "CPU" and cpu_temp == 0:
                    cpu_temp = temp
                    print(f"✔️ CPU Temp Success: {cpu_temp}°C (sensor name: {node.get('Text')})")
                
                elif current_hardware == "GPU" and gpu_temp == 0:
                    gpu_temp = temp
                    print(f"✔️ GPU Temp Success: {gpu_temp}°C (sensor name: {node.get('Text')})")

            if "Children" in node:
                for child in node["Children"]:
                    search(child, current_hardware)

        search(data)

    except Exception as e:
        print("LHM error:", e)


def monitor_pc():
    global cpu_usage, ram_usage, storage_percent, uptime_str

    while True:
        cpu_usage = psutil.cpu_percent(interval=1)
        ram_usage = psutil.virtual_memory().percent
        main_drive = psutil.disk_partitions()[0].mountpoint
        storage_percent = psutil.disk_usage(main_drive).percent
        uptime_seconds = time.time() - psutil.boot_time()
        horas = int(uptime_seconds // 3600)
        minutos = int((uptime_seconds % 3600) // 60)
        uptime_str = f"{horas}h {minutos}m"

        read_lhm()

        time.sleep(1)


threading.Thread(target=monitor_pc, daemon=True).start()


@app.route('/stats')
def stats():
    return jsonify({
        "cpu": cpu_usage,
        "ram": ram_usage,
        "temp": cpu_temp,
        "gpu_temp": gpu_temp,
        "storage": storage_percent,
        "uptime": uptime_str
    })


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
