def part_1(file: str):
    bag = {"red": 12, "green": 13, "blue": 14}

    with open(file, "r") as f:
        puzzle_contents = f.read().splitlines()

    possible_games = 0

    for line in puzzle_contents:
        game_num = int(line[: line.find(":")].split()[1])
        game_sets = line[line.find(":") + 1 :].split(";")
        game_set_num = 0
        is_possible = True
        while (game_set_num < len(game_sets)) & is_possible:
            cubes = game_sets[game_set_num].split(",")
            for cube in cubes:
                cube_color = cube.strip().split(" ")[1]
                cube_qty = int(cube.strip().split(" ")[0])
                if bag.get(cube_color, 0) < cube_qty:
                    is_possible = False
            game_set_num += 1
        possible_games += game_num if is_possible else 0
    return possible_games


def part_2(file: str):
    with open(file, "r") as f:
        puzzle_contents = f.read().splitlines()

    sum_of_power = 0
    for line in puzzle_contents:
        game_sets = line[line.find(":") + 1 :].split(";")
        game_set_num = 0
        max_so_far = {}
        while game_set_num < len(game_sets):
            cubes = game_sets[game_set_num].split(",")
            for cube in cubes:
                cube_color = cube.strip().split(" ")[1]
                cube_qty = int(cube.strip().split(" ")[0])
                if max_so_far.get(cube_color, 0) < cube_qty:
                    max_so_far[cube_color] = cube_qty
            game_set_num += 1
        power = 1
        for value in max_so_far.values():
            power *= value
        sum_of_power += power
    return sum_of_power


if __name__ == "__main__":
    puzzle_input = "day_02_puzzle_input.txt"
    with open(puzzle_input, "r") as f:
        puzzle_contents = f.read().splitlines()

    print("Answer to Part 1:", part_1(puzzle_contents))
    print("Answer to Part 2:", part_2(puzzle_contents))
