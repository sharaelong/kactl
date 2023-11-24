/**
 * Author:
 * Description:
 */
#pragma once

mt19937 rng(1010101);
lint randInt(lint l, lint r) {
    return uniform_int_distribution<lint>(l, r)(rng);
}

import random
random.randrange(s, e)  # random integer from [s, e)
random.random()         # random float from [0, 1)
random.uniform(a, b)    # random float from [a, b]
random.shuffle(list)    # shuffle list
random.sample(list, n)  # sampling without replacement
