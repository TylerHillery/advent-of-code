import { readFile } from "node:fs/promises";
import path from "node:path";
import { fileURLToPath } from "node:url";

export async function part1(file: string): Promise<number> {
  const data = await readFile(file, "utf-8");

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

if (import.meta.url === `file://${process.argv[1]}`) {
  const filename = fileURLToPath(import.meta.url);
  const inputFilePath = path.join(filename, "..", "..", "data", "input.txt");

  console.log("Answer to part 1:", await part1(inputFilePath));
}
