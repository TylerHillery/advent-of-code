import { readFile } from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";

export function part1(data: string): number {
  function getFirstAndLastDigit(str: string): number {
    const digits = str.split("").filter((char) => !isNaN(Number(char))); // could also use a regex str.match(/\d/g)
    const firstDigit = digits[0];
    const lastDigit = digits[digits.length - 1];
    if (firstDigit !== undefined && lastDigit !== undefined) {
      return Number(firstDigit + lastDigit);
    } else {
      return 0;
    }
  }

  return data
    .split("\n")
    .map((line) => getFirstAndLastDigit(line))
    .reduce((sum, cailbrationValue) => sum + cailbrationValue, 0);
}

export function part2(data: string): number {
  function getFirstAndLastDigit(str: string) {
    const validDigits = {
      one: "1",
      two: "2",
      three: "3",
      four: "4",
      five: "5",
      six: "6",
      seven: "7",
      eight: "8",
      nine: "9",
    };
    let firstDigit: string | undefined = undefined;
    let lastDigit: string | undefined = undefined;

    for (let i = 0; i < str.length; i++) {
      if (!isNaN(Number(str[i]))) {
        if (firstDigit === undefined) {
          firstDigit = str[i];
        }
        lastDigit = str[i];
        continue;
      }
      for (const [k, v] of Object.entries(validDigits)) {
        const strDigit = str.slice(i, i + k.length);
        if (strDigit === k) {
          if (firstDigit === undefined) {
            firstDigit = v;
          }
          lastDigit = v;
          break;
        }
      }
    }

    return firstDigit && lastDigit ? Number(firstDigit + lastDigit) : 0;
  }

  return data
    .split("\n")
    .map((line) => getFirstAndLastDigit(line))
    .reduce((sum, value) => sum + value, 0);
}

if (import.meta.url === `file://${process.argv[1]}`) {
  const filename = fileURLToPath(import.meta.url);
  const inputFilePath = path.join(filename, "..", "..", "data", "input.txt");
  const data = await readFile(inputFilePath, "utf-8");

  console.log("Answer to part 1:", part1(data));
  console.log("Answer to part 2:", part2(data));
}
