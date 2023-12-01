def part_1():
    with open("day_01_puzzle_input.txt", "r") as f:
        lines = f.read().splitlines()

    calibrations = []
    for line in lines:
        numbers = "".join([char for char in line if char.isnumeric()])
        calibrations.append(int(numbers[0] + numbers[-1]))

    return sum(calibrations)


def part_2():
    NUM_WORDS = {
        "one": "1",
        "two": "2",
        "three": "3",
        "four": "4",
        "five": "5",
        "six": "6",
        "seven": "7",
        "eight": "8",
        "nine": "9",
    }

    with open("day_01_puzzle_input.txt", "r") as f:
        lines = f.read().splitlines()

    calibrations = []
    for line in lines:
        nums_in_lines = {}
        i = 0
        while i < len(line):
            for num_word in NUM_WORDS:
                if line[i:].startswith(num_word):
                    nums_in_lines[i] = NUM_WORDS[num_word]
            if line[i].isnumeric():
                nums_in_lines[i] = line[i]
            i += 1

        number_only_line = "".join([nums_in_lines[idx] for idx in sorted(nums_in_lines)])

        calibrations.append(int(number_only_line[0] + number_only_line[-1]))
    return sum(calibrations)


if __name__ == "__main__":
    print("Answer to Part 1:", part_1())
    print("Answer to Part 2:", part_2())
