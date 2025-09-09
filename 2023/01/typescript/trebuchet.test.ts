import path from "node:path";

import { fileURLToPath } from "url";
import { describe, expect,it } from "vitest";

import { part1 } from "./trebuchet";

describe("Day 1: Trebuchet?!", () => {
  it("Part 1", async () => {
    const inputFile = path.join(
      fileURLToPath(import.meta.url),
      "..",
      "..",
      "data",
      "example_input_part_1.txt",
    );
    const result = await part1(inputFile);
    const expectedResult = 142;
    expect(result).toEqual(expectedResult);
  });
});
