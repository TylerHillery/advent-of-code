import { readFile } from "node:fs/promises";
import path from "node:path";

import { describe, expect, test } from "vitest";

import {
  binarySearch,
  insertIntoSortedArray,
  part1,
  part2,
  zipMap,
} from "./historian-hysteria";

describe.each([
  [[1, 2, 3, 4, 5], 3, { isFound: true, index: 2 }],
  [[1, 2, 3, 4, 5], 1, { isFound: true, index: 0 }],
  [[1, 2, 3, 4, 5], 5, { isFound: true, index: 4 }],
  [[1, 2, 3, 4, 5], 6, { isFound: false, index: 5 }],
  [[1, 2, 3, 4, 5], 0, { isFound: false, index: 0 }],
])("binarySearch(T[], T): BinarySearchResult", (arr, target, expected) => {
  test(`should return ${expected}`, () => {
    const result = binarySearch(arr, target);
    expect(result).toEqual(expected);
  });
});

describe.each([
  [[1, 2, 4, 5], 0, [0, 1, 2, 4, 5]],
  [[1, 2, 4, 5], 6, [1, 2, 4, 5, 6]],
  [[1, 2, 4, 5], 3, [1, 2, 3, 4, 5]],
])("insertIntoSortedArray(T[], T): T[]", (arr, n, expected) => {
  test(`should return ${expected}`, () => {
    const result = insertIntoSortedArray(arr, n);
    expect(result).toEqual(expected);
  });
});

describe.each([
  [[1, 2, 3], [4, 5, 6], (x: number, y: number) => x + y, [5, 7, 9]],
])("flatMap(arr1, arr2, cb)", (arr1, arr2, cb, expected) => {
  test(`should return ${expected}`, () => {
    const arr = [];
    for (const result of zipMap(arr1, arr2, cb)) {
      arr.push(result);
    }
    expect(arr).toEqual(expected);
  });
});

test("Part 1", async () => {
  const data = await readFile(
    path.join(import.meta.dirname, "..", "data", "example_input_part_1.txt"),
    "utf-8",
  );
  const result = part1(data);
  const expected = 11;
  expect(result).toEqual(expected);
});

test("Part 2", async () => {
  const data = await readFile(
    path.join(import.meta.dirname, "..", "data", "example_input_part_2.txt"),
    "utf-8",
  );
  const result = part2(data);
  const expected = 31;
  expect(result).toEqual(expected);
});
