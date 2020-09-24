import subprocess
import re

class Comparator():
    def __init__(self, my_work, reference_work, possible_arguments):
        self.my_bin = my_work
        self.tr_bin = reference_work

    def prepare_args(self):
        pass

    def launch(self, args=['.']):
        snds = args.copy()
        self.my_args = args.insert(0, self.my_bin)
        self.tr_args = snds.insert(0, self.tr_bin)

        self.my_args = "./ft_ls -al /"
        self.tr_args = "ls -al /"
        print("Launch my: ", self.my_args)
        self.my_output = subprocess.run(self.my_args, stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE, shell=True)
        print("Launch tr: ", self.tr_args)
        self.tr_output = subprocess.run(self.tr_args, stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE, shell=True)

        self.my_stdout = self.my_output.stdout.decode('utf-8')
        self.my_stderr = self.my_output.stderr.decode('utf-8')

        #print(self.tr_output)
        self.tr_stdout = self.tr_output.stdout.decode('utf-8')
        #self.tr_stderr = self.tr_output.stderr.decode('utf-8')


    def clean_output(self):
        self.my_cl_stdout = re.sub(r'[\t ]+', r' ', self.my_stdout)
        self.my_cl_stdout = re.sub(r'\x1b\[[0-9;]+m', r'', self.my_cl_stdout)
        #print(self.tr_stdout)
        self.tr_cl_stdout = re.sub(r'[\t ]+', r' ', self.tr_stdout)
        #print(self.tr_cl_stdout)

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
            print("Different number of lines.")
        for line in range(len(tr_lines)):
            my_line = my_lines[line].split(" ")
            tr_line = tr_lines[line].split(" ")
            if len(my_line) != len(tr_line):
                print("Different number of colunms on line ", line)
            err = ""
            for col in range(len(tr_line)):
                if col != 5 and my_line[col] != tr_line[col]:
                    err += "  " + str(col) + ": " + col_type[col] + "\n"
                    err += "\tmy: " + my_line[col] + "\n"
                    err += "\ttr: " + tr_line[col] + "\n"
            if err:
                print("LINE ", line)
                print("  my: ", my_lines[line])
                print("  tr: ", tr_lines[line])
                print(err)


    def pipeline(self):
        self.launch()
        self.clean_output()
        self.diff_output(self.my_cl_stdout, self.tr_cl_stdout)

if __name__ == "__main__":
    test = Comparator("./ft_ls", "ls", ['-R', '-r', '-l', '-a', '-t'])
    test.pipeline()
