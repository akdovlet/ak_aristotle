# Usage

```
cd philo
make
./philo 199 303 100 100 8
```
arguments correspond to: amount of philosophers, time to die in ms, time to eat in ms, time to sleep in ms
and the last optional argument corresponds to the amout of times each philosopher must eat in order to complete the simulation

If given enough time ((time to eat && time to eat sleep) < time to die), no philosophers should die. If given an odd amount of philosophers, they will require 3*time_to_eat to survive the simulation
