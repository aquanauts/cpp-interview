# Aquatic's C++ Test

## Background
An exchange is a process that accepts orders from market participants, and matches "bid" orders (buys) with "ask" orders (sells). When the orders match (described below), the relevant orders "trade".

Orders are uniquely identified by an unsigned integer. Orders have a "side" (either `BID` or `ASK`), a "price" (a signed integer), and a "quantity" (an unsigned integer).

A bid order's price is the maximum price the participant is prepared to pay. An ask order's price is the minimum price the participant is prepared to sell for.

An order that doesn't immediately match an existing order to buy or sell is remembered, and becomes valid until it is either traded against by a subsequent order, or is canceled. Such an order is said to "rest" in the book.

An incoming order is compared to all the resting orders on the opposite side of the book (incoming bids are matched against resting asks and vice versa). Matches occur when the incoming order is at or better than any resting order(s). Each match causes two trades to be noted: the resting order trades and then the incoming order. The quantity that trades is the minimum of the two orders, and the price is that of the resting order.

An incoming order can match multiple resting orders. Orders are matched by the best price first, and then for orders at the same price, by the order that rested first.

If the incoming order has any remaining quantity left, it will rest in the book.

You will not be asked to delete a non-existent order. An order with a given ID will be added at most once.

### Examples

All these examples assume the book is empty to start with. Some examples are also present in `test.cpp`.

#### Example one

- A bid order at price 150 for quantity 10 rests.
- An ask order at price 150 for quantity 5 will trade 5 lots against the resting bid order (resulting in two trades, one for the resting order, and then one for the incoming ask order). No quantity rests from the ask order.
- A subsequent ask order at price 150 for 20 will trade the remaining 5 lots with the resting order (again, resulting in two trades). The resting bid order is used up, and the remaining quantity in the incoming order (15, in this case) will rest.

#### Example two

- A bid order at price 150 for quantity 10 rests.
- Another bid order at price 150 for quantity 50 rests.
- Yet another bid order at price 155 for quantity 20 rests.
- An incoming ask order to sell 1000 at price 140 will match with, in this sequence:
  - the bid order at 155, for 20, depleting it.
  - the first-placed bid order at 150 for 10, depleting it.
  - the bid order at 150 for 50, depleting it
- the incoming ask order then rests at price 140 with remaining quantity 920

## Your task

Your task is to finish the code in `src/Exchange.cpp`, recording orders as they are placed, potentially matching resting orders, and deleted. Your code must match orders appropriately, and should call the constructor-provided `TradeReporter`'s `on_trade` method with the details of the matching trade. We'll use the tests in `test.cpp` as our entry point.

Simple types are provided in `src/Types.hpp`. Please feel free to modify existing files or to add files. Compiler flags are specified in `CMakeLists.txt`.


### Some things to consider

We expect that solving this will take you about two hours. Your implementation should prioritize correctness and simplicity, rather than performance, generality, or the accurate simulation of real-world exchanges.

Here are some of the things we'll be looking for in your solution:
  * Can you understand the development environment and be productive in it?
  * Can you create a straightforward and effective solution in a reasonable amount of time?
  * Is there any unnecessary complexity? Is the amount of abstraction appropriate?
  * Does it resemble software that others would want to maintain in perpetuity?
  * Does it demonstrate an awareness for contemporary best practices in C++?

## Development

The repository, in its current state, is only compatible with a 64-bit version of a Linux-based OS. We recommend accessing one for free via a Github Codespace (see `codespace.png` if you're unfamiliar with how to obtain one). A Codespace is a preconfigured, isolated development container running in the cloud, and so insulates you from some potential development environment woes. The next stage of the interview process will also be conducted within a collaborative Codespace (due to the availability of a convenient live sharing extension), extending the work you do in this stage.

When you've got the repository checked out in your environment of choice, it's important to first create a working branch with `git checkout -b [your branch name]`, since you'll be submitting a `git diff` of the result of your work and the state of `main`.

When you're on your branch, `make build` will build the unit test binary, and `make test` will run it. If you're not working in a Codespace, these commands will get dependencies if they're not already present, so it'll take a while the first time you run either of these. You can modify `environment.yml` as well as the `Makefile` and `CMakeLists.txt` to adjust the development environment as you see fit.

You can build and run in release mode by setting the environment variable `BUILD_TYPE=release` in your invocation of either `make build` or `make test`.

When you're satisfied with your work, run `make patch` and submit the resultant patch file, `aqtc_cpp.patch`, to the link sent in the e-mail you received.
