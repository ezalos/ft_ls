import subprocess
import re
import time
import platform

PURPLE = '\033[95m'
BLUE = '\033[94m'
GREEN = '\033[92m'
YELLOW = '\033[93m'
RED = '\033[91m'
RESET = '\033[0m'
BOLD = '\033[1m'
UNDERLINE = '\033[4m'

month_dic = {
	"Jan" : ["janv.", "jan"],
	"Feb" : ["févr" , "fév"],
	"Mar" : ["mars" , "mar"],
	"Apr" : ["avril", "avr"],
	"May" : ["mai"  , "mai"],
	"Jun" : ["juin" , "jui"],
	"Jul" : ["juil.", "jul"],
	"Aug" : ["août" , "aoû"],
	"Sep" : ["sept.", "sep"],
	"Oct" : ["oct." , "oct"],
	"Nov" : ["nov." , "nov"],
	"Dec" : ["déc.", "déc"]
}


class BinCute():
	def __init__(self, binary, leaks=False):
		self.binary = binary
		self.command = ""
		self.raw_output = None
		self.output = ""
		self.time = None
		self.leaks = leaks

	def prepare_command(self, args):
		self.command = self.binary
		if type(args) == type(""):
			self.command += " " + args
		elif type(args) == type([]):
			for arg in args:
				self.command += " " + str(arg)
		else:
			print("Wrong args tyoe: ", type(args))

	def launch(self):
		  t = time.clock()
		  # print(self.command)
		  self.raw_output = subprocess.run(self.command, stdout=subprocess.PIPE,
										  stderr=subprocess.PIPE, shell=True)
		  self.time = time.clock() - t
		  self.stdout = self.raw_output.stdout.decode('utf-8')
		  self.stderr = self.raw_output.stderr.decode('utf-8')

	def clean_output(self, colors=False, white_spaces=False):
		output = self.stdout
		if colors:
				output = re.sub(r'[\t ]+', r' ', output)
		if white_spaces:
			output = re.sub(r'\x1b\[[0-9;]+m', r'', output)
		self.output = output
		return self.output

import itertools

class Comparator():
	def __init__(self, my_work, reference_work, possible_arguments, folders):
		self.my_bin = my_work
		self.tr_bin = reference_work
		self.possible_arguments = possible_arguments
		self.folders = folders
		self.args = ""

	def prepare_args(self):
		for folder in self.folders:
			for i in range(len(self.possible_arguments)):
				arg_comb = list(itertools.combinations(self.possible_arguments, i))
				for comb in arg_comb:
					next = list(comb)
					if next:
						next.append(folder)
					else:
						next = folder
					yield next

	def launch(self, args=['.']):
		mine = BinCute(self.my_bin)
		them = BinCute(self.tr_bin)

		for arg in self.prepare_args():
			mine.prepare_command(arg)
			them.prepare_command(arg)

			print("TEST: ", mine.command, " && ", them.command)

			mine.launch()
			them.launch()

			out1 = mine.clean_output(colors=True, white_spaces=True)
			out2 = them.clean_output(colors=True, white_spaces=True)

			if platform.system() == 'Linux':
				os_dic = 0
			else:
				os_dic = 1
			for word, initial in month_dic.items():
				 out1 = out1.replace(word, initial[os_dic])
			self.diff_output(out1, out2)
			print()

	def diff_output(self, out1, out2):
		col_type = {0 : "rights",
					1 : "link count",
					2 : "owner",
					3 : "gr_owner",
					4 : "size",
					5 : "month",
					6 : "day",
					7 : "hour/year",
					8 : "name"}

		my_lines = out1.split("\n")
		tr_lines = out2.split("\n")
		if len(my_lines) != len(tr_lines):
			# if len(my_lines) > len(tr_lines):
			#
			print("Different number of lines.")
		else:
			len_lines = len(my_lines)

		for line in range(len(tr_lines)):
			my_line = my_lines[line].split(" ")
			tr_line = tr_lines[line].split(" ")
			if len(my_line) != len(tr_line):
				 print("Different number of colunms on line ", line)
			err_my = ""
			err_tr = ""
			# if my_line != tr_line:
			if my_line != tr_line:
				for col in range(len(tr_line)):
					try:
						if my_line[col] != tr_line[col]:
							err_my += RED + my_line[col] + RESET + " "
							err_tr += RED + tr_line[col] + RESET + " "
							  # err += "  " + str(col) + ": " + col_type[col] + "\n"
							  # err += "\tmy: " + my_line[col] + "\n"
							  # err += "\ttr: " + tr_line[col] + "\n"
						else:
							err_my += GREEN + my_line[col] + RESET + " "
							err_tr += GREEN + tr_line[col] + RESET + " "
					except IndexError:
						if len(my_line) < len(tr_line):
							err_tr += YELLOW + tr_line[col] + RESET + " "
						else:
							err_my += YELLOW + my_line[col] + RESET + " "
				# else:
				# 	print("      : ", my_lines[line])
				# 	break

			if err_my:
				 print("{:<4d}my: ".format(line), err_my)
				 print("    tr: ", err_tr)


	def pipeline(self):
		self.launch()

if __name__ == "__main__":
	arguments = ['']#-l -R, '-t'
	folders = [".", "tests", "tests/types", "tests/dates", "tests/rights"]
	# folders = ["tests/dates"]
	test = Comparator("./ft_ls -lR", "LANG=C ls -lR", arguments, folders)
	test.pipeline()
	# test = Comparator("./ft_ls -lR", "LANG=C ls -lR", arguments, folders)
	# test.pipeline()
