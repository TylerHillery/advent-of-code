import { readFile } from "node:fs/promises";
import path from "node:path";

const CUBE_COLORS = ["red", "green", "blue"] as const;

type CubeColors = (typeof CUBE_COLORS)[number];
type CubeSet = [number, CubeColors];
type CubeGame = {
  gameId: number;
  draws: CubeSet[][];
};

function assertCubeColor(str: string | undefined): asserts str is CubeColors {
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  if (!CUBE_COLORS.includes(str as any)) {
    throw new Error(`Not of type color: ${CUBE_COLORS.join(",")}`);
  }
}

export function parseInput(data: string): CubeGame[] {
  const games: CubeGame[] = [];
  for (const line of data.split("\n")) {
    // @ts-expect-error temp comment to ignore undefined error
    const gameId = Number(line.split(":")[0].split(" ")[1]);
    const rawGameValues = line.split(":")[1];

    if (rawGameValues !== undefined) {
      const draws: CubeSet[][] = [];
      for (const rawCubeSet of rawGameValues.split(";")) {
        const cubeSets: CubeSet[] = [];
        for (const rawCube of rawCubeSet.split(",")) {
          if (typeof rawCube === "string") {
            const rawCubeParts = rawCube.trim().split(" ");
            const numberOfCubes = Number(rawCubeParts[0]);
            const rawCubeColor = rawCubeParts[1];
            assertCubeColor(rawCubeColor);
            const cubeSet: CubeSet = [numberOfCubes, rawCubeColor];
            cubeSets.push(cubeSet);
          }
        }
        draws.push(cubeSets);
      }
      const cubeGame: CubeGame = {
        gameId: gameId,
        draws: draws,
      };
      games.push(cubeGame);
    }
  }
  return games;
}

export function part1(cubeGames: CubeGame[]): number {
  const NUMBER_OF_CUBES: Record<CubeColors, number> = {
    red: 12,
    green: 13,
    blue: 14,
  };

  function isLessThanTotalCubes(element: CubeSet[]) {
    return element.every((cubeSet) => {
      const [numberOfCubes, cubeColor] = cubeSet;
      return numberOfCubes <= NUMBER_OF_CUBES[cubeColor];
    });
  }

  const possibleGames = cubeGames.filter((game) =>
    game.draws.every(isLessThanTotalCubes),
  );

  return possibleGames.reduce((sum, game) => sum + game.gameId, 0);
}

export function part2(cubeGames: CubeGame[]): number {
  let result = 0;
  for (const game of cubeGames) {
    const maxNumberofCubes: Record<CubeColors, number> = {
      red: 0,
      green: 0,
      blue: 0,
    };
    for (const cubeSet of game.draws.flat()) {
      const [numberOfCubes, cubeColor] = cubeSet;
      if (numberOfCubes > maxNumberofCubes[cubeColor]) {
        maxNumberofCubes[cubeColor] = numberOfCubes;
      }
    }

    const power = Object.values(maxNumberofCubes).reduce((power, current) => {
      if (current > 0) {
        power *= current;
      }
      return power;
    });
    result += power;
  }
  return result;
}

if (import.meta.filename === process.argv[1]) {
  const inputFilePath = path.join(
    import.meta.dirname,
    "..",
    "data",
    "input.txt",
  );
  const data = await readFile(inputFilePath, "utf-8");
  console.log("Answer to part 1:", part1(parseInput(data)));
  console.log("Answer to part 2:", part2(parseInput(data)));
}
