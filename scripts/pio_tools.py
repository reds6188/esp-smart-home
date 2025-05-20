import configparser, csv
import log

def get_board(device):
    return 'esp32dev' if device == 'ESP32' else 'esp32s3usbotg'

# Read Software Version from "platformio.ini"
def get_software_version(device):
    key = 'sw_version'
    board = get_board(device)
    config = configparser.ConfigParser()
    config.read('./platformio.ini')

    if key in config['env:'+board]:
        return config['env:'+board][key]

    log_error(f'ERROR: "{key}" not found')
    return ''

# Return the partiton table from "platformio.ini"
def get_partition_table(device):
    key = 'board_build.partitions'
    board = get_board(device)
    config = configparser.ConfigParser()
    config.read('./platformio.ini')
    if key in config['env:'+board]:
        partitions_csv = config['env:'+board][key]
        with open('./' + partitions_csv, 'r') as csv_file:
            reader = csv.reader(csv_file, delimiter=',')
            return list(reader)

    log_error('No partition table was specified')
    return []

# Return the size of a specific partition
def get_partition_size(device, partition):
    table = get_partition_table(device)
    for row in table:
        if row[0] == partition:
            address = row[3].strip()
            size = row[4].strip()
            log_info(f'"{partition}" partition found at address {address} with size {size}')
            return size

    log_error(f'"{partition}" partition not found')
    return 0