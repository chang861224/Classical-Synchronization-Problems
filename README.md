# Single-Lane-Bridge-Problem
This is a group project of Operating Systems course

## Problem:
7. Single Lane Bridge (SLB) Problem
The problem is depicted in below figure. A bridge over a river is only wide enough to permit a
single lane of traffic. Consequently, cars can only move concurrently if they are moving in the
same direction. A safety violation occurs if two cars moving in different directions enter the
bridge at the same time.
In our concurrent programming model, each car is a thread and the problem is to ensure that
cars moving in different directions (eastbound and westbound) cannot concurrently access the
shared resource, i.e., the bridge. The car is moving fast, but it is not instantaneous it might
takes a random number of ticks to go from one side to the other. Again (Use interrupt –>
OneTick() ) to make the simulation more realistic, we must also ensure that cars moving in the
same direction cannot pass each other. The bridge is also not strong enough to hold more than
m cars at a time.
Find a solution to this problem which does not cause starvation. That is, cars that want to
get across should eventually get across. However, we want to maximize use of the bridge. Cars
should travel across to the maximum capacity of the bridge. If a car leaves the bridge going
east and there are no westbound cars, then the next eastbound car should be allowed to cross.
We don’t want a solution which moves cars across the bridge m at a time, i.e., eastbound cars
that are waiting should not wait until all m cars that are eastbound and crossing the bridge
have crossed before being permitted to cross.

![Alt text](https://cdn.discordapp.com/attachments/371122008018386944/503460548751654922/2018-10-21.png)
