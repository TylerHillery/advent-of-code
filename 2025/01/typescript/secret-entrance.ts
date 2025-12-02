import { readFile } from "node:fs/promises";
import path from "node:path";

const DIRECTIONS = ["L", "R"] as const;

type Direction = (typeof DIRECTIONS)[number];

function isDirection(input: unknown): input is Direction {
  return DIRECTIONS.includes(input as Direction);
}

export function part1(input: string): number {
  let counter = 0;
  input.split("\n").reduce((acc, line) => {
    const direction = line[0];
    if (!isDirection(direction)) {
      throw new Error(
        `Not a valid direction must be one of: ${DIRECTIONS.join()}`,
      );
    }
    const distance = Number(line.slice(1));
    switch (direction) {
      case "L":
        acc = (acc - distance) % 100;
        if (acc < 0) {
          acc += 100;
        }
        break;
      case "R":
        acc = (acc + distance) % 100;
        break;
    }
    if (acc === 0) counter++;
    return acc;
  }, 50);

  return counter;
}

export function part2(input: string): number {
  console.log(input);
  return 42;
}

async function main() {
  const data = await readFile(
    path.join(import.meta.dirname, "..", "data", "input.txt"),
    "utf-8",
  );
  const part1Answer = part1(data);
  console.log(`Answer to Part 1: ${part1Answer}`);
}

main();
