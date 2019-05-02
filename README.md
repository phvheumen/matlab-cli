# matlab-cli
A small and simple tool to give matlab truly a command line interface. 
The tool should work for any platform MATLAB can run on, however it is only tested on Windows. 
It is making use of the MATLAB C++ Engine API introduced in 2017b.

## Compile
Make sure MATLAB is configured with a suitable compiler. On Windows I use 'MinGW64 Compiler (C++)'.
One can verify the compiler used for this tool with `mex -setup -client engine cpp`

Furthermore make sure that the dynamic libraries path are added to the correct environment variables depending on the platform.
Inform https://nl.mathworks.com/help/matlab/matlab_external/build-c-engine-programs.html for the locations.

Note: It seems the Windows paths are incorrectly indicated on the Mathworks website. The following path must be added to PATH on Windows:
`<matlabroot>\extern\bin\win64`

compile with command `mex -client engine matlab-cli.cpp`

## Usage
Interactive usage. Exit with Crtl+C.

``` 
C:\matlab-cli\>matlab-cli
>> magic(5)

ans =

    17    24     1     8    15
    23     5     7    14    16
     4     6    13    20    22
    10    12    19    21     3
    11    18    25     2     9

>>
```

Run scripts. Here a dummy script `gen_seq` is used that is used to generate the 10 first numbers of the Fibonacci sequence.
```
C:\matlab-cli>matlab-cli gen_seq

F =

     1     1     2     3     5     8    13    21    34    55

```

If a batch of scripts need to be run, it is more efficient to first start a Matlab instance with
```
matlab -r "matlab.engine.shareEngine"
```
That starts a Matlab instance where the engine is shared and the matlab-cli can connect to. Otherwise matlab-cli will start and close a MATLAB instance every time it is invoked.


