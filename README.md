# NonogramSolver 🧩

A C++ program to solve n * m Nonogram/Picross puzzles.

You can compile from source using Visual Studio or you can download the release.

```bash
PicrossSolver.exe <filename> <filename2> <...> --help
```

Use the `--help` flag to see an example layout for a Nonogram or optionally open a provided Nonogram file.

**Note:** Dragging a text file onto an .exe in windows runs the program with the filename(s) as an argument. This program works this way too!

## Example

`PicrossSolver hat.txt`

```cmd
Solving 'hat.txt'.
Press enter to compute generation 1.
Input q to exit solver.

|            O -     |
|          O O -     |
|        O O O -     |
|        O O O -     |
|      O O O O -     |
|      O O O O -     |
|    O O O O O -     |
|    O O O O O       |
|    O O O O O O     |
|O O O O O O O O O O |

Pass took 11.235ms
Press enter to compute generation 2.
Input q to exit solver.

|            O O     |
|          O O       |
|        O O O       |
|        O O O       |
|      O O O O       |
|      O O O O       |
|    O O O O O       |
|    O O O O O       |
|    O O O O O O     |
|O O O O O O O O O O |

Pass took 12.049ms
Press enter to compute generation 3.
Input q to exit solver.
```

At the moment this program brute forces the solution using a "bars and stars" algorithm. There is a provided `wolf.txt` testcase which takes too long to compute. If you can solve this Nonogram using this/another program please message me! I would love to learn more.

## Known bugs

This program has a pretty serious memory leak which I'm yet to fix. PR's are welcome but I'm still figuring it out.

Not really a bug, but this program has a multithreaded solution commented out. I found it only improved times for larger Nonograms however they require more passes to solve since they have (sort of) races to compute rows. When they are sequential the program solves the Nonogram faster. So it's off as it compromises to improve speed.
