import { readFile } from "node:fs/promises";
import path from "node:path";

import { describe, expect, it } from "vitest";

import { parseInput, part1, part2 } from "./cube-conundrum";

describe("Day 2: Cube Conundrum", () => {
  it("Part 1", async () => {
    const inputFilePath = path.join(
      import.meta.dirname,
      "..",
      "data",
      "example_input_part_1.txt",
    );
    const data = await readFile(inputFilePath, "utf-8");
    const result = part1(parseInput(data));
    const expectedResult = 8;
    expect(result).toEqual(expectedResult);
  });

  it("Part 2", async () => {
    const inputFilePath = path.join(
      import.meta.dirname,
      "..",
      "data",
      "example_input_part_2.txt",
    );
    const data = await readFile(inputFilePath, "utf-8");
    const result = part2(parseInput(data));
    const expectedResult = 2286;
    expect(result).toEqual(expectedResult);
  });
});
