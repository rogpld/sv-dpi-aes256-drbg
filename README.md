# SV DPI Random Number Generation using AES-256 CTR DRBG

Generates secure random numbers in C and shows the frequency of ones as a report.

## Deps

Tested with:

- Verilator 5.036
- OpenSSL 3.5.3

## Expected output

```bash
# ./build.sh
# ./obj_dir/Vtb

100000 samples
[C-DPI] Initializing NIST RNG...
Bit | Count (1s) | Frequency
----|------------|----------
  0 |   50022    |  50.02%       [OK]
  1 |   50012    |  50.01%       [OK]
  2 |   50017    |  50.02%       [OK]
  3 |   50077    |  50.08%       [OK]
  4 |   49792    |  49.79%       [OK]
  5 |   49864    |  49.86%       [OK]
  6 |   50116    |  50.12%       [OK]
  7 |   49853    |  49.85%       [OK]
  8 |   50229    |  50.23%       [OK]
  9 |   49653    |  49.65%       [OK]
 10 |   50206    |  50.21%       [OK]
 11 |   50073    |  50.07%       [OK]
 12 |   50001    |  50.00%       [OK]
 13 |   49727    |  49.73%       [OK]
 14 |   49874    |  49.87%       [OK]
 15 |   49861    |  49.86%       [OK]
 16 |   50213    |  50.21%       [OK]
 17 |   49905    |  49.91%       [OK]
 18 |   49767    |  49.77%       [OK]
 19 |   49702    |  49.70%       [OK]
 20 |   49924    |  49.92%       [OK]
 21 |   49713    |  49.71%       [OK]
 22 |   49896    |  49.90%       [OK]
 23 |   50061    |  50.06%       [OK]
 24 |   50015    |  50.02%       [OK]
 25 |   49551    |  49.55%       [OK]
 26 |   49959    |  49.96%       [OK]
 27 |   50005    |  50.01%       [OK]
 28 |   49794    |  49.79%       [OK]
 29 |   49893    |  49.89%       [OK]
 30 |   49969    |  49.97%       [OK]
 31 |   50014    |  50.01%       [OK]
DONE
- tb.sv:53: Verilog $finish
- S i m u l a t i o n   R e p o r t: Verilator 5.036 <date>
- Verilator: $finish at 0s; walltime 0.064 s; speed 0.000 s/s
- Verilator: cpu 0.065 s on 1 threads; alloced 497 MB
```

## Refs

- <https://github.com/pq-crystals/kyber/blob/main/ref/nistkat/rng.c>
