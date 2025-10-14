from pathlib import Path


def part_1(input_file: str):
    with open(input_file, "r") as f:
        puzzle_contents = f.read().splitlines()

    # loop through each line of the puzzle input
    # the index of the puzzle_contents is the row #
    # the index of the line is the column #
    part_digits = {}
    for row, line in enumerate(puzzle_contents):
        for col, char in enumerate(line):
            # if the char in the line not a number and not = to . then we know
            # it is a symbol
            if char != "." and not char.isnumeric():
                # Now we are going to check every char between the row - 1
                # and row + 1 and column - 1 and column + 1 as long as it is
                # not out of the length of the rows and columns to see if it
                # is a number, then we know that we have a part number
                # no need to check where the r = row and c = column because that
                # is the symbol
                for r in range(max(0, row - 1), min(len(puzzle_contents) + 1, row + 2)):
                    for c in range(max(0, col - 1), min(len(line) + 1, col + 2)):
                        if puzzle_contents[r][c].isnumeric():
                            # now know this row col is a part digit (we dont know the full number yet)
                            if not part_digits.get(r):
                                part_digits[r] = {}
                            part_digits[r][c] = False
    part_numbers = []
    # the logic here is to loop through every valid part digit we found and figure
    # out the full part number by checking for continous digits
    # I first walk backwards from the start col of the valid digit and check to
    # see if the value before it is a digit and I do that till either it is not
    # a digit or it past index 0 while doing this, if it is a digit I am
    # appending the value to the front of the part number
    # then I basically do the same thing again but walking forward by adding 1
    # until I reach past the length of the row. This time I append the digit
    # to the end of the number. Now to avoid adding the same digit twice I check
    # to see I have the default value of part_digits[row][col] set to False
    # and I only go throught the part digits the haven't been checked
    # As I move figure out the full part number I check to see if that column
    # already exists in part_digits and set it to True that way I don't iterate
    # over that part digit in a future interation
    for row in part_digits:
        for col in part_digits[row]:
            if not part_digits[row][col]:
                part_digits[row][col] = True
                part_number = puzzle_contents[row][col]

                is_continous = True
                c = col - 1
                while c >= 0 and is_continous:
                    if puzzle_contents[row][c].isnumeric():
                        part_number = puzzle_contents[row][c] + part_number
                        if c in part_digits[row]:
                            part_digits[row][c] = True
                        c -= 1
                    else:
                        is_continous = False

                is_continous = True
                c = col + 1
                while c <= len(puzzle_contents[row]) - 1 and is_continous:
                    if puzzle_contents[row][c].isnumeric():
                        part_number += puzzle_contents[row][c]
                        if c in part_digits[row]:
                            part_digits[row][c] = True
                        c += 1
                    else:
                        is_continous = False
                part_numbers.append(int(part_number))
    return sum(part_numbers)


def part_2(input_file: str):
    with open(input_file, "r") as f:
        puzzle_contents = f.read().splitlines()

    part_digits = {}
    for row, line in enumerate(puzzle_contents):
        for col, char in enumerate(line):
            if char == "*":
                for r in range(max(0, row - 1), min(len(puzzle_contents) + 1, row + 2)):
                    for c in range(max(0, col - 1), min(len(line) + 1, col + 2)):
                        if puzzle_contents[r][c].isnumeric():
                            if not part_digits.get(r):
                                part_digits[r] = {}
                            part_digits[r][c] = {
                                "is_checked": False,
                                "gear_position": (row, col),
                            }
    part_numbers = []
    gear_position_count = {}
    for row in part_digits:
        for col in part_digits[row]:
            if not part_digits[row][col]["is_checked"]:
                part_digits[row][col]["is_checked"] = True
                gear_row = part_digits[row][col]["gear_position"][0]
                gear_col = part_digits[row][col]["gear_position"][1]
                if not gear_position_count.get(gear_row):
                    gear_position_count[gear_row] = {}
                gear_position_count[gear_row][gear_col] = 1 + gear_position_count.get(
                    gear_row
                ).get(gear_col, 0)
                part_number = puzzle_contents[row][col]

                is_continous = True
                c = col - 1
                while c >= 0 and is_continous:
                    if puzzle_contents[row][c].isnumeric():
                        part_number = puzzle_contents[row][c] + part_number
                        if c in part_digits[row]:
                            part_digits[row][c]["is_checked"] = True
                        c -= 1
                    else:
                        is_continous = False

                is_continous = True
                c = col + 1
                while c <= len(puzzle_contents[row]) - 1 and is_continous:
                    if puzzle_contents[row][c].isnumeric():
                        part_number += puzzle_contents[row][c]
                        if c in part_digits[row]:
                            part_digits[row][c]["is_checked"] = True
                        c += 1
                    else:
                        is_continous = False
                part_numbers.append([int(part_number), (gear_row, gear_col)])
    gear_ratios = []
    for row in gear_position_count:
        for col in gear_position_count[row]:
            if gear_position_count[row][col] == 2:
                gear_ratio = 1
                for part_number in part_numbers:
                    if row == part_number[1][0] and col == part_number[1][1]:
                        gear_ratio *= part_number[0]
                gear_ratios.append(gear_ratio)
    return sum(gear_ratios)


if __name__ == "__main__":
    input_file = Path(__file__).parent.parent / "data" / "input.txt"
    print("The answer to Part 1:", part_1(input_file))
    print("The answer to Part 2:", part_2(input_file))
