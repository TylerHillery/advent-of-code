import { readFile } from "node:fs/promises";
import path from "node:path";

export function part1(input: string) {
  // TODO: regex is probably better than splitting
  const sum = input.split(",").reduce((sum, range) => {
    const [lowerBound, upperBound] = range.split("-").map((id) => Number(id));
    if (lowerBound === undefined) {
      throw Error(`Parsing range ${range} failed`);
    }
    if (upperBound === undefined) {
      throw Error(`Parsing range ${range} failed`);
    }

    for (let i = lowerBound; i <= upperBound; i++) {
      const iStr = i.toString();
      if (iStr.length % 2 !== 0) {
        continue;
      }
      const mid = iStr.length / 2;
      if (iStr.slice(0, mid) === iStr.slice(mid)) {
        sum += i;
      }
    }
    return sum;
  }, 0);
  return sum;
}

export function part2(input: string) {
  const sum = input.split(",").reduce((sum, range) => {
    const [lowerBound, upperBound] = range.split("-").map((id) => Number(id));

    if (lowerBound === undefined) {
      throw new Error(`Parsing range ${range} failed`);
    }
    if (upperBound === undefined) {
      throw new Error(`Parsing range ${range} failed`);
    }

    for (let i = lowerBound; i <= upperBound; i++) {
      // how do we find the length of the pattern?
      // we no longer can just split in half and compare
      // lets just brute force we know the smallest pattern length of 1
      // and the largest pattern you can have is half the length of iStr
      const iStr = i.toString();

      const maxPatternLength = Math.floor(iStr.length / 2); // TODO: if only one digit this might cause issues

      for (
        let patternLength = 1;
        patternLength <= maxPatternLength;
        patternLength++
      ) {
        // we know if the str length is not evenly divisble by the pattern it doesn't repeat
        if (iStr.length % patternLength !== 0) {
          continue;
        }

        // NOTE: original idea was to split the string in equal parts and confirm they all equal
        // if (
        //   !splitStrToEqualParts(iStr, patternLength).every(
        //     (value) => value === iStr.slice(0, patternLength)
        //   )
        // ) {
        //   continue;
        // }

        // new idea is to recreate the string since we know the pattern and how many
        // times to repeat and then compare to see if it equals iStr
        const pattern = iStr.slice(0, patternLength);
        const repeat = iStr.length / patternLength;
        if (iStr === pattern.repeat(repeat)) {
          sum += i;
          break; // once we find the smallest pattern we can break out of inner loop;
        }
      }
    }

    return sum;
  }, 0);
  return sum;
}

const data = await readFile(
  path.join(import.meta.dirname, "..", "data", "input.txt"),
  "utf-8",
);

console.log(`Answer to Part 1: ${part1(data)}`);
console.log(`Answer to Part 2: ${part2(data)}`);

// Utility Function
export function splitStrToEqualParts(
  str: string,
  partLength: number,
): string[] {
  if (str.length % partLength !== 0) {
    throw new Error("Can't divide string into equal part lengths");
  }
  const strs: string[] = [];
  let start = 0;
  for (let i = partLength; i <= str.length; i += partLength) {
    strs.push(str.slice(start, i));
    start = i;
  }
  return strs;
}
