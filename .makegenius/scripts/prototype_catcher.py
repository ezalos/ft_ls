import re
import os
import sys
import math

prototype_pattern = r"(?#                                       \
)(?:^|\n)(?#						        BEGIN condition\
)((?#							        -\
	)[a-zA-Z_-]+(?#				                Return type\
	)\t+(?#							-\
	)\*?[a-zA-Z_-]+(?#					Function name\
		)\((?:(?#					arg begin\
	        	)[a-zA-Z_-]+ \*?[a-zA-Z_-]+(?#	        argument\
			)(?:,\s+)?(?#			        whitespace\
		))+\)(?#				    	arg end\
))(?#								-\
)\n\{(?#							END condition\
)"


comment_pattern = r"\/\*([^\*]*((?!\*\/)[\x00-\x7f])?)*\*\/"

def file_list(directory):
    list_of_files = []
    for (dirpath, dirnames, filenames) in os.walk(directory):
        for f in filenames:
            if f[-2:] == ".c":
                list_of_files.append(dirpath + "/" + f)
    return list_of_files

def get_file_protos(file_path):
    with open(file_path) as f:
        content = f.read()
    cleaned_file = re.sub(comment_pattern, "", content)
    protos = re.findall(prototype_pattern, cleaned_file)
    return protos

def sort_protos(protos):
    sort_func = lambda x: x[re.search(r"^[^\t]+\t+", x).end():]
    all_protos = []
    for f in protos:
        for p in f:
            all_protos.append(p)
    protos = sorted(all_protos, key=sort_func)
    return protos

def align_protos(protos):
    tab_size = 4
    type_len = lambda x: len(x[:re.search(r"^[^\t]+", x).end()])
    len_type = 0
    for i in protos:
        if type_len(i) > len_type:
            len_type = type_len(i)
    len_type += 1 + 1
    nb_of_tabs = lambda x: math.ceil((len_type - type_len(x)) / tab_size)
    tab = []
    for i in protos:
        new_proto = re.sub(r'(^[^\t]+)\t+', r'\g<1>' + r'\t' * nb_of_tabs(i), i)
        new_proto = re.sub(r'\n\t+', r'\n' + r'\t' * (math.ceil(len_type / tab_size) + 0), new_proto)
        tab.append(new_proto)
    protos = tab
    return protos

def generate_header(protos, name="test", subname=""):
    define = "AUTO_" + name.upper() + "_" + subname.upper() + "_H"
    header = "#ifndef " + define + "\n"
    header += "# define " + define + "\n"
    header += "\n"
    for proto in protos:
        header += proto + ";" + "\n"
    header += "\n"
    header += "#endif"
    print(header)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("USAGE:\n\t" + "pyhton3 " + sys.argv[0] + " folder_to_explore " + " file_to_write")
    else:
        files = file_list(sys.argv[1])
        protos = []
        for f in files:
            protos.append(get_file_protos(f))
        protos = sort_protos(protos)
        protos = align_protos(protos)
        generate_header(protos)

