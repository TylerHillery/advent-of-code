from pathlib import Path

from cube_conundrum import part_1, part_2


def test_part_1():
    input_file = Path(__file__).parent.parent / "data" / "example_input_part_1.txt"
    result = part_1(input_file)
    expected = 8
    assert result == expected


def test_part_2():
    input_file = Path(__file__).parent.parent / "data" / "example_input_part_2.txt"
    result = part_2(input_file)
    expected = 2286
    assert result == expected
