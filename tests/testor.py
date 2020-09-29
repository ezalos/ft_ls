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
		self.list_of_errors = []

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

		mine_speed_mean = 0
		them_speed_mean = 0
		for arg in self.prepare_args():
			mine.prepare_command(arg)
			them.prepare_command(arg)

			print("TEST: ", mine.command, " && ", them.command)

			mine.launch()
			them.launch()
			print("SPEED {:<3.0f}%".format(them.time * 100 / mine.time), "Time mine: ", mine.time, " Time them ", them.time)

			mine_speed_mean += mine.time
			them_speed_mean += them.time
			out1 = mine.clean_output(colors=True, white_spaces=True)
			out2 = them.clean_output(colors=True, white_spaces=True)

			if platform.system() == 'Linux':
				os_dic = 0
			else:
				os_dic = 1
			for word, initial in month_dic.items():
				 out1 = out1.replace(word, initial[os_dic])
				 out2 = out2.replace(word, initial[os_dic])
			# self.diff_output(out1, out2)
			self.cut_folders(out1, out2)
			print()
		print("SPEED MEAN {:<3.0f}%".format(them_speed_mean * 100 / mine_speed_mean),
				"\n\tTime mine: ", mine_speed_mean,
				"\n\tTime them: ", them_speed_mean)
		# with open("tests/list_of_errors.py", "r+") as f:
		# 	f.seek(0)
		# 	f.truncate()
		# 	f.write("list_of_errors = " + self.list_of_errors)

	def cut_folders(self, out1, out2):
		my_folders = out1.split("\n\n")
		tr_folders = out2.split("\n\n")
		if len(my_folders) < len(tr_folders):
			print("Mine has", len(my_folders) - len(tr_folders), "folders missing")
			max_len_folders = len(tr_folders)
		elif len(my_folders) > len(tr_folders):
			print("Mine has", len(tr_folders) - len(my_folders), "folders excess")
			max_len_folders = len(my_folders)
		else:
			max_len_folders = len(my_folders)
		try:
			for folder in range(max_len_folders):
				last_index = folder
				if my_folders[folder] != tr_folders[folder]:
					if (max_len_folders > 1):
						self.list_of_errors.append(my_folders[folder].split("\n")[0])
						# print("ERROR for my_folder: ", my_folders[folder].split("\n")[0])
						print("ERROR for folder: ", tr_folders[folder].split("\n")[0][:-2])
					self.cut_lines(my_folders[folder], tr_folders[folder])
		except IndexError:
			return None
			if len(my_folders) < len(tr_folders):
				print("Missing folders for mine:")
				for folder in range(last_index, max_len_folders):
					print("Them: ", folder, "/", max_len_folders)
					print(YELLOW + tr_folders[folder] + RESET + "\n")
			else:
				print("Excess folders for mine")
				for folder in range(last_index, max_len_folders):
					print("Mine: ", folder, "/", max_len_folders)
					print(YELLOW + my_folders[folder] + RESET + "\n")


	def cut_lines(self, out1, out2):
		my_lines = out1.split("\n")
		tr_lines = out2.split("\n")
		if len(my_lines) < len(tr_lines):
			print("Mine has", len(my_lines) - len(tr_lines), "lines missing")
			max_len_lines = len(tr_lines)
		elif len(my_lines) > len(tr_lines):
			print("Mine has", len(tr_lines) - len(my_lines), "lines excess")
			max_len_lines = len(my_lines)
		else:
			max_len_lines = len(my_lines)
		try:
			for line in range(max_len_lines):
				last_index = line
				if my_lines[line] != tr_lines[line]:
					self.cut_columns(my_lines[line], tr_lines[line], line)
				else:
					print(" " * 8, tr_lines[line])
		except IndexError:
			if len(my_lines) < len(tr_lines):
				print("Missing lines for mine:")
				for line in range(last_index, max_len_lines):
					print(" " * 8, YELLOW + tr_lines[line] + RESET + " ")
			else:
				print("Excess lines for mine")
				for line in range(max_len_lines):
					print(" " * 8, YELLOW + my_lines[line] + RESET + " ")

	def cut_columns(self, out1, out2, line_nb):
		my_cols = out1.split(" ")
		tr_cols = out2.split(" ")
		if len(my_cols) < len(tr_cols):
			print("Mine has", len(my_cols) - len(tr_cols), "cols missing")
			max_len_cols = len(tr_cols)
		elif len(my_cols) > len(tr_cols):
			print("Mine has", len(tr_cols) - len(my_cols), "cols excess")
			max_len_cols = len(my_cols)
		else:
			max_len_cols = len(my_cols)
		err_my = ""
		err_tr = ""
		for col in range(max_len_cols):
			try:
				if my_cols[col] != tr_cols[col]:
					err_my += RED + my_cols[col] + RESET + " "
					err_tr += RED + tr_cols[col] + RESET + " "
				else:
					err_my += GREEN + my_cols[col] + RESET + " "
					err_tr += GREEN + tr_cols[col] + RESET + " "
			except IndexError:
				if len(my_cols) < len(tr_cols):
					err_tr += YELLOW + tr_cols[col] + RESET + " "
				else:
					err_my += YELLOW + my_cols[col] + RESET + " "
		if err_my:
			 print("{:<4d}my: ".format(line_nb), err_my)
			 print("    tr: ", err_tr)
		else:
			 print("{:<4d}my: ".format(line_nb), out1)
			 print("    tr: ", out2)

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
	folders = [".", "tests", "tests/types", "tests/dates", "tests/rights", "~"]
	# folders = ["tests/dates"]
	test = Comparator("./ft_ls -lR", "LANG=C ls -lR", arguments, folders)
	test.pipeline()
	# test = Comparator("./ft_ls -lR", "LANG=C ls -lR", arguments, folders)
	# test.pipeline()
