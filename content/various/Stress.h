/**
 * Author:
 * Description:
 */
#pragma once

import os
while True:
    with open("input.txt", "w") as f:
        # Generate Data
        pass
    
    os.system("source.exe < input.txt > output.txt")
    if os.system("checker.exe < input.txt") != 0:
        break
