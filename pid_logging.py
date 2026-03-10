import serial
import csv

port = '/dev/cu.usbmodem101'   # change if needed
baud = 9600

ser = serial.Serial(port, baud)

with open("pid_log.csv", "w", newline="") as f:
    writer = csv.writer(f)

    writer.writerow([
        "time_ms",
        "s1",
        "s2",
        "s3",
        "errorX",
        "errorY",
        "posX",
        "posY"
    ])

    print("Logging... press Ctrl+C to stop")

    try:
        while True:
            line = ser.readline().decode().strip()
            if line:
                parts = line.split(",")
                if len(parts) == 8:
                    writer.writerow(parts)

    except KeyboardInterrupt:
        print("Logging stopped")