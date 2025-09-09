import { readFile } from "node:fs/promises";
import path from "node:path";

import { fileURLToPath } from "url";
import { describe, expect, it } from "vitest";

import { part1, part2 } from "./trebuchet";

describe("Day 1: Trebuchet?!", () => {
  it("Part 1", async () => {
    const inputFile = path.join(
      fileURLToPath(import.meta.url),
      "..",
      "..",
      "data",
      "example_input_part_1.txt",
    );
    const data = await readFile(inputFile, "utf-8");
    const result = part1(data);
    const expectedResult = 142;
    expect(result).toEqual(expectedResult);
  });

  it("Part 2", async () => {
    const inputFile = path.join(
      fileURLToPath(import.meta.url),
      "..",
      "..",
      "data",
      "example_input_part_2.txt",
    );

    const data = await readFile(inputFile, "utf-8");
    const result = part2(data);
    const expectedResult = 281;
    expect(result).toEqual(expectedResult);
  });
});
