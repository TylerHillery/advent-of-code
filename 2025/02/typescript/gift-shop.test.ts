import { readFile } from "node:fs/promises";
import path from "node:path";

import { expect, test } from "vitest";

import { part1, part2, splitStrToEqualParts } from "./gift-shop";

test.each([["1212", 2, ["12", "12"]]])(
  "splitStrToEqualParts(%i, %i) -> %i",
  (str, partLength, expected) => {
    const result = splitStrToEqualParts(str, partLength);
    expect(result).toEqual(expected);
  },
);

test("Part 1", async () => {
  const data = await readFile(
    path.join(import.meta.dirname, "..", "data", "example_input_part_1.txt"),
    "utf-8",
  );
  const result = part1(data);
  const expected = 1227775554;
  expect(result).toEqual(expected);
});

test("Part 2", async () => {
  const data = await readFile(
    path.join(import.meta.dirname, "..", "data", "example_input_part_2.txt"),
    "utf-8",
  );
  const result = part2(data);
  const expected = 4174379265;
  expect(result).toEqual(expected);
});
