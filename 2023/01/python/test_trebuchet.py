from pathlib import Path

from trebuchet import part_1, part_2


def test_part_1():
    input_file = Path(__file__).parent.parent / "data" / "example_input_part_1.txt"
    result = part_1(input_file)
    expected = 142
    assert result == expected


def test_part_2():
    input_file = Path(__file__).parent.parent / "data" / "example_input_part_2.txt"
    result = part_2(input_file)
    expected = 281
    assert result == expected
