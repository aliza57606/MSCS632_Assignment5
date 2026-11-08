# Ride Sharing System — C++ and GNU Smalltalk

This assignment implements a class-based ride sharing demonstration in two languages. Both versions have a `Ride` superclass; `StandardRide` and `PremiumRide` subclasses; encapsulated `Driver` and `Rider` ride collections; and polymorphic fare calculation.

## Run C++

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o rideshare
./rideshare
```

## Run Smalltalk (GNU Smalltalk)

On macOS, install GNU Smalltalk using Homebrew:

```bash
brew install gnu-smalltalk
gst RideSharing.st
```

The script is targeted at GNU Smalltalk 3.x (not Pharo or Squeak).

## Expected fares
- Standard: $3.00 base + $2.00/mile; 5 miles = $13.00
- Premium: $6.00 base + $3.50/mile; 8 miles = $34.00

## Notes
- C++ was compiled and executed in the authoring environment.
- The Smalltalk implementation was written against GNU Smalltalk's documented syntax but could not be executed in the authoring environment; please run and capture your own terminal screenshot before submission.
- Add your own GitHub repository URL to the report after publishing the files.
