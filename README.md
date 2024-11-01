# Air Traffic Control

## Background

Let's say that we're an air traffic control team, and we'd like to write some software to help our human traffic controllers ensure that the aircraft under our management at any given moment aren't at risk of colliding with each other. Towards that objective, we'd like to write a C++ library that processes messages that contain information about aircraft location. Each position message consists of the following fields:

- `timestamp`: a timestamp for the current air traffic control session in milliseconds
- `aircraft_id`: the aircraft's identifier
- `position`: a 3D vector indicating the current position of the aircraft
- `direction`: a unit 3D vector indicating the direction of the aircraft's travel
- `speed`: the aircraft's speed in meters per second

In addition, there are departure messages that arise when an aircraft exits our airspace.

Your task is to finish the `Planespotter` class in `src/Planespotter.cpp` and to write some basic documentation in `DOCUMENTATION.md` explaining to a project manager the assumptions that the software makes, its limitations, operating recommendations for the software in its current state, and recommendations for a future iterations.

A `Planespotter` models each aircraft as a point moving at a constant speed in a straight line in 3 dimensions. Upon receiving a position message, the `Planespotter` should tell us whether any of these points are expected to cause a proximity violation with any of the other known aircraft, assumed to still be proceeding on their last known courses, over some provided time horizon. The proximity threshold and prediction time horizon can be configured by the user of a `Planespotter`. There's some middle school math involved, but we won't get any more involved than that.

The unit tests in `test.cpp` will act as the entry point for running your library code and as a limited form of validation. Feel free to add any additional classes, libraries, tests, etc. that you're inclined to. You may even modify the signature of the `Planespotter` methods, so long as it retains its utility.

### What we're looking for
We expect that solving this will take you about two hours of active development (i.e. reading this, consulting reference material, typing, iteration, validation) time, although you're free to take as much or as little time as you want. Your implementation should prioritize correctness and maintainability, rather than performance, generality, or the accurate simulation of real-world collision avoidance systems. None of those other qualities are bad, however, and we'd certainly welcome a solution that incorporated them; you can also comment in `DOCUMENTATION.md` about how you'd extend the software along those other axes.

Here are some of the things we'll be looking for in your solution:
  * Can you understand the development environment and be productive in it?
  * Can you create a straightforward and effective solution in a reasonable amount of time?
  * Can you write technical material that's useful to its audience?
  * Is there any unnecessary complexity? Is the amount of abstraction appropriate?
  * Can you write software that others would want to maintain in perpetuity?
  * Does it demonstrate an awareness for contemporary best practices in C++?

## Development

The repository is compatible with a 64-bit version of a Linux-based OS. We recommend accessing one for free via a Github Codespace (see `codespace.png` for a screenshot of where to click on Github). A Codespace is a preconfigured, isolated development container running in the cloud, and so insulates you from some potential development environment woes. The follow-up interview will also be conducted within a collaborative Codespace.

When you've got the repository checked out in your environment of choice, it's important to first create a working branch with `git checkout -b [your branch name]`, since you'll be submitting a `git diff` of the result of your work and the state of `main`.

When you're on your branch, `make build` will build the unit test binary, and `make test` will run it. If you're not working in a Codespace, these commands will get dependencies if they're not already present, so it'll take a while the first time you run either of these. You can modify `environment.yml` as well as the `Makefile` and `CMakeLists.txt` to adjust the development environment as you see fit.

You can build and run in release mode by setting the environment variable `BUILD_TYPE=release` in your invocation of either `make build` or `make test`.

When you're done, run `make patch` and send the result, `aqtc_cpp.patch`, to your recruiter via e-mail. 
