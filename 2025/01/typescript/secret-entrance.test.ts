import { readFile } from "node:fs/promises";
import path from "node:path";

import { expect, test } from "vitest";

import { part1 } from "./secret-entrance";

test("Part 1", async () => {
  const data = await readFile(
    path.join(import.meta.dirname, "..", "data", "example_input_part_1.txt"),
    "utf-8",
  );
  const result = part1(data);
  const expected = 3;
  expect(result).toEqual(expected);
});
