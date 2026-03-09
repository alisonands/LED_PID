import serial
import csv

# Arduino port '/dev/cu.usbmodem1101'
arduino_port = '/dev/cu.usbmodem1101'
baud_rate = 9600

ser = serial.Serial(arduino_port, baud_rate)

# create and write CSV file
with open('pid_errors.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    # header
    writer.writerow(['time_ms', 'errorX', 'errorY'])
    
    print("Logging errors...")
    
    try:
        while True:
            line = ser.readline().decode('utf-8').strip()
            if line:
                # expect Arduino line format: millis,errorX,errorY
                parts = line.split(',')
                if len(parts) == 3:
                    writer.writerow(parts)
    except KeyboardInterrupt:
        print("Logging stopped.")