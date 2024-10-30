## Aquatic's C++ Test

An exchange is a process that accepts orders from market participants, and matches "bid" orders (buys) with "ask" orders (sells). When the orders match (described below), the relevant orders "trade".

Orders are uniquely identified by an unsigned integer. Orders have a "side" (either `BID` or `ASK`), a "price" (a signed integer), and a "quantity" (an unsigned integer).

A bid order's price is the maximum price the participant is prepared to pay. An ask order's price is the minimum price the participant is prepared to sell for.

An order that doesn't immediately match an existing order to buy or sell is remembered, and becomes valid until it is either traded against by a subsequent order, or is canceled. Such an order is said to "rest" in the book.

An incoming order is compared to all the resting orders on the opposite side of the book (incoming bids are matched against resting asks and vice versa). Matches occur when the incoming order is at or better than any resting order(s). Each match causes two trades to be noted: the resting order trades and then the incoming order. The quantity that trades is the minimum of the two orders, and the price is that of the resting order.

An incoming order can match multiple resting orders. Orders are matched by the best price first, and then for orders at the same price, by the order that rested first.

If the incoming order has any remaining quantity left, it will rest in the book.

You will not be asked to delete a non-existent order. An order with a given ID will be added at most once.

## Examples

All these examples assume the book is empty to start with. Some examples are also present in `tests/test.cpp`.

### Example one

- A bid order at price 150 for quantity 10 rests.
- An ask order at price 150 for quantity 5 will trade 5 lots against the resting bid order (resulting in two trades, one for the resting order, and then one for the incoming ask order). No quantity rests from the ask order.
- A subsequent ask order at price 150 for 20 will trade the remaining 5 lots with the resting order (again, resulting in two trades). The resting bid order is used up, and the remaining quantity in the incoming order (15, in this case) will rest.

### Example two

- A bid order at price 150 for quantity 10 rests.
- Another bid order at price 150 for quantity 50 rests.
- Yet another bid order at price 155 for quantity 20 rests.
- An incoming ask order to sell 1000 at price 140 will match with, in this sequence:
  - the bid order at 155, for 20, depleting it.
  - the first-placed bid order at 150 for 10, depleting it.
  - the bid order at 150 for 50, depleting it
- the incoming ask order then rests at price 140 with remaining quantity 920

## Your task

Your task is to finish the code in `Exchange.cpp`, recording orders as they are placed, potentially matching resting orders, and deleted. Your code must match orders appropriately, and should call the constructor-provided `TradeReporter`'s `on_trade` method with the details of the matching trade. We'll use the tests in `tests/test.cpp` as our entry point.

Simple types are provided in `Types.hpp`. Please feel free to modify existing files or to add files. Compiler flags are specified in the `Makefile`.


### Some things to consider

We expect that solving this will take you about two hours. Your implementation should prioritize correctness and simplicity, rather than performance, generality, or the accurate simulation of real-world exchanges.

Here are some of the things we'll be looking for in your solution:
  * Can you understand the development environment and be productive in it?
  * Can you create a straightforward and effective solution in a reasonable amount of time?
  * Is there any unnecessary complexity? Is the amount of abstraction appropriate?
  * Does it resemble software that others would want to maintain in perpetuity?
  * Does it demonstrate an awareness for contemporary best practices in C++?

## Instructions

`make build` will build the unit test binary; `make test` will run it. These commands will automatically get dependencies from Conda Forge, so it'll take a while the first time you run either of these. You can modify
`environment.yml` as well as the `Makefile` and `CMakeLists.txt` to adjust the development environment as you see fit.
