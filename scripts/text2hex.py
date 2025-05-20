import os
from log import *

src_dir = "data"
dst_dir = "src"
dst_file = "html"
total_count = 0

# Create destination directory if it doesn't exist
if not os.path.exists(dst_dir):
    os.makedirs(dst_dir)

def text2hex(file, single_file, overwrite):
    mode = "w" if overwrite else "a"
    count = 0
    index = 0
    end_of_line = 16
    cpp_file = ""
    h_file = ""

    # Check if path is a file or directory
    if os.path.isdir('/'.join([src_dir, file])):
        print(f'"{file}" is a directory, skip...')
        return 0

    file_name = file.split('.')[0]
    file_ext = file.split('.')[1]

    cpp_file = (dst_file if single_file else file_name) + ".cpp"
    h_file = (dst_file if single_file else file_name) + ".h"
    
    if single_file:
        mode = "a"
    
    f_in = open('/'.join([src_dir, file]), "r")

    f_buffer = ""
    while 1:
        char = f_in.read(1)
        if not char: 
            break
        #if char == '\n' or char == '\t':
        #    continue
        count += 1
        f_buffer += f'0x{ord(char):02X}, '
        index += 1
        if index == end_of_line:
            index = 0
            #f_out.write('\n\t')
            f_buffer += '\n\t'
        #print(f.read())

    # Write to output file
    var_name = '_'.join([file_name, file_ext]).upper().replace('-','_')

    f_out = open('/'.join([dst_dir, cpp_file]), mode)
    f_out.write(f'const uint8_t {var_name}[{count}] PROGMEM = {{\n\t')
    f_out.write(f_buffer)
    f_out.write('\n};\n')
    f_out.close()

    f_out = open('/'.join([dst_dir, h_file]), mode)
    f_out.write(f'#define {var_name}_PATH "/{file}"\n')
    f_out.write(f'extern const uint8_t {var_name}[{count}];\n\n')
    f_out.close()

    print(f'>>> Written {count} byte(s)')
    return count

# Create new files and initialize them
cpp_file = dst_file + ".cpp"
h_file = dst_file + ".h"

cpp_out = open('/'.join([dst_dir, cpp_file]), "w")
cpp_out.write(f'#include "{h_file}"\n\n')
cpp_out.close()

h_out = open('/'.join([dst_dir, h_file]), "w")
h_out.write(f'#ifndef {dst_file.upper()}_H_\n#define {dst_file.upper()}_H_\n\n#include <Arduino.h>\n\n')
h_out.close()

files = os.listdir(src_dir)
for x in files:
	if x[0] == '.':
		print(f'Skipping \"{x}\"...')
		continue
	print(f'Processing \"{x}\"...')
	total_count += text2hex(x, True, True)


h_out = open('/'.join([dst_dir, h_file]), "a")
h_out.write(f'\n// Total count: {total_count} bytes\n\n')
h_out.write(f'\n#endif  /* {dst_file.upper()}_H_ */')
h_out.close()

log_info(f'FINISH! Total count = {total_count} bytes')