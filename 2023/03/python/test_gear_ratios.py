from pathlib import Path

from gear_ratios import part_1, part_2


def test_part_1():
    input_file = Path(__file__).parent.parent / "data" / "example_input_part_1.txt"
    result = part_1(input_file)
    expected_result = 4361
    assert result == expected_result


def test_part_2():
    input_file = Path(__file__).parent.parent / "data" / "example_input_part_2.txt"
    result = part_2(input_file)
    expected_result = 467835
    assert result == expected_result
