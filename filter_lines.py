import sys

def find_and_print_lines(input_filename, output_filename):
    try:
        # Read the input file
        with open(input_filename, 'r') as infile:
            lines = infile.readlines()

        # Find lines containing "TILE0 L1.5 th"
        filtered_lines = [line for line in lines if "TILE0 L1.5 th" in line]

        # Write filtered lines to a new file
        with open(output_filename, 'w') as outfile:
            outfile.writelines(filtered_lines)

        # Check for consecutive "Received" lines in the new file
        cntr0 = 0;		  
        for i, line in enumerate(filtered_lines):
            if "Received" in line:
                cntr0 += 1;
            else:
                cntr = cntr0;
                cntr0 = 0;
                if (cntr >= 3):
                    print(cntr, "Consecutive 'Received' lines starting from line ", (i+1-cntr))
                    for j in range (cntr):
                        print(filtered_lines[i-(cntr-j)], end="")
                    print("");


    except FileNotFoundError:
        print(f"Error: File '{input_filename}' not found.")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py input_filename.txt")
    else:
        input_filename = sys.argv[1]
        output_filename = "filtered_output.txt"
        find_and_print_lines(input_filename, output_filename)
