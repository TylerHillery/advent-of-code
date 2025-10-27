import { readFile } from "node:fs/promises";
import path from "node:path";

import { argv } from "process";

export type BinarySearchResult = {
  isFound: boolean;
  index: number;
};

// FEEDBACK:
// - really should be called bisectLeft after I later learned
export function binarySearch<T>(arr: T[], target: T): BinarySearchResult {
  let left = 0;
  let right = arr.length - 1;
  while (left <= right) {
    const mid = Math.floor((left + right) / 2);
    const value = arr[mid];

    if (value === target) {
      return { isFound: true, index: mid };
    } else if (value! > target) {
      // TODO: add undefined checks vs non null assertion
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return { isFound: false, index: left };
}

export function insertIntoSortedArray<T>(arr: T[], n: T): T[] {
  // NOTES
  // we want to return a new array with n inserted into arr that's already sorted
  // we can do a binary search to find the index to sort into
  // problem is any form of copying is considered O(N)
  // so if copying is O(N) we mine as well just create a new array instead an add
  // one by one to the array

  // this has me thinking though, all "functional" languages / patterns that always
  // have you return a new object if the object is passed by reference vs modifying
  // doesn't do the following downsides
  // 1. Terrible for performance because you have to copy array to a new array
  // 2. Bad for memory because you creating entire new object

  // PRIOR SOLUTION BEFORE BINARY SEARCH IMPLEMENTATION
  // let result: number[] = [];
  // for (const [index, element] of Object.entries(arr)) {
  //   // if we know n <= current element then we can just push n and the rest of
  //   // the array to the new array. Still doesn't help the time complexity but
  //   // does help average run time.
  //   if (n <= element) {
  //     result.push(n);
  //     result.push(...arr.slice(Number(index)));
  //     return result;
  //   }
  //   result.push(element);
  // }

  // // we know if it's hasn't returned yet then n is > max element in array
  // // so we still need to push it
  // result.push(n);
  // return result;

  // NON-MUTING ORIGINAL ARRAY O(N) BECAUSE OF NEED FOR SPREADING
  const { index } = binarySearch(arr, n);

  return [...arr.slice(0, index), n, ...arr.slice(index)];

  // MUTING ORIGINAL ARRAY O(log n)
  // if arrays under hood are link listed then splicing should be O(1)
  // because you don't need to recopy the elements over it's just updating the
  // next and previous pointers
  // let { isFound, index } = binarySearch(arr, n);

  // // if array isn't found and it's last index was the last element of arr
  // // we know item is great than all other items in a arr so we need to push
  // if (!isFound && index === arr.length - 1) {
  //   arr.push(n);
  //   return arr;
  // }

  // arr.splice(index, 0, n);
  // return arr

  // After further research, JavaScript arrays are contingous so splice is a O(N)
  // operation because of the need to shift all the elements over.

  // Also a silly assumption I had is you can't be able to do binarySearch on
  // have a list and also have O(1) insertion. The O(1) requites a linked list
  // which you can't binarySearch on.

  // This begs the question what data structure should I use that would allow me
  // to search it in O(Log N) time and update it in O(Log N) while keeping it sorted?
}

// FEEDBACK:
// - zip is best implement with (...arrays)
// - if arrays are of same length map already gives and index number as well
// - so you can just use map with the index or just map on smallest array
export function* zipMap<T, U, K>(arr1: T[], arr2: U[], cb: (x: T, y: U) => K) {
  // generator that interates through two arrays stoping at the shorter one
  // then applying a callback function expecting element from each array
  // returning the result of K for each iteraton
  const minLength = Math.min(arr1.length, arr2.length);
  for (let i = 0; i < minLength; i++) {
    yield cb(arr1[i]!, arr2[i]!); // TODO: add undefined checks vs non null assertions
  }
}

// FEEDBACK:
// - better off just adding to an array and sorting after vs keeping array sorted
export function part1(data: string): number {
  let list1: number[] = [];
  let list2: number[] = [];

  // looping through all of this is going to be O(N)
  for (const line of data.split("\n")) {
    const [leftStr, rightStr] = line.split("   ");
    const leftNum = Number(leftStr);
    const rightNum = Number(rightStr);
    list1 = insertIntoSortedArray(list1, leftNum);
    list2 = insertIntoSortedArray(list2, rightNum);
  }

  function absoluteDifference(x: number, y: number): number {
    return Math.abs(x - y);
  }

  const totalDistance = zipMap(list1, list2, absoluteDifference).reduce(
    (sum, currentValue) => sum + currentValue,
    0,
  );

  return totalDistance;
}

export function part2(data: string): number {
  // we loop through the raw data if number belongs to left list we just push
  // it onto the leftArray to keep track of all left items. For the right list
  // thought we have an Object that keeps track of acts a a counter for each element
  // that appears in the right list. This allows a simple lookup to see how many
  // times the left element appears in the right list
  const leftArray = [];
  const rightOccurences: Record<string, number> = {};

  for (const line of data.split("\n")) {
    const [leftStr, rightStr] = line.split("   ");
    const leftNum = Number(leftStr);
    const rightNum = Number(rightStr);
    leftArray.push(leftNum);
    rightOccurences[rightNum] = (rightOccurences[rightNum] ?? 0) + 1;
  }

  const result = leftArray
    .map((n) => (rightOccurences[n] ? rightOccurences[n] * n : 0))
    .reduce((sum, current) => sum + current);

  return result;
}

if (argv[1] === import.meta.filename) {
  const data = await readFile(
    path.join(import.meta.dirname, "..", "data", "input.txt"),
    "utf-8",
  );

  console.log("Answer to part 1:", part1(data));
  console.log("Answer to part 2:", part2(data));
}
